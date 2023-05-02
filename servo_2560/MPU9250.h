

void DataUp();
void InitMPU9250();
void IMU_OUT();


typedef struct IMU
{
	int A_Xout;
	int A_Yout;
	int A_Zout;
	
	int G_Xout;
	int G_Yout;
	int G_Zout;
}IMU;
#include "MPU9250.c"