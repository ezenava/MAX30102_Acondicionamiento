/*
 * -----------------------
 * TPM.c
 * -----------------------
 * 
 * Materias:
 * Sistemas Electrónicos Embebidos
 * 
 * 6to Año Técnico en Electrónica
 * Colegio Pio IX
 * 
 * Revisión 1
 * Año 2023
 * 
 * Profesores: Matías Marfisi, Tomás Zuran, Federico Diograzia
 * 
 */

#include "TPM.h"

static const uint8_t tpm_prescaler[] = {
	1,
	2,
	4,
	8,
	16,
	32,
	64,
	128
};

/*
 * Funcion: TPM_InitOverflow
 * ----------------------------
 *	Inicializa un modulo TPM. Revisar si el valor de prescaler se ajusta a las necesidades de frecuencia.
 *
 *	     48MHz	
 *	---------------- < 65535 (maximo 16 bits)
 *	freq * prescaler
 *
 *	Parametros:
 *	tpm: número de TPM
 *	freq: frecuencia de interrupcion deseada
 *
 *	returns: nada
 */
void TPM_InitOverflow(uint8_t tpm, uint32_t freq, uint8_t prescaler)
{
	// Utilizo vector de punteros en MKL25Z4.h para seleccionar el registro de TPM correspondiente
	TPM_Type *tpm_ptr[] = TPM_BASE_PTRS;
	/*
	 tpm_ptr[0] -> TPM0
	 tpm_ptr[1] -> TPM1
	 tpm_ptr[2] -> TPM2
	 */
	// Habilito módulo TPM
	SIM->SCGC6 |= 1 << (SIM_SCGC6_TPM0_SHIFT + tpm);
	// Selecciono fuente de clock para TPM
	SIM->SOPT2 = (SIM->SOPT2 & (~SIM_SOPT2_TPMSRC_MASK)) | SIM_SOPT2_TPMSRC(1);
	// Habilito interrupciones, selecciono incrementos de clock y fijo prescaler en valor necesario (ajustar)
	TPM_SC_REG(tpm_ptr[tpm]) = TPM_SC_TOIE_MASK | TPM_SC_CMOD(1) | TPM_SC_PS(prescaler);
	// Fijo el modulo necesario a la frecuencia deseada
	TPM_MOD_REG(tpm_ptr[tpm]) = CLOCK_FREQ / (freq * tpm_prescaler[prescaler]);
	// Habilito interrupcion
	NVIC_EnableIRQ(TPM0_IRQn + tpm);
}

volatile unsigned int tiempo_tpm = 0;
volatile unsigned int cont = 0;
volatile unsigned int tempe = 0,tiempo_promedio = 0;

void TPM0_IRQHandler(void)
{
	// Atiendo la interrupcion
	TPM0->SC |= TPM_SC_TOF_MASK;
	
	/* Codigo a ejecutar en interrupcion */
if(tempe > 0)
		tempe --;
	/* Fin codigo a ejecutar en interrupcion */
}

void TPM1_IRQHandler(void)
{
	// Atiendo la interrupcion
	TPM1->SC |= TPM_SC_TOF_MASK;
	
	/* Codigo a ejecutar en interrupcion */

	/* Fin codigo a ejecutar en interrupcion */
}

void TPM2_IRQHandler(void)
{
	// Atiendo la interrupcion
	TPM2->SC |= TPM_SC_TOF_MASK;
	
	/* Codigo a ejecutar en interrupcion */
	
	/* Fin codigo a ejecutar en interrupcion */
}
