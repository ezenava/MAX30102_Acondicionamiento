/*
 * -----------------------
 * TPM.h 
 * -----------------------
 * 
 * Materias:
 * Sistemas Electr�nicos Embebidos
 * 
 * 6to A�o T�cnico en Electr�nica
 * Colegio Pio IX
 * 
 * Revisi�n 1
 * A�o 2023
 * 
 * Profesores: Mat�as Marfisi, Tom�s Zuran, Federico Diograzia
 * 
 */

#ifndef _TPM_H
#define _TPM_H

#include "MKL25Z4.h"
#include "GPIO.h"

#define CLOCK_FREQ 		48000000

/*
 * Enum para bits PS TPMx_SC control clock prescaler (pag. 552 Reference Manual)
 */
enum{
	PRESCALER_1 = 0,
	PRESCALER_2,
	PRESCALER_4,
	PRESCALER_8,
	PRESCALER_16,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128
};

extern volatile unsigned int tiempo_tpm,cont,tempe,tiempo_promedio;

void TPM_InitOverflow(uint8_t tpm, uint32_t freq, uint8_t prescaler);

#endif