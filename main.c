#include "Functions.h"
#include <stdio.h>
#include "NIDAQmx.h"
#include <math.h>
#include "mydaq.h"


#define SAMPLE (double)(0.004) // [5ms]
#define FINISH_TIME (double)(10.0) 
#define BUFF (int)(20000)

static double WHOLEPERIOD;
static int PERIODBUFF;


float DAQdatasize[4] = { 0.0 };
int    error = 0;

FILE* pfile;

void main() {

	double initialT = 0.0;
	double presentT = 0.0;
	double endtimeT = 0.0;

	double Time1 = 0.0;
	double Time2 = 0.0;


	int j = 0;
	int i = 0;

	static double storeT[BUFF]; // buffTime
	static double storeD[BUFF];
	static double buffInput[BUFF];
	static double buffOutput[BUFF];
	static double bufChkTaskTime[BUFF];

	initialT = CheckWindowsTime() * 0.001;

	TaskHandle  handle_ao0 = 0;
	TaskHandle  handle_ao1 = 0;
	TaskHandle  handle_ai = 0;
	TaskHandle  handle_po = 0;

	float64      data[1] = { 1.0 };
	float64      read[4] = { 0.0 };
	float64      dc[BUFF] = { 0.0 };
	float64      sine[BUFF] = { 0.0 };
	float64      digital = 0;

	uInt32      digital_ON[1] = { 1 };
	uInt32      digital_OFF[1] = { 0 };
	int32       sign_change = 0;

	WHOLEPERIOD = 0.0;
	PERIODBUFF = 0;


	DAQmxCreateTask("", &handle_ao0);
	DAQmxCreateTask("", &handle_ao1);
	DAQmxCreateTask("", &handle_ai);
	DAQmxCreateTask("", &handle_po);

	CREATE_CHAI(handle_ai, "Dev4/ai0:3");
	CREATE_CHAO(handle_ao0, "Dev4/aoO");
	CREATE_CHAO(handle_ao1, "Dev4/ao1");
	CREATE_CHPO(handle_po, "Dev4/port0/line0");


	DAQmxStartTask(handle_ai);
	DAQmxStartTask(handle_ao0);
	DAQmxStartTask(handle_ao1);
	DAQmxStartTask(handle_po);

	do {

		Time1 = CheckWindowsTime() * 0.001;




		READ_CHAI(handle_ai, read);
		if (digital * read[3] < 0) sign_change++;
		digital = read[3];

		if (sign_change > 10) {
			buffInput[PERIODBUFF] = read[3];
		}

		WRITE_CHAI(handle_ao0, &read[0]);
		WRITE_CHAI(handle_ao1, &read[3]);

		if (read[3] >= 0) {
			if (sign_change > 10) {
				buffOutput[PERIODBUFF] = 1;
				WRITE_CHPO(handle_po, digital_ON);
			}
			else {
				buffOutput[PERIODBUFF] = 0;
				WRITE_CHPO(handle_po, digital_OFF);
			}
		}



		Time2 = CheckWindowsTime() * 0.001;
		bufChkTaskTime[PERIODBUFF] = Time2 - Time1;


		while (1)
		{

			presentT = CheckWindowsTime() * 0.001;
			endtimeT = presentT - initialT - WHOLEPERIOD;

			if (endtimeT >= SAMPLE)
				break;
		}

		WHOLEPERIOD = SAMPLE * ((double)PERIODBUFF + 1.0);

		storeT[PERIODBUFF] = WHOLEPERIOD;
		storeD[PERIODBUFF] = presentT - initialT;


			PERIODBUFF++;

	} while (PERIODBUFF < 5000);


	errno_t err;



	err = fopen_s(&pfile, "C:\\Users\\¹®¼±ºó\\Desktop\\HGU 19-Summer\\1Á¶\\1.1\\bufChkTaskTime.txt", "w");
	for (int i = 0; i <= PERIODBUFF; i++) {
		fprintf(pfile, "%f \n", bufChkTaskTime[i]);
	}
	fclose(pfile);

	DAQmxStopTask(handle_ai);
	DAQmxStopTask(handle_ao0);
	DAQmxStopTask(handle_ao1);
	DAQmxStopTask(handle_po);

	DAQmxClearTask(handle_ai);
	DAQmxClearTask(handle_ao0);
	DAQmxClearTask(handle_ao1);
	DAQmxClearTask(handle_po);

	printf("End of program, press Enter key to quit\n");

		
}

