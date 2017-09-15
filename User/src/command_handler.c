#include "command_handler.h"


#define MAX_P2 650
#define MAX_P4 600
#define MAX_P6 750
#define MAX_P1_P2 240
#define MAX_P3_P4 240
#define MAX_P5_P6 240
#define MIN_P1_P2 180
#define MIN_P3_P4 180
#define MIN_P5_P6 180
#define MAX_Speed 100


double CurrentPosition[6] = {0,0,0,0,0,0};
double Speed[6] = {0,0,0,0,0,0};




//----------------------------------------------------------------------------------
//Функция возвращает манипулятор в начальное положение
//----------------------------------------------------------------------------------
void SetZero (void)
{
	uint8_t FlagZero = 0;
	uint8_t i = 0;
	uint8_t Flag_Start[3] = {1,1,1};
	uint32_t TIME1[3] = {0,0,0};
	uint32_t TIME2[3] = {0,0,0};
	uint32_t TIME3[3] = {0,0,0};
	uint32_t temphelper = 0;
	uint16_t MotorRang[3] = {0,0,0};
	
	Speed[0] = 20;
	Speed[1] = 20;
	Speed[2] = 20;
	Speed[3] = 20;
	Speed[4] = 10;
	Speed[5] = 10;
	
	
	SetZeroFlag (1);
	StartMotor(AXIS_X1, REVERSE, Speed[0]);
	StartMotor(AXIS_X2, REVERSE, Speed[1]);
	//StartMotor(AXIS_Y1, REVERSE, Speed[2]);
	//StartMotor(AXIS_Y2, REVERSE, Speed[3]);
	//StartMotor(AXIS_Z1, REVERSE, Speed[4]);
	//StartMotor(AXIS_Z2, REVERSE, Speed[5]);
	
	
//----------------------------------------------------------------------------------
//Первая фаза, ноль по линейным осям
//----------------------------------------------------------------------------------
	timer_mcsXhun(START_T);
	
	while (FlagZero == 0){
		if(EndStop(AXIS_X2) == 1){
			Flag_Start[0] = 0;
		}
		/*if(EndStop(AXIS_Y2) == 1){
			Flag_Start[1] = 0;
		}
		if(EndStop(AXIS_Z2) == 1){
			Flag_Start[2] = 0;
		}*/
		
		if(Flag_Start[0] == 0){
			StopMotor(AXIS_X1, Speed[0]);
			StopMotor(AXIS_X2, Speed[1]);
			TIME1[0] = timer_mcsXhun(SEE_T);
		}
		/*if(Flag_Start[1] == 0){
			StopMotor(AXIS_Y1, Speed[2]);
			StopMotor(AXIS_Y2, Speed[3]);
			TIME1[1] = timer_mcsXhun(SEE_T);
		}
		if(Flag_Start[2] == 0){
			StopMotor(AXIS_Z1, Speed[4]);
			StopMotor(AXIS_Z2, Speed[5]);
			TIME1[2] = timer_mcsXhun(SEE_T);
		}*/
		if(/*Flag_Start[1] + Flag_Start[2]*/ + Flag_Start[0] == 0){
			FlagZero = 1;
		}
		
	}
	timer_mcsXhun(STOP_T);
	
//----------------------------------------------------------------------------------
//Вторая  фаза, ноль по угловым осям
//----------------------------------------------------------------------------------
	FlagZero = 0;
	StartMotor(AXIS_X1, FORWARD, Speed[0]);
	StartMotor(AXIS_X2,FORWARD, Speed[1]);
	//StartMotor(AXIS_Y1, FORWARD, Speed[2]);
	//StartMotor(AXIS_Y2, FORWARD, Speed[3]);
	//StartMotor(AXIS_Z1, FORWARD, Speed[4]);
	//StartMotor(AXIS_Z2, FORWARD, Speed[5]);
	
	
	timer_mcsXhun(START_T);
	
	while (FlagZero == 0){
		if(EndStop(AXIS_X1) == 1){
			Flag_Start[0] = 0;
		}
		/*if(EndStop(AXIS_Y1) == 1){
			Flag_Start[1] = 0;
		}
		if(EndStop(AXIS_Z1) == 1){
			Flag_Start[2] = 0;
		}*/
		
		if(Flag_Start[0] == 0){
			StopMotor(AXIS_X1, Speed[0]);
			StopMotor(AXIS_X2, Speed[1]);
			TIME2[0] = timer_mcsXhun(SEE_T);
		}
		/*if(Flag_Start[1] == 0){
			StopMotor(AXIS_Y1, Speed[2]);
			StopMotor(AXIS_Y2, Speed[3]);
			TIME2[1] = timer_mcsXhun(SEE_T);
		}
		if(Flag_Start[2] == 0){
			StopMotor(AXIS_Z1, Speed[4]);
			StopMotor(AXIS_Z2, Speed[5]);
			TIME2[2] = timer_mcsXhun(SEE_T);
		}*/
		if(/*Flag_Start[1] + Flag_Start[2] +*/ Flag_Start[0] == 0){
			FlagZero = 1;
		}
	}
	timer_mcsXhun(STOP_T);
	
	TIME3[0] = (20000 * MAX_P2) / Speed[0] - 2 * TIME1[0] - TIME2[0] - MIN_P1_P2 / Speed[0];
	MotorRang[0] = AXIS_X2;
	//TIME3[1] = (20000 * MAX_P4) / Speed[2] - 2 * TIME1[1] - TIME2[1] - MIN_P3_P4 / Speed[2];	
	//MotorRang[1] = AXIS_Y2;
	//TIME3[2] = (20000 * MAX_P6) / Speed[4] - 2 * TIME1[2] - TIME2[2] - MIN_P5_P6 / Speed[4];
	//MotorRang[2] = AXIS_Z2;
	
	FlagZero = 0;
	
	/*while (FlagZero == 0){
		FlagZero = 1;
		for ( i =0 ; i < 2; ++i)
		{
			if ( TIME3[i] > TIME3[i + 1]) {
				temphelper = TIME3[i];
				TIME3[i] = TIME3[i + 1];
				TIME3[i + 1] = temphelper;
				temphelper = MotorRang[i];
				MotorRang[i] = MotorRang[i + 1];
				MotorRang[i + 1] = temphelper;
				if (MotorRang[i] == AXIS_Z2 ) {
					Speed[i] = 10;
				} else {
					Speed[i] = 20;
				}
				FlagZero = 0; // на очередной итерации была произведена перестановка элементов
			}				
		}		
	}*/
	
	StartMotor(AXIS_X2,FORWARD, Speed[1]);
	//StartMotor(AXIS_Y2,FORWARD, Speed[3]);
	//StartMotor(AXIS_Z2,FORWARD, Speed[5]);
	delay_mcsXhun(TIME3[0]);
	StopMotor(MotorRang[0], Speed [0]);
	//delay_mcsXhun(TIME3[1] - TIME3[0]);
	//StopMotor(MotorRang[1], Speed[1]);
	//delay_mcsXhun(TIME3[2] - TIME3[1]);
	//StopMotor(MotorRang[2], Speed[2]);
	
	for ( i = 0; i < 6; ++i){
		CurrentPosition[i] = 0;
		Speed[i] = 0;
	}

	SetZeroFlag (1);
}



//----------------------------------------------------------------------------------
//Функция передвигает манипулятор в заданное положение с заданной скоростью
//----------------------------------------------------------------------------------
void GoToPosition (double* NewPosition, double* NewSpeed)
{
	//uint32_t Time[6] = {0,0,0,0,0,0};
	uint8_t i = 0;
	//double delta[6] = {0,0,0,0,0,0};
	
	//Проверка позиции
	if ( NewPosition[0] > NewPosition[1] || NewPosition[1] > MAX_P2 || NewPosition[0] < 0 ){
		return;
	}
		if ( NewPosition[2] > NewPosition[3] || NewPosition[3] > MAX_P4 || NewPosition[2] < 0){
		return;
	}
	if ( NewPosition[4] > NewPosition[5] || NewPosition[5] > MAX_P6 || NewPosition[4] < 0){
		return;
	}
	if ( NewPosition[1] - NewPosition[0] > MAX_P1_P2 ){
		return;
	}
	if ( NewPosition[3] - NewPosition[2] > MAX_P3_P4 ){
		return;
	}
	if ( NewPosition[5] - NewPosition[4] > MAX_P5_P6 ){
		return;
	}
	
	for (i = 6; i < 12; ++i ){
		if ( NewPosition[i]> MAX_Speed ){
			return;
		}
	}
	
	//если нужно придти в 0
	if ( NewPosition[0] + NewPosition[1] + NewPosition[2] + NewPosition[3] + NewPosition[4] + NewPosition[5] == 0 ){
		SetZero();
		return;
	}
	
	/*for (int i = 0; i < 6; ++i ){
		if
	}*/
}
