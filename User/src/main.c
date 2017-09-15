#include "main.h"

uint8_t anti_drebezg (GPIO_TypeDef* GPIOPORT, uint16_t Pin, uint8_t count);

uint32_t delay_count = 0;//счетчик задержки
uint8_t button_count = 0;//счетчик кнопки
uint8_t button_flag = 0;//флаг кнопки
uint8_t flag_zero = 0; //флаг операции установки нуля
uint16_t GPIO_count[6] = {0,0,0,0,0,0};
uint8_t GPIO_flag[6] = {0,0,0,0,0,0};
uint8_t DIR[6] = {0,0,0,0,0,0};
uint16_t Data_ADC[6] = {0,0,0,0,0,0};
uint8_t flag = 0;
uint32_t time_count = 0;
uint8_t SystikCount = 0;

//---------------------
//Функция прерывания
//---------------------
void SysTick_Handler(void)
{
	if(delay_count > 0){
		delay_count--;
	}
	
	time_count ++;
	
	if( BUTTON_READ() == 1){
		if(button_count<5)//5 для защиты от дребезга
			{
			button_count++;
		} else {
				button_flag=1;
			}	
	} else {
			if(button_count>0) {
			button_count--;
		} else {
				button_flag=0;
			}	
	}
	
	
	/*if (SystikCount < 100) {
		SystikCount++;
	} else {
		ADC_SoftwareStartInjectedConv(ADC1);
		ADC_SoftwareStartInjectedConv(ADC2);
		ADC_SoftwareStartInjectedConv(ADC3);
			SystikCount = 0;
	}*/
	
		GPIO_flag[0] = anti_drebezg (GPIOC, GPIO_Pin_1, 0);
		GPIO_flag[1] = anti_drebezg (GPIOC, GPIO_Pin_2,1);
		GPIO_flag[2] = anti_drebezg (GPIOC, GPIO_Pin_3,2);
		GPIO_flag[3] = anti_drebezg (GPIOC, GPIO_Pin_4,3);
		GPIO_flag[4] = anti_drebezg (GPIOC, GPIO_Pin_5,4);
		GPIO_flag[5] = anti_drebezg (GPIOC, GPIO_Pin_6,5);

	
	flag = 0;
	if ( flag_zero == 0 ) {
			/*if((GPIO_flag[0] == 1) || (GPIO_flag[1] == 1)){
				GPIO_SetBits(GPIOE, AXIS_X1);
				GPIO_SetBits(GPIOE, AXIS_X2);
				flag = 1;
			} 
			if((GPIO_flag[2] == 1) || (GPIO_flag[3] == 1) ){
				GPIO_SetBits(GPIOE, AXIS_Y1);
				GPIO_SetBits(GPIOE, AXIS_Y2);
				flag = 1;
			} 
			if((GPIO_flag[4] == 1) || (GPIO_flag[5] == 1) ){
				GPIO_SetBits(GPIOE, AXIS_Z1);
				GPIO_SetBits(GPIOE, AXIS_Z2);
				
				flag = 1;
			} */
		}
	
}

/*void ADC_IRQHandler (void)
{
	if ( ADC_GetITStatus (ADC1, ADC_IT_JEOC) == SET)
	{
		ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
		
		Data_ADC[0] = (uint16_t) ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
		Data_ADC[1] = (uint16_t) ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
	}
	if ( ADC_GetITStatus (ADC2, ADC_IT_JEOC) == SET)
	{
		ADC_ClearITPendingBit(ADC2, ADC_IT_JEOC);
		
		Data_ADC[2] = (uint16_t) ADC_GetInjectedConversionValue(ADC2, ADC_InjectedChannel_1);
		Data_ADC[3] = (uint16_t) ADC_GetInjectedConversionValue(ADC2, ADC_InjectedChannel_2);
	}
		if ( ADC_GetITStatus (ADC3, ADC_IT_JEOC) == SET)
	{
		ADC_ClearITPendingBit(ADC3, ADC_IT_JEOC);
		
		Data_ADC[4] = (uint16_t) ADC_GetInjectedConversionValue(ADC3, ADC_InjectedChannel_1);
		Data_ADC[5] = (uint16_t) ADC_GetInjectedConversionValue(ADC3, ADC_InjectedChannel_2);
	}
	
}*/


uint8_t anti_drebezg (GPIO_TypeDef* GPIOPORT, uint16_t Pin, uint8_t count)
{
		if( GPIO_ReadInputDataBit(GPIOPORT, Pin) == 1){
			if(GPIO_count[count] < 	200)//20 мс  для защиты от дребезга
			{
				GPIO_count[count]++;	
			} else {
				return 1;
			}	
	} else {
			if(GPIO_count[count] > 200) {
			GPIO_count[count]--;
		} else {
				return 0;
			}	
	}
	return 0;
}


//---------------------
//Функция задержки
//---------------------
void delay_mcsXhun(uint32_t delay_temp)
{
	delay_count = delay_temp;
	
	while(delay_count){};
	
}
	

int main(void)
{
	
	
	/*uint8_t ENDSTOP1 = 0;
	uint8_t ENDSTOP2 = 0;*/
	//тест 
	uint8_t flagTest = 0;
	//для разгона
	//uint32_t CountPulse = 1; // текущая дискрета ускорения
	//uint16_t CountFrequency = START_FREQ; // текущая частота
	//float gSnum = START_FREQ - (ACCELERATION * TAKT_CONF)/(2 * START_FREQ); // считаем параметр старта
	//uint32_t Time = 10000 / START_FREQ; //время импульса в мс
	//float CountCoef = 0; 
	//uint16_t StartFrequency = START_FREQ;


	SystemCoreClockUpdate(); //посчитать SystemCoreClock
	SysTick_Config(SystemCoreClock/10000);//генерация каждую десятую миллисекунду
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //Включение тактирования 4 таймера
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //Включение тактирования 2 таймера
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   //Тактирование порта D
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //Тактирование порта B
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//Тактирование порта A
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);   //Тактирование порта E
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //Тактирование порта C
	
	//------------------------------------
	//настройка портов на различные режимы
	//------------------------------------
	GPIO_ini ( GPIOD, AXIS_X1| AXIS_X2| AXIS_Y1 |AXIS_Y2|AXIS_Z1| AXIS_Z2|GPIO_Pin_12|GPIO_Pin_13, OUT); //порт D на выход 
	GPIO_ini ( GPIOA, GPIO_Pin_0,IN); //порт A на вход
	GPIO_ini ( GPIOC, GPIO_Pin_6|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5, IN); //порт C на вход
	GPIO_ini ( GPIOB, AXIS_X1| AXIS_X2| AXIS_Y1 |AXIS_Y2|AXIS_Z1|AXIS_Z2,AF);//порт B на AF режим
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6 , GPIO_AF_TIM4); //настройка AF режима
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7 , GPIO_AF_TIM4); //настройка AF режима
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8 , GPIO_AF_TIM4); //настройка AF режима
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9 , GPIO_AF_TIM4); //настройка AF режима
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10 , GPIO_AF_TIM2); //настройка AF режима
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11 , GPIO_AF_TIM2); //настройка AF режима
	GPIO_ini ( GPIOE, AXIS_X1| AXIS_X2| AXIS_Y1 |AXIS_Y2|AXIS_Z1|AXIS_Z2,OUT); //порт E на выход

	
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	
	
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	//ADC_ini(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
	 
	 
	while( 1 )
	{
		
	 if( button_flag == 1){
		 /*StartMotor (AXIS_Z2, FORWARD, 15);
		StartMotor (AXIS_Z1, FORWARD, 15);
		
		delay_mcsXhun(200000);
		StopMotor( AXIS_Z1, CalcTAKT(20,AXIS_Z1));
		StopMotor( AXIS_Z2, CalcTAKT(20,AXIS_Z2));*/

		StartMotor (AXIS_Y1, REVERSE, 20);
		StartMotor (AXIS_Y2, REVERSE, 20);
		StartMotor (AXIS_X2, REVERSE, 20);
		StartMotor (AXIS_X1, REVERSE, 20);
		delay_mcsXhun(50000);
		 while( flag == 0){
		//StartMotor (AXIS_Z2, FORWARD, 10);
		//StartMotor (AXIS_Z1, FORWARD, 10);
		StartMotor (AXIS_Y1, FORWARD, 20);
		StartMotor (AXIS_Y2, FORWARD, 20);
		StartMotor (AXIS_X2, FORWARD, 20);
		StartMotor (AXIS_X1, FORWARD, 20);
			 
		 delay_mcsXhun(100000);
		//StartMotor (AXIS_Z2, REVERSE, 20);
		//StartMotor (AXIS_Z1, REVERSE, 20);
		StartMotor (AXIS_Y1, REVERSE, 20);
		StartMotor (AXIS_Y2, REVERSE, 20);
		StartMotor (AXIS_X2, REVERSE, 20);
		StartMotor (AXIS_X1, REVERSE, 20);
		
		delay_mcsXhun(100000);
		StopMotor( AXIS_X2, CalcTAKT(20,AXIS_X2));
		StopMotor( AXIS_X1, CalcTAKT(20,AXIS_X1));
		StopMotor( AXIS_Y1, CalcTAKT(20,AXIS_Y1));
		StopMotor( AXIS_Y2, CalcTAKT(20,AXIS_Y2));
			 delay_mcsXhun(20000);
		StartMotor (AXIS_Z2, flagTest, 10);
		StartMotor (AXIS_Z1, flagTest, 10);
		
		delay_mcsXhun(300000);
		StopMotor( AXIS_Z1, CalcTAKT(10,AXIS_Z1));
		StopMotor( AXIS_Z2, CalcTAKT(10,AXIS_Z2));
		delay_mcsXhun(20000);
		if(flagTest == 0)
		{
			flagTest = 1;
		} else {
			flagTest = 0;
		}
		}
 }	
	}
}


Bool EndStop (uint16_t MotorPin)
{
	switch ( MotorPin ) {
		case AXIS_X1:
			if (GPIO_flag[0] == 1) {
				return 1;
			} else {
				break;
			}
		case AXIS_X2:
			if (GPIO_flag[1] == 1) {
				return 1;
			} else {
				break;
			}
		case AXIS_Y1:
			if (GPIO_flag[2] == 1) {
				return 1;
			} else {
				break;
			}
		case AXIS_Y2:
			if (GPIO_flag[3] == 1) {
				return 1;
			} else {
				break;
			}
		case AXIS_Z1:
			if (GPIO_flag[4] == 1) {
				return 1;
			} else {
				break;
			}
		case AXIS_Z2:
			if (GPIO_flag[5] == 1) {
				return 1;
			} else {
				break;
			}
	}
	return 0;
}


uint32_t timer_mcsXhun(uint8_t mode)
{
	if (mode == START_T){
		time_count = 0;
		return 0;
	} else {
		return  time_count;
	}
}

void SetZeroFlag (uint8_t flag)
{
	flag_zero = flag;
}


