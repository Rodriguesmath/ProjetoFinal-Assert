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
/// Tamanho da janela da media movel (100 amostras x 5ms = 500ms)
#define dMOVING_AVERAGE_SIZE 100

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */

/* PROTOTIPOS LOCAIS */

/* FUNCOES PUBLICAS */

/// Variavel local (privada ao arquivo) que guarda o ultimo valor cru lido
static uint32_t rawAdcValue = 0;

/// Variavel local (privada ao arquivo) que guarda o ultimo valor percentual calculado
static uint8_t percentageValue = 0;

/// Buffer circular para armazenar as ultimas 100 amostras do ADC
static uint32_t adcBuffer[dMOVING_AVERAGE_SIZE];

/// Acumulador para manter a soma fluida das amostras (evita laco FOR pesado)
static uint32_t adcSum = 0;

/// Indice atual do buffer circular
static uint8_t bufferIndex = 0;

/// Flag que indica se o buffer da media movel encheu ao menos uma vez
static bool isBufferFull = false;

void Sampler_Init(void) {
    /* O Bsp_Init ja realiza a inicializacao da HAL do ADC e do Timer de amostragem.
       Aqui garantimos a inicializacao segura da memoria do buffer e estados. */
    rawAdcValue = 0;
    percentageValue = 0;
    adcSum = 0;
    bufferIndex = 0;
    isBufferFull = false;
    
    for (uint8_t i = 0; i < dMOVING_AVERAGE_SIZE; i++) {
        adcBuffer[i] = 0;
    }
}

void Sampler_Routine(void) {
    /* Verifica se o Bsp sinalizou que passaram 5ms via interrupcao do Timer */
    if (Bsp_GetSamplingFlag()) {
        /* Limpa a flag de controle para nao ficar em loop lendo sem necessidade */
        Bsp_ClearSamplingFlag();
        
        /* Pede para a camada Bsp realizar a leitura fisica do ADC */
        uint32_t newAdcSample = (uint32_t)Bsp_ReadAdc();
        
        /* ================= LÓGICA DE MÉDIA MÓVEL RÁPIDA ================= */
        /* Subtrai do acumulador a amostra mais velha (que sera sobrescrita) */
        if (isBufferFull) {
            adcSum -= adcBuffer[bufferIndex];
        }
        
        /* Salva a amostra nova na posicao atual e a adiciona no acumulador */
        adcBuffer[bufferIndex] = newAdcSample;
        adcSum += newAdcSample;
        
        /* Rotaciona o indice do buffer circular */
        bufferIndex++;
        if (bufferIndex >= dMOVING_AVERAGE_SIZE) {
            bufferIndex = 0;
            isBufferFull = true; /* Sinaliza que atingimos a estabilidade (100 amostras completas) */
        }
        
        /* Calcula a media real. Evita divisão por 0 caso o sistema tenha acabado de ligar. 
           Se estiver no meio do enchimento, tira a media parcial da quantidade capturada. */
        if (isBufferFull) {
            rawAdcValue = adcSum / dMOVING_AVERAGE_SIZE;
        } else if (bufferIndex > 0) {
            rawAdcValue = adcSum / bufferIndex; 
        }
        /* ================================================================= */
        
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
