#ifndef UART0_H_
#define UART0_H_

#include "MKL25Z4.h"

void init_uart_0(void);
void UART0_TransmitirChar(char data) ;
void UART0_TransmitirInt(int data) ;
void UART0_TransmitirString(const char *str);
void UART0_TransmitirUint32(uint32_t data);
void UART0_TransmitirFloat(float value);

#endif