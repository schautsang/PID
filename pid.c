
#include "stdio.h"
#include "string.h"
#include "math.h"

typedef struct
{  
	double SetPoint;  
	double ActualPoint;  
	double LastError;
	double SumError;
	double Kp, Ki, Kd;   
	double UMAX;  
	double UMIN;  
} PID; 

double PIDCal(PID *pPID, double Point)
{  
	int index = 1; 
	double Error; 
	
	pPID->SetPoint = Point;  
	Error = pPID->SetPoint - pPID->ActualPoint;  
	   
	if (pPID->ActualPoint > pPID->UMAX)  
	{  
		if (fabs(Error) > 200.0)  
		{  
			index = 0;  
		}
		else  
		{  
			index = 1;  
			pPID->SumError += Error;  
		}  
	}  
	else if (pPID->ActualPoint < pPID->UMIN)
	{  
		if (fabs(Error) > 200.0)  
		{  
			index = 0;  
		}  
		else
		{  
			index = 1;
			  
			if (Error > 0)  
			{  
				pPID->SumError += Error; 
			}  
		}  
	}  
	else
	{  
		if (fabs(Error) > 200.0)  
		{  
			index = 0;  
		}  
		else
		{  
			index = 1;  
			pPID->SumError += Error;  
		}  
	}  
	   
	pPID->ActualPoint = pPID->Kp*Error + index*pPID->Ki*pPID->SumError + pPID->Kd*(Error - pPID->LastError); 
	   
	pPID->LastError = Error; 
	  
	return pPID->ActualPoint;  
}  


int main(int argc, char *argv[])
{
	int i;
	
	PID pid;
	memset(&pid, 0, sizeof(pid));
	pid.Kp = 0.2;
	pid.Ki = 0.04;
	pid.Kd = 0.2;
	pid.UMAX = 400.0;
	pid.UMIN = -200.0;
	
	i = 1000;
	while (i--)
	{
		printf("%.4f ", PIDCal(&pid, 245.0));
	}
	
	system("pause");	
	return 0;
}

