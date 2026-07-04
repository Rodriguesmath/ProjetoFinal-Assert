/*
 * @brief Implementacao do modulo de amostragem ADC.
 */

/* INCLUDES */
#include "Sampler.h"
#include "Bsp.h"

/* DEFINES LOCAIS */
/// Valor maximo lido pelo hardware ADC (resolucao de 12 bits)
#define dADC_MAX_RAW_VALUE 4095
/// Valor maximo de escala em porcentagem (100%)
#define dMAX_PERCENTAGE_VALUE 100

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */

/* PROTOTIPOS LOCAIS */

/* FUNCOES PUBLICAS */

/// Variavel local (privada ao arquivo) que guarda o ultimo valor cru lido
static uint32_t rawAdcValue = 0;

/// Variavel local (privada ao arquivo) que guarda o ultimo valor percentual calculado
static uint8_t percentageValue = 0;

void Sampler_Init(void) {
    /* O Bsp_Init ja realiza a inicializacao da HAL do ADC e do Timer de amostragem.
       Aqui apenas garantimos o estado seguro das nossas variaveis. */
    rawAdcValue = 0;
    percentageValue = 0;
}

void Sampler_Routine(void) {
    /* Verifica se o Bsp sinalizou que passaram 5ms via interrupcao do Timer */
    if (Bsp_GetSamplingFlag()) {
        /* Limpa a flag de controle para nao ficar em loop lendo sem necessidade */
        Bsp_ClearSamplingFlag();
        
        /* Pede para a camada Bsp realizar a leitura fisica do ADC */
        rawAdcValue = (uint32_t)Bsp_ReadAdc();
        
        /* Trava em 4095 para evitar estourar o limite de 12 bits teorico */
        if (rawAdcValue > dADC_MAX_RAW_VALUE) {
            rawAdcValue = dADC_MAX_RAW_VALUE;
        }
        
        /* Converte o valor cru para a escala percentual usando regra de tres simples */
        percentageValue = (uint8_t)((rawAdcValue * dMAX_PERCENTAGE_VALUE) / dADC_MAX_RAW_VALUE);
    }
}

uint32_t Sampler_GetRawAdc(void) {
    return rawAdcValue;
}

uint8_t Sampler_GetPercentage(void) {
    return percentageValue;
}

/* FUNCOES LOCAIS */
