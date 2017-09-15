#include "mcu_ini.h"


//-----------------------------
//Настройка портов ввода/вывода
//------------------------------



void GPIO_ini (GPIO_TypeDef* GPIOPORT, uint16_t Pin,uint8_t GMode)
{
	GPIO_InitTypeDef GPIO_INITPORT; //структура для настройки порта
	
	if(GMode == OUT)
	{
	GPIO_INITPORT.GPIO_Pin = Pin; //включение выходов
	GPIO_INITPORT.GPIO_Mode = GPIO_Mode_OUT; //настройка на AF режим ножки 
	GPIO_INITPORT.GPIO_Speed = GPIO_Speed_2MHz; //скорость 
	GPIO_INITPORT.GPIO_OType = GPIO_OType_PP; //подтягивание земли к питанию
	GPIO_INITPORT.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  }
	if(GMode == IN)
	{
		GPIO_INITPORT.GPIO_Pin = Pin; //включение входов
	GPIO_INITPORT.GPIO_Mode = GPIO_Mode_IN; //настройка  режим ножки 
	GPIO_INITPORT.GPIO_Speed = GPIO_Speed_2MHz; //скорость 
	GPIO_INITPORT.GPIO_OType = GPIO_OType_PP; //подтягивание земли к питанию
	GPIO_INITPORT.GPIO_PuPd = GPIO_PuPd_DOWN;
	}
	if(GMode == AF){
		
		GPIO_INITPORT.GPIO_Pin = Pin; //включение выходов
	GPIO_INITPORT.GPIO_Mode = GPIO_Mode_AF; //настройка на AF режим ножки 
	GPIO_INITPORT.GPIO_Speed = GPIO_Speed_100MHz; //скорость 
	GPIO_INITPORT.GPIO_OType = GPIO_OType_PP; //подтягивание земли к питанию
	GPIO_INITPORT.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	}
	if(GMode == AN ){	
	GPIO_INITPORT.GPIO_Pin = Pin; //включение выходов
	GPIO_INITPORT.GPIO_Mode = GPIO_Mode_AN; //настройка на аналоговый режим ножки 
	GPIO_INITPORT.GPIO_Speed = GPIO_Speed_2MHz; //скорость 
	GPIO_INITPORT.GPIO_OType = GPIO_OType_PP; //подтягивание земли к питанию
	GPIO_INITPORT.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	}
	
	GPIO_Init(GPIOPORT, &GPIO_INITPORT);
	
}





	//-----------------
	//настройка таймера
	//------------------
	
void timer_ini (TIM_TypeDef* TIMx, uint16_t Period, uint16_t Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_timer1;//структура отвечающая за настройку таймера
	
	
	TIM_timer1.TIM_Prescaler = Prescaler; //Предделитель 
	TIM_timer1.TIM_CounterMode = TIM_CounterMode_Up; //счет вверх
	TIM_timer1.TIM_Period = Period ; //период таймера 
	TIM_timer1.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIMx, &TIM_timer1); //функция настройки таймера
	

}




