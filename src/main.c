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
  // IOPin pot_ax0 = {GPIOA, PIN0, GPIO_ANALOG_MODE, ADC1_IN0};
  IOPin servo_ax0 = {GPIOB, PIN4, GPIO_ALT_FUNCION, GPIO_ALTF_TIM3_TIM5};
  Servo servo = {servo_ax0, TIM3, 1};
  // GPIO_Config(pot_ax0);
  Servo_Init(&servo);
  uint8_t i = 0;
  int8_t operand = 1;
  while (1)
  {
    if (i == 180) {
      operand = -1;
    } else if (i == 0) {
      operand = 1;
    }
    Servo_Write(&servo, i);
    sprintf(buffer, "PWM duty cycle steps: %d\r\n", servo.timer->CCR1);
    send_string_pc(buffer);
    i += operand;
    msleep(1);
  }
  return 0;
}