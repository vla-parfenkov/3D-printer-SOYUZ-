/****************************************/
/*			Очередь			*/
/****************************************/

#ifndef QUEUE_H
#define QUEUE_H


#include "main.h"

#define DELAY_COMMAND 1
#define PWM_COMMAND 2
#define SETBITS_COMMAND 3
#define RESETBITS_COMMAND 4

struct QueueCommand {
	uint8_t TypeCommand;
	uint32_t TimeDel;
	TIM_TypeDef* TIMTYPE;
	uint16_t pin;
	uint16_t period;
	uint16_t pulse;
	uint16_t prescaler;
	GPIO_TypeDef* GPIO;
	struct QueueCommand *next;
};



void Push (uint8_t Type, uint32_t timeDel, TIM_TypeDef* timetype, uint16_t Pin, uint16_t Period, uint16_t Pulse, uint16_t Prescaler, GPIO_TypeDef* gpio);
void pop(void);
uint8_t isEmpty (void);

#endif
