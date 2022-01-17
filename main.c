
#include "Digital_Control.h"



void main(void)

{

		//---------------------------------------------------------------

		// Initialization

		//---------------------------------------------------------------

		Simul_Time = 0.0;
		Simul_count = 0;
		sum = 0; // used in obtaining Gyro_offset

		/*Set DAQ*/
		set_DAQ();
		

		/*Obtain Gyro Offset*/
		Gyro_offset();
		printf("Gyro_Offset = %.2lf\n", gyro_offset);


		/*Motor Position Initialize*/

		Position_Init();
		
		printf("Voltage of Potentio = %.2lf\n", Vpot);
		printf("If you want to start, press any character~\n");
		

		getchar();

		DAQ_digital_write(1);

		Start_Time = CheckWindowsTime()*0.001;

		do {

			Time1 = CheckWindowsTime()*0.001; // Time for checking Task Time
			

			//---------------------------------------------------------------

			// import Data 

			//---------------------------------------------------------------

			DAQ_read();
			

			//---------------------------------------------------------------

			// Digital Controller


			//---------------------------------------------------------------

			Tracking_Controller();


			err_cur = Win - Wout; 

	
			PID_Controller(err_cur);


		
		
			
			//---------------------------------------------------------------

			// Export Data 

			//---------------------------------------------------------------
		
			
			Linearization(); 

			DAQ_analog_write(Vss);
		
	

			//---------------------------------------------------------------

			// Idle Time 

			//---------------------------------------------------------------
			Time2 = CheckWindowsTime()*0.001; // Time for checking Task Time
		

			while (1)

			{

				Current_Time = CheckWindowsTime()*0.001;
				Processing_Time = Current_Time - Start_Time - Simul_Time;




				if (Processing_Time >= SAMPLING_TIME)  break;

			}


			Simul_Time = SAMPLING_TIME * ((double)(Simul_count)+1.0);
			//printf("Simul_Time = %lf  \n", Simul_Time);



			Simul_count++;



		} while (Simul_Time <= FINISH_TIME);

		/*Clear DAQ*/
		
		DAQ_digital_write(0);
		clear_DAQ();

	
		
		/*Record Data*/
		Recording_Data();


		printf("End");
		
		getchar();

}