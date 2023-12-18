#include "DS18B20.h"
#include "MKL25Z4.h"
#include "SysTick.h"
#include "TPM.h"
#include "GPIO.h"

int16_t lectura = 0;

void DS18B20_Init(void)
	{

	GPIO_Init(GPIOB,11);
	GPIO_Mode(GPIOB,11,1);
		// Pin de Vcc
	//PORTE_PCR2 = PORT_PCR_MUX(1);
	//Pin de datos
	PORTB_PCR11 = PORT_PCR_MUX(1);

}

//int alt=0;


void mandarComando(uint8_t cmd) 
{
	int j, i;

	for (j = 0; j < 8; j++) 
	{
		GPIOB_PDDR |= 1 << 11;
		// Cuanto Toff tengo (~100us para un 0, ~1us para un 1)
		GPIOB_PDOR &= ~(1 << 11);
		for (i = 0; i < (cmd & (1 << j) ? 1 : 200); i++)
			__ASM volatile ("nop");

		GPIOB_PDDR &= ~(1 << 11);

		while ((GPIOB_PDIR & 1 << 11) == 0)
			;

		// Ton tiene que ser mayor a 1us
		for (i = 0; i < 300; i++)
			__ASM volatile ("nop");
	}

	for (i = 0; i < 100; i++)
		__ASM volatile ("nop");
}

void iniciarConversion() 
{
	uint32_t i, j;

	__ASM volatile ("cpsid i");
	GPIOB_PDDR |= 1 << 11;
	GPIOB_PCOR |= 1 << 11;

	// Aproximadamente 300ns + 271 ns por ciclo del for
	for (i = 0; i < 3000; i++)
		__ASM volatile ("nop");

	GPIOB_PDDR &= ~(1 << 11);

	for (i = 0; i < 5; i++)
		__ASM volatile ("nop");

	while ((GPIOB_PDIR & (1 << 11)) != 0);
	
	while ((GPIOB_PDIR & (1 << 11)) == 0);

	for (i = 0; i < 2000; i++)
		__ASM
		volatile ("nop");

	mandarComando(0xCC);

	mandarComando(0x44);

	__ASM volatile ("cpsie i");

}

uint16_t iniciarLectura() 
{
	int i, j;
	
	int16_t aux = 0;

	for (j = 0; j < 16; j++) {

		GPIOB_PDDR |= 1 << 11;
		GPIOB_PCOR |= 1 << 11;

		__ASM volatile ("nop");

		GPIOB_PDDR &= ~(1 << 11);

		for (i = 0; i < 8; i++)
			__ASM volatile ("nop");

		if (GPIOB_PDIR & 1 << 11) {
			aux |= 1 << j;
		}
		for (i = 0; i < 300; i++)
			__ASM volatile ("nop");
	}

	return aux;
}

uint16_t lecturaTemperatura() 
{
	uint32_t i;

	__ASM volatile ("cpsid i");
	GPIOB_PDDR |= 1 << 11;
	GPIOB_PCOR |= 1 << 11;

	// Aproximadamente 300ns + 271 ns por ciclo del for
	for (i = 0; i < 3000; i++)
		__ASM volatile ("nop");

	GPIOB_PDDR &= ~(1 << 11);

	while ((GPIOB_PDIR & (1 << 11)) != 0)
		;
	while ((GPIOB_PDIR & (1 << 11)) == 0)
		;

	for (i = 0; i < 3000; i++)
		__ASM
		volatile ("nop");

	mandarComando(0xCC);

	mandarComando(0xBE);

	uint16_t aux = iniciarLectura();

	__ASM volatile ("cpsie i");

	return aux;

}

float Obtener_Temp(void){
			float valorfinal1=0;
	iniciarConversion();
		tiempo = 1;
		while (tiempo > 0);
		
		lectura = lecturaTemperatura();
		valorfinal1 = lectura*0.0625;
		tiempo = 1;
		while (tiempo > 0);
		
	return valorfinal1;
	}

//	
//float Promedio_Temp(void){
// int turno = 0;
//	float Temperatura[10];
//	
//	if(tiempo_tempe == 0 && turno == 0 ){
//	tiempo_tempe = 30;
//	turno = 1;
//	}
//	if(tiempo_tempe == 0 && turno == 1){
//		
//		
//		for(int i=0;i < 10;i++){
//		Temperatura[i] = Obtener_Temp();
//		}
//	}
//	
//		return (Temperatura[0]+Temperatura[1]+Temperatura[2]+Temperatura[3]+Temperatura[4]+Temperatura[5]+Temperatura[6]+Temperatura[7]+Temperatura[8]+Temperatura[9])/10;
//	}
//	
//	
//	