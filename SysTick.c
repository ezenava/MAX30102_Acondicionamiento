#include "MKL25Z4.h"
#include "SysTick.h"


uint32_t tiempo =0;


void SysTick_Init(void)
{
		SysTick->CTRL = 0x7;
		SysTick->VAL = 47999;
}

void SysTick_Handler() 
{
	if (tiempo > 0)
		tiempo--;
}
