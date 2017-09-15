#ifndef INVERSE_TASK_H
#define INVERSE_TASK_H

#include "stm32f4xx.h"
#include <math.h>

//-------------------------------
//Структура обобщенных координат
//-------------------------------
struct CGenCoordinats {
	double P1;
	double P2;
	double P3;
	double P4;
	double P5;
	double P6;
};



struct CGenCoordinats Inversetask(double X, double Y,double Z,double PHI, double THETTA,double PSI);
void Matrixmult (double* MATRIXA, double* MATRIXB, double* MATRIXC,int line,int column, int dimen);
void Matrixsumm (double* MATRIX1, double* MATRIX2, double* MATRIXRES,int line,int column);
double SolveGenCoor (double* MATRIXROT, double* CorJoin,double* CorLocSys, int component);


#endif 



