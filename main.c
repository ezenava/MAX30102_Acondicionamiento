#include "MKL25Z4.h"
#include "DS18B20.h"
#include "SysTick.h"
#include "TPM.h"
#include "GPIO.h"





float valorfinal[20],promedio;
int alt=0;
	
int main(void) 
{
	
	
	
	//Init_MCU();
	SystemCoreClockUpdate();

	
	SysTick_Init();
	DS18B20_Init();
	TPM_InitOverflow(0,1001,PRESCALER_1);
		
	
	for (;;) 
	{
		if(alt==0){
		tempe = 40000;
			alt=1;
		}
		
		for(int i=0; i < 20;i++){
		
		valorfinal[i] = Obtener_Temp();
		}
				if(tempe == 0 && alt == 1){	

					promedio = 2 +(valorfinal[0]+valorfinal[1]+valorfinal[2]+valorfinal[3]+
								valorfinal[4]+valorfinal[5]+valorfinal[6]+valorfinal[7]+valorfinal[8]+valorfinal[9])/10;
					alt=0;
		}
	}
	return 0;
}

