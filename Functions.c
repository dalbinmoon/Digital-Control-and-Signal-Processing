#ifndef SOURCE_USER_DEFINED_FUNCTION
#define SOURCE_USER_DEFINED_FUNCTION

//-------------------------------------------

#include "Functions.h"
#include <math.h>
#include <stdio.h>
#include <conio.h>

#define PI               3.14159265359

/* Linearization */
#define AP  (double)( 0.1958) 
#define BP  (double)( 2.7204) 
#define AN  (double)( 0.1917) 
#define BN  (double)( 2.2692) 

//------------------------
double CheckWindowsTime(void)
{
	LARGE_INTEGER liCount, liFreq;

	QueryPerformanceCounter(&liCount);
	QueryPerformanceFrequency(&liFreq);

	return ((liCount.QuadPart / ((double)(liFreq.QuadPart)))*1000.0);
}
extern void Triangular_Input(double freq) // Only available at even frequency such as 0.2, 0.4 ... (but 0.1Hz is available)
{
	double change_point = 1.0 / 2.0 / freq;

	if (Simul_Time >= change_point && ((int)(Simul_Time * 1000.0) % (int)(change_point*1000) == 0)) N++;
	
	if (N % 2 == 0) Vcmd = -(5/change_point)*Simul_Time + (2.5 + 5 * N);
	if (N % 2 == 1) Vcmd = (5 / change_point)*Simul_Time - (2.5 + 5 * N);

}
extern void Linearization(void)
{
	if (Vcmd <= -0.1 && Vcmd <= 0.1) Vss = 2.5;

	if (Vcmd > 0.1 ) Vss = AP * Vcmd + BP;
	if (Vcmd < -0.1) Vss = AN * Vcmd + BN;
}
extern void Recording_Data(void)
{
	
	/*File Handling*/
	FILE * pFile;

	/*Data Recording into file*/

	errno_t err;
	char file_path[200];
	sprintf_s(file_path, sizeof(char) * 200, "D:\\2019_summer\\Digital_Control\\Final\\OuterLoop_Sensor\\Step_Response\\Tracking_step_response8.txt");
	


	err = fopen_s(&pFile, file_path, "w");
	for (int i = 0; i < Simul_count; i++) {

		fprintf(pFile, "%8.6f\t%8.6f\n", bufInput[i], bufOutput[i]);
		//fprintf(pFile, "%8.6f\t\t%8.6f\t\t%8.6f\t\t%8.6f\t\t%8.6f\t\t%8.6f\t\t%8.6f\t\t%8.6f\n", bufOutput[i],bufOutput2[i], bufOutput3[i], bufOutput4[i], bufOutput5[i], bufOutput6[i], bufOutput7[i]);
		//fprintf(pFile, "%8.6f\t\t%8.6f\t\t%8.6f\t\t%8.6f\n", bufOutput[i], bufOutput2[i], bufOutput3[i], bufOutput4[i]);
		//fprintf(pFile, "%8.6f\n", bufOutput[i]);
	}

	fclose(pFile);
}
extern void Reading_Data(void)
{
	FILE * pFile;
	errno_t err;
	char file_path[200];
	sprintf_s(file_path, sizeof(char) * 200, "D:\\2019_summer\\Digital_Control\\Lab\\Lab2\\node1.txt");
	err = fopen_s(&pFile, file_path, "r");
	for (int i = 0; i < 2500; i++) {
		fscanf_s(pFile, "%lf", &bufInput[i]);
	}
	fclose(pFile);
}
extern void Gyro_offset(void)
{
	for (int i = 0; i < 1000; i++) {
		DAQ_read(); // 반드시 있어야 함
		gyro_raw[i] = read[0];
		sum += gyro_raw[i];
	}
	gyro_offset = sum / 1000;
	
}
extern void Modeling(double freq)
{
		Vcmd = 1.5*sin(2 * PI*freq*Simul_Time);
		bufInput[Simul_count] = Vcmd;
}
extern void LPF_N2(void)
{
	bufOutput[Simul_count] = (b[1] - b[0] * a[1])*P[1] + (b[2] - b[0] * a[2])*P[0] + b[0] * input[Simul_count];
	C[0] = P[1];
	C[1] = -a[2] * P[0] - a[1] * P[1] + input[Simul_count];

	P[0] = C[0];
	P[1] = C[1];
}
extern void Step(void)
{
	if (Simul_Time <= 0.25*FINISH_TIME)
		Vcmd = 2.5;
	else if (Simul_Time > 0.25*FINISH_TIME && Simul_Time <= 0.5*FINISH_TIME)
		Vcmd = -2.5;
	else if (Simul_Time > 0.5*FINISH_TIME && Simul_Time <= 0.75*FINISH_TIME)
		Vcmd = 2.5;
	else
		Vcmd = -2.5;

	

	bufInput[Simul_count] = Vcmd;
	//printf("%f\n", Vcmd);
}

extern void Ramp(void)
{
	if (flag == 1) { // 맨 처음의 경우에 초기값 설정
		Vcmd = -2.5;
		Ramp_check = 0;
		resolution=0.01;
		flag = 0;
	}

	if (Ramp_check == 0) {
		Vcmd += resolution;
	}
	else {
		Vcmd = Vcmd - 5;
	}

	if (Vcmd >= 2.5) {
		Ramp_check = 1;
	}
	if (Vcmd <2.5) {
		Ramp_check = 0;
	}

}

void moving_gimbal(void)
{
	int key;
	//while (1) {
		if (_kbhit()) {
			key = _getch();
			if (key == 224 || key == 0) {
				key = _getch();
				switch (key) {
				case 75: //printf("← \n");
					Vcmd = 2.5;
					
					break;
				case 77:// printf("→ \n");
					Vcmd = -2.5;
					
					break;
				default:
					Vcmd = 0;
					
					break;
				}
				DAQ_digital_write(1);
				Linearization();
				DAQ_analog_write(Vss);
				Sleep(10);
				DAQ_digital_write(0);
			}

		}
	//}
}
extern void Position_Init(void)
{
	
	DAQ_digital_write(1);
	
	while (1) {
		
		DAQ_read(); // 반드시 있어야 함.
		
		if(Vpot< 2.495)Vss = 3.0;
		if (Vpot > 2.505)Vss = 2.0;
		DAQ_analog_write(Vss);
		
		if (Vpot >= 2.495 && Vpot <= 2.505) {
			DAQ_digital_write(0);
			Vss = 2.5;
			DAQ_analog_write(Vss);
			break;
		}
		if (Vpot >= 2.495 && Vpot <= 2.505)
			break;
	}
	
}
#endif