#include "helpers.h"
#include "servo.h"
#include "gpio.h"
#include "usart.h"
#include "systemclock_config.h"
#include "stm32f4xx.h"
#include <stdio.h>

#define DEBUG

volatile char buffer[255];

void SystemInit(void)
{
/* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif
}

int main(void)
{
  if (SysClockConfig() == COUNTDOWN_EXCEEDED_ERROR)
  {
    return COUNTDOWN_EXCEEDED_ERROR;
  }
  USART_Init_PC();
  
  // Alt function PB3 is connected to TIM2_CH2
  IOPin servo_ax0 = {GPIOB, PIN4, GPIO_ALT_FUNCION, GPIO_ALTF_TIM3_TIM5};
  Servo servo = {servo_ax0, TIM3, 1};
  Servo_Init(servo);
  // GPIO_Config(servo_ax0);
  volatile int i = 0;
  while (1)
  {
    Servo_Write(servo, i++%5);
    // sprintf((char *)buffer, "PB4 Output: %ld\r\n", GPIOB->ODR);
    // send_string_pc((char *) buffer);
    msleep(500);
  }
  return 0;
}