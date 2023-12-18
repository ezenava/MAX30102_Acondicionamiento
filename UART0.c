#include "MKL25Z4.h"
#include "GPIO.h"
#include <stdint.h>
#include <stdio.h>

#define TRANSMISOR_OK (UART0_S1 & UART0_S1_TC_MASK)


void init_uart_0(void) {
// clock UART 0
SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; // clock UART 0
// selecciono clock del UART0 MCGIRCLK
SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
// Configura pines limpiando los flags de int pendientes y seleccionando los pines
PORTA_PCR2 &= ~PORT_PCR_MUX_MASK;
PORTA_PCR2 |= (PORT_PCR_ISF_MASK| (0x2 << PORT_PCR_MUX_SHIFT));
PORTA_PCR1 &= ~PORT_PCR_MUX_MASK;
PORTA_PCR1 |= (PORT_PCR_ISF_MASK| (0x2 << PORT_PCR_MUX_SHIFT));
UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK); // Deshabilita la UART0
UART0_C1 = 0;
UART0_C4 = UART0_C4_OSR(15);
UART0_BDL = UART0_BDL_SBR(56); // 9600 baud -->
UART0_BDH = UART0_BDH_SBR(1);
UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK); // Habilitamos Tx y Rx
}


void UART0_TransmitirChar(char data) {
    // Esperar hasta que el buffer de transmisión esté vacío
  while (!TRANSMISOR_OK);
    // Enviar el carácter
    UART0_D = data;
}
void UART0_TransmitirInt(int data) {
    // Esperar hasta que el buffer de transmisión esté vacío
 while (!TRANSMISOR_OK); //
    // Enviar el carácter
    UART0_D = data;
}


void UART0_TransmitirString(const char *str) {
//    while (*str) {
//        UART0_TransmitirChar(*str++);
//    }
	 while (*str != '\0') {
        UART0_TransmitirChar(*str);
        str++;
    }
}
void UART0_TransmitirUint32(uint32_t data) {
    uint8_t* pData = (uint8_t*)&data;
    for (int i = 0; i < 4; i++) {
        while (!TRANSMISOR_OK); // Espera a que el buffer de transmisión esté vacío
        UART0_D = pData[i]; // Envía un byte
    }
}

void UART0_TransmitirFloat(float value) {
    char buffer[32]; // Tamaño del buffer para la cadena de caracteres
    
    // Convierte el valor float a una cadena de caracteres
    snprintf(buffer, sizeof(buffer), "%.2f", value);
    
    // Enviar cada carácter de la cadena
    for (int i = 0; buffer[i] != '\0'; i++) {
        while (!TRANSMISOR_OK); // Espera a que el registro de transmisión esté vacío
        UART0->D = buffer[i]; // Envía el carácter
    }
}
