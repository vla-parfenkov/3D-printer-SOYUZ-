#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx.h"
#include "inverse_task.h"
#include "pwm.h"
#include "mcu_ini.h"
#include "motor_controller.h"
#include "command_handler.h"
#include "adc_ini.h"



#define BUTTON_READ()  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define AF             ((uint8_t) 0x02)
#define IN             ((uint8_t) 0x01)
#define OUT            ((uint8_t) 0x00)
#define AN 						((uint8_t) 0x03)
#define AXIS_X1 				GPIO_Pin_6
#define AXIS_X2 				GPIO_Pin_7
#define AXIS_Y1 				GPIO_Pin_8
#define AXIS_Y2 				GPIO_Pin_9
#define AXIS_Z1 				GPIO_Pin_10
#define AXIS_Z2 				GPIO_Pin_11
#define START_T					0
#define STOP_T					1
#define SEE_T						2
typedef uint8_t					Bool; 


						
uint32_t timer_mcsXhun(uint8_t mode);
void delay_mcsXhun(uint32_t delay_temp);
Bool EndStop (uint16_t MotorPin);
void SetZeroFlag (uint8_t flag);


#endif 

