
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "MKL25Z4.h"

#define CLOCK_FREQ 48000000

#define SYSTICK_ENABLE 		(1 << 0)
#define SYSTICK_TICKINT 	(1 << 1)
#define SYSTICK_CLKSOURCE	(1 << 2)

/*
 * El modificador extern nos permite acceder a una variable definida en este archivo, en cualquier otro.
 * En este ejemplo, se utilizará en main.c para controlar el estado del LED rojo.
 */
extern uint32_t tiempo;

void SysTick_Init(void); // Tiempo en ms deseado para interrupcion

#endif
