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
  volatile int i = 0;
  if (SysClockConfig() == COUNTDOWN_EXCEEDED_ERROR)
  {
    return COUNTDOWN_EXCEEDED_ERROR;
  }
  USART_Init_PC();
  IOPin output = {GPIOA, PIN0};
  IOPin input = {GPIOB, PIN3};
  GPIO_Config(input, GPIO_ANALOG_MODE);
  Servo_Init(output);

  while (1)
  {
    Servo_Write(i++%0xA0);
    sprintf(buffer, "\n Angle: %i\n", i);
    send_string_pc((char *)buffer);
    msleep(5000);
  }
  return 0;
}