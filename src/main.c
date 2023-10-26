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
  IOPin output = {GPIOB, PIN3, 0b0001};
  GPIO_Config(output, GPIO_ALT_FUNCION);
  Timer_Init_PWM(TIM2);
  // Servo_Init(output);
  while (1)
  {
  }
  return 0;
}