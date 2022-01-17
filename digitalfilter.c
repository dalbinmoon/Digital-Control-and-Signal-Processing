#include "digitalfilter.h"


double digitalfilter(double* Num, double* Den, double* Cstate, double* Pstate, int N, double input)
{
	//---------------------------------------------------------------
	// Digital Filter
	//---------------------------------------------------------------
	// INPUT   input : reference input
	//         Num   : numerator of a transfer function in matlab_b
	//         Den   : denominator of a transfer fnction in matlab_a
	//         Pstate: Xk-1 Past state vector
	//         N     : order of a transfer function
	//-----------------------------------------------------------------------
	// OUPUT   output  : filtered output 
	//         Cstate  : Xk
	//-----------------------------------------------------------------------
	// e.g order is reverse
	//-----------------------------------------------------------------------

	if (Den[N] != 1.0) printf("Error in DF: Check the filter coefficient "); //digital transfer function�� �´� �� Ȯ���Ѵ�

	Cstate[N - 1] = input; //Cstate�� �ʱ�ȭ ��Ų��
	output = Num[N] * input; //output ������ �� ������ b0*input ���� ����д�

	for (int i = 0; i < N; i++)
	{
		if (i < N - 1)
		
		Cstate[i] = Pstate[i + 1]; 

		Cstate[N - 1] += (-1.0 * Den[i] * Pstate[i]);
		output += (Num[i] - Num[N] * Den[i]) * Pstate[i];

	}
	for (int i = 0; i < N; i++) Pstate[i] = Cstate[i];

	return output;
}