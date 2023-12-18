#include "MKL25Z4.h"

#ifndef DS18B20_H_
#define DS18B20_H_


void DS18B20_Init(void);
void mandarComando(uint8_t cmd);
void iniciarConversion();
uint16_t iniciarLectura();
uint16_t lecturaTemperatura();

float Obtener_Temp(void);
float Promedio_Temp(void);
#endif 