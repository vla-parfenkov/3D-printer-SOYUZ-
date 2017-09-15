#include "inverse_task.h"


//-------------------------------
//Решение обратной задачи
//-------------------------------
	struct CGenCoordinats Inversetask(double X, double Y,double Z,double PHI, double THETTA,double PSI){
//-------------------------------
//Обощенные координаты
//-------------------------------
struct CGenCoordinats Q;

		
		
//-------------------------------
//Считаем косинусы и синусы
//-------------------------------		
		
	const double CPHI =	cos(PHI);
	const double SPHI = sin(PHI);
	const double CTHETTA = cos(THETTA);
	const double STHETTA = 	sin(THETTA);
	const double CPSI = cos(PSI);
	const double SPSI = sin(PSI);	
		
		
		
//-------------------------------
//Инициализация матриц поворота
//-------------------------------
		double rotZ[3][3]= {0,0,0,0,0,0,0,0,0};
		double rotY[3][3] = {0,0,0,0,0,0,0,0,0};
		double rotX[3][3] = {0,0,0,0,0,0,0,0,0};
    double TEMPM[3][3] = {0,0,0,0,0,0,0,0,0};//матрица для промежуточных решений
    double rotation [3][3] = {0,0,0,0,0,0,0,0,0};	//общая матрица поворота	
//-------------------------------
//задание координат сферических шарниров
//-------------------------------													
													
	double SJOIN1[3][1] = {0,-32,-32};	
  double SJOIN2[3][1] = {0,-32,32};	
  double SJOIN3[3][1] = {-32,0,32};	
  double SJOIN4[3][1] = {32,0,32};	
  double SJOIN5[3][1] = {-32,-32,0};	
	double SJOIN6[3][1] = {-32,32,0};
  

	double TRANS[3][1];//вектор переноса
  TRANS [0][0] = X;
	TRANS [1][0] = Y;
	TRANS [2][0] = Z;	
		
//-------------------------------
//Заполнение матриц поворота
//-------------------------------
		rotZ[1][1]=rotZ[0][0] = CPHI;
    rotZ[1][0]=SPHI;
    rotZ[0][1] = -SPHI;
    rotZ[2][2] = 1; 


													
		rotY[2][2]=rotY[0][0] = CTHETTA;
		rotY[0][2] = STHETTA;
		rotY[2][0] = -STHETTA;
    rotY[1][1] = 1;
													
		
			
    rotX[0][0] = 1;
    rotX[1][1] = rotX[2][2] = CPSI;
    rotX[1][2] = 	-SPSI;
    rotX[2][1] = 	SPSI;												
		
		
//-------------------------------
//Нахождение общей матрицы поворота
//-------------------------------	
		
		Matrixmult (&rotZ[0][0],&rotY[0][0],&TEMPM[0][0],3,3,3);
		Matrixmult (&TEMPM[0][0],&rotX[0][0],&rotation[0][0],3,3,3);
													




//-------------------------------
//Нaхождение обобщенных координат
//-------------------------------


Q.P1 = SolveGenCoor (&rotation[0][0], &SJOIN1[0][0],&TRANS[0][0], 0);
Q.P2 = SolveGenCoor (&rotation[0][0], &SJOIN2[0][0],&TRANS[0][0], 0);
Q.P3 = SolveGenCoor (&rotation[0][0], &SJOIN3[0][0],&TRANS[0][0], 1);
Q.P4 = SolveGenCoor (&rotation[0][0], &SJOIN4[0][0],&TRANS[0][0], 1);	 	 
Q.P5 = SolveGenCoor (&rotation[0][0], &SJOIN5[0][0],&TRANS[0][0], 2);
Q.P6 = SolveGenCoor (&rotation[0][0], &SJOIN6[0][0],&TRANS[0][0], 2);
	 
	 return Q;
	 
	}
	
//-------------------------------
//Функция перемножения матриц
//-------------------------------
void Matrixmult (double* MATRIXA, double* MATRIXB, double* MATRIXC,int line,int column, int dimen){
	int r;
	int i;
	int j;
	

													
		 for(i=0;i<line;i++){
			for (j=0;j<column;j++){
				for (r=0; r<dimen;r++){	
		     *(MATRIXC+i*column+j)=*(MATRIXC+i*column+j)+*(MATRIXA+i*dimen+r)* *(MATRIXB+r*column+j);
			}
		 }
		 }
	
}

//-------------------------------
//Функция сложения матриц
//-------------------------------

void Matrixsumm (double* MATRIX1, double* MATRIX2, double* MATRIXRES,int line,int column){
	
	int i;
	int j;
	
											
		 for(i=0;i<line;i++){
			for (j=0;j<column;j++){
		     *(MATRIXRES+i*column+j)=*(MATRIX1+i*column+j)+*(MATRIX2+i*column+j);
			}
		 }
	
		}

//---------------------------------------------
//Функция нaхождения обобщенной координаты
//---------------------------------------------

		double SolveGenCoor (double* MATRIXROT, double* CorJoin,double* CorLocSys, int component)		
		{
			
			double TEMPV[3][1] = {0,0,0}; //вектор для промежуточных решений	
			
			
	 Matrixmult (MATRIXROT,CorJoin,&TEMPV[0][0],3,1,3);
	 Matrixsumm (CorLocSys, &TEMPV[0][0], &TEMPV[0][0],3,1);
	 
	 return TEMPV[component][0];
	 
		}

		

		