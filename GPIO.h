/*
 * -----------------------
 * GPIO.h (para el MKL25Z)
 * -----------------------
 * 
 * Materias:
 * Taller - Sistemas Electrónicos Digitales
 * Programación de Dispositivos Electrónicos
 * 
 * 5to Año Técnico en Electrónica
 * Colegio Pio IX
 * 
 * Revisión 3
 * Año 2022
 * 
 * Profesores: Tomás Zuran, Héctor Albano, Diego Codevilla
 * 
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "MKL25Z4.h"

#define SALIDA		1
#define ENTRADA		0


//Le indica al pin que lo voy a utilizar como GPIO
extern void GPIO_Init(GPIO_MemMapPtr portDir, uint8_t pin);

//Configura al pin como entrada o salida (0 = Entrada, 1 = Salida, ver defines en este archivo)
extern void GPIO_Mode(GPIO_MemMapPtr port, uint8_t pin, uint8_t mode);

//Setea el valor del pin en 0 o en 1, si el mismo fue previamente configurado como SALIDA.
extern void GPIO_Set(GPIO_MemMapPtr port, uint8_t pin, uint8_t value);

//Lee el valor que actualmente tiene un pin. El mismo tuvo que ser previamente configurado como entrada.
extern uint8_t GPIO_Read(GPIO_MemMapPtr port, uint8_t pin);

//Habilita la resistencia de pull UP interna del pin, si el mismo fue previamente configurado como entrada.
extern void GPIO_EnablePullUpResistor(GPIO_MemMapPtr portDir, uint8_t pin);

//Deshabilita la resistencia de pull (sea up o down) interna del pin.
extern void GPIO_DisablePullResistor(GPIO_MemMapPtr portDir, uint8_t pin);

#endif /* GPIO_H_ */
