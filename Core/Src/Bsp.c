/*
 * @brief Implementacao do Board Support Package (BSP).
 *        Abstrai as operacoes de hardware (HAL) para a aplicacao.
 */

/* INCLUDES */
#include "Bsp.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>

/* DEFINES LOCAIS */
/// Tempo maximo de espera (timeout) para transmissao serial
#define dUART_TX_TIMEOUT_MS 100
/// Tempo maximo de espera (timeout) para conversao do ADC em milissegundos
#define dADC_TIMEOUT_MS 100
/// Valor maximo em porcentagem (100%)
#define dMAX_PERCENTAGE 100
/// Valor maximo do timer PWM (ARR).
#define dPWM_MAX_VALUE  1000

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */

/* PROTOTIPOS LOCAIS */
/**
 * @brief  Mapeia o identificador do LED para o respectivo canal e timer da HAL.
 * @param  ledId Identificador do LED (eLED_1, eLED_2, eLED_3).
 * @param  htim Ponteiro duplo para retornar a referencia do handle do timer.
 * @param  channel Ponteiro para retornar o numero do canal do timer.
 * @retval bool Verdadeiro se o LED for valido, falso caso contrario.
 */
static bool getPwmChannelParams(ledId_t ledId, TIM_HandleTypeDef **htim, uint32_t *channel);

/* FUNCOES PUBLICAS */

/// Variavel flag global para indicar amostragem do ADC (TIM6)
static volatile bool samplingFlag = false;

/// Variavel flag global para indicar tick de debounce (TIM7)
static volatile bool debounceFlag = false;

/// Variavel flag global para indicar acionamento do botao (EXTI)
static volatile bool buttonTriggerFlag = false;

void Bsp_Init(void) {
    /* Inicializa e calibra o ADC */
    HAL_ADC_Start(&hadc1);
    
    /* Inicializa os canais de PWM corretos baseados no mapeamento */
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);  /* LED 1 */
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);  /* LED 2 */
    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1); /* LED 3 */
    
    /* Inicializa os Timers de base de tempo com interrupcoes */
    HAL_TIM_Base_Start_IT(&htim6); /* Amostragem (5ms) */
    HAL_TIM_Base_Start_IT(&htim7); /* Debounce */
}

void Bsp_SetLedPwm(ledId_t led, uint8_t percentage) {
    TIM_HandleTypeDef *htim = NULL;
    uint32_t channel = 0;
    
    if (percentage > dMAX_PERCENTAGE) {
        percentage = dMAX_PERCENTAGE;
    }
    
    if (getPwmChannelParams(led, &htim, &channel)) {
        /* Calcula o valor do compare register baseando-se na porcentagem */
        uint32_t compareValue = (uint32_t)percentage * (dPWM_MAX_VALUE / dMAX_PERCENTAGE);
        __HAL_TIM_SET_COMPARE(htim, channel, compareValue);
    }
}

uint16_t Bsp_ReadAdc(void) {
    uint16_t adcValue = 0;
    
    /* Inicia a conversao do ADC via software */
    HAL_ADC_Start(&hadc1);
    
    /* Aguarda o fim da conversao em modo polling */
    if (HAL_ADC_PollForConversion(&hadc1, dADC_TIMEOUT_MS) == HAL_OK) {
        adcValue = (uint16_t)HAL_ADC_GetValue(&hadc1);
    }
    
    return adcValue;
}

bool Bsp_GetSamplingFlag(void) {
    return samplingFlag;
}

void Bsp_ClearSamplingFlag(void) {
    samplingFlag = false;
}

bool Bsp_GetDebounceFlag(void) {
    return debounceFlag;
}

void Bsp_ClearDebounceFlag(void) {
    debounceFlag = false;
}

bool Bsp_GetButtonTrigger(void) {
    return buttonTriggerFlag;
}

void Bsp_ClearButtonTrigger(void) {
    buttonTriggerFlag = false;
}

void Bsp_TransmitString(const char *str) {
    if (str != NULL) {
        HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), dUART_TX_TIMEOUT_MS);
    }
}

bool Bsp_ReadUartChar(uint8_t *data) {
    /* Leitura nao bloqueante (timeout = 0) de 1 byte da UART */
    return (HAL_UART_Receive(&huart3, data, 1, 0) == HAL_OK);
}

uint32_t Bsp_GetTick(void) {
    return HAL_GetTick();
}

/**
 * @brief Callback chamado pela HAL quando ocorre o estouro (update) de um timer base.
 * @param htim Handle do timer que gerou a interrupcao.
 * @retval void
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    /* Verifica de qual timer veio a interrupcao */
    if (htim->Instance == TIM6) {
        samplingFlag = true;
    }
    else if (htim->Instance == TIM7) {
        debounceFlag = true;
    }
}

/**
 * @brief Callback chamado pela HAL quando ocorre uma interrupcao externa (EXTI).
 * @param GPIO_Pin Pino que gerou a interrupcao.
 * @retval void
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    /* Verifica se a interrupcao veio do pino do botao de usuario */
    if (GPIO_Pin == USER_Btn_Pin) {
        buttonTriggerFlag = true;
    }
}

/* FUNCOES LOCAIS */

static bool getPwmChannelParams(ledId_t ledId, TIM_HandleTypeDef **htim, uint32_t *channel) {
    bool isValid = true;
    
    switch (ledId) {
        case eLED_1:
            *htim = &htim3;
            *channel = TIM_CHANNEL_3;
            break;
        case eLED_2:
            *htim = &htim4;
            *channel = TIM_CHANNEL_2;
            break;
        case eLED_3:
            *htim = &htim12;
            *channel = TIM_CHANNEL_1;
            break;
        default:
            isValid = false;
            break;
    }
    
    return isValid;
}
