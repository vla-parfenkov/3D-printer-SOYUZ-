#include "queue.h"
#include <stdio.h>

uint32_t size = 0;
struct QueueCommand queue_command;

void Push (uint8_t Type, uint32_t timeDel, TIM_TypeDef* timetype, uint16_t Pin, uint16_t Period, uint16_t Pulse, uint16_t Prescaler, GPIO_TypeDef* gpio)
{
	if(size == 0){
		queue_command.TypeCommand = Type;
		switch (Type)
		{
			case DELAY_COMMAND:
				queue_command.TimeDel = timeDel;
				break;
			case PWM_COMMAND:
				queue_command.TIMTYPE = timetype;
				queue_command.pin = Pin;
				queue_command.period = Period;
				queue_command.pulse = Pulse;
				queue_command.prescaler = Prescaler;
				break;
			case SETBITS_COMMAND:
				queue_command.GPIO = gpio;
				queue_command.pin = Pin;
				break;
			case RESETBITS_COMMAND:
				queue_command.GPIO = gpio;
				queue_command.pin = Pin;
				break;
		}
		queue_command.next = NULL;
		size++;
	} else {
		struct QueueCommand New;
		New.TypeCommand = Type;
		switch (Type)
		{
			case DELAY_COMMAND:
				New.TimeDel = timeDel;
				break;
			case PWM_COMMAND:
				New.TIMTYPE = timetype;
				New.pin = Pin;
				New.period = Period;
				New.pulse = Pulse;
				New.prescaler = Prescaler;
				break;
			case SETBITS_COMMAND:
				New.GPIO = gpio;
				New.pin = Pin;
				break;
			case RESETBITS_COMMAND:
				New.GPIO = gpio;
				New.pin = Pin;
				break;
		}
		New.next = &queue_command;
		queue_command = New;
		size++;
	}
	
}

void pop(void)
{
	if(size == 0)
	{
		return;
	} else {
		switch (queue_command.TypeCommand)
		{
			case DELAY_COMMAND:
				delay_mcsXhun(queue_command.TimeDel);
				break;
			case PWM_COMMAND:
				PWM (queue_command.TIMTYPE, queue_command.pin, queue_command.period, queue_command.pulse, queue_command.prescaler);
				break;
			case SETBITS_COMMAND:
				GPIO_SetBits(queue_command.GPIO,queue_command.pin);
				break;
			case RESETBITS_COMMAND:
				GPIO_ResetBits(queue_command.GPIO,queue_command.pin);
				break;
		}
		queue_command = *queue_command.next;
		size--;
	}
}

uint8_t isEmpty (void)
{
	if (size == 0)
	{
		return 1;
	}else {
		return 0;
	}
}
