/*
 * @brief Implementacao das funcoes do modulo de amostragem ADC.
 */

/* INCLUDES */
#include "Sampler.h"

/* DEFINES LOCAIS */

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */

/* PROTOTIPOS LOCAIS */

/* FUNCOES PUBLICAS */

void Sampler_Init(void) {
    /* Inicializacao do periferico ADC */
}

void Sampler_Routine(void) {
    /* Leitura periodica e processamento dos dados do ADC */
}

uint32_t Sampler_GetRawAdc(void) {
    uint32_t rawValue = 0;
    /* Obtencao do valor cru do hardware */
    return rawValue;
}

uint8_t Sampler_GetPercentage(void) {
    uint8_t percentage = 0;
    /* Calculo da porcentagem com base no valor cru */
    return percentage;
}

/* FUNCOES LOCAIS */
