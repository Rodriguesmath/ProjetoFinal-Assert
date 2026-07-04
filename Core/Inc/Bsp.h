/*
 * @brief Arquivo de definicoes para o Board Support Package. Esconde a HAL da aplicacao.
 */
#ifndef _BSP_H_
#define _BSP_H_

/* INCLUDES NECESSARIOS */
#include <stdbool.h>
#include <stdint.h>

/* CONFIGURACOES */

/* DEFINES PUBLICOS */

/* TIPOS DE DADOS PUBLICOS */
/// Enumeracao para os LEDs da placa
typedef enum {
    eLED_1,
    eLED_2,
    eLED_3
} ledId_t;

/* PROTOTIPOS PUBLICOS */

/**
 * @brief Inicializa os perifericos de hardware (ADC, PWM, Timers, UART, GPIOs).
 * @param void
 * @retval void
 */
void Bsp_Init(void);

/**
 * @brief Define a porcentagem do PWM para um LED especifico.
 * @param led O identificador do LED.
 * @param percentage Porcentagem do duty cycle (0 a 100).
 * @retval void
 */
void Bsp_SetLedPwm(ledId_t led, uint8_t percentage);

/**
 * @brief Realiza a leitura do ADC em modo polling e retorna o valor.
 * @param void
 * @retval uint16_t Valor lido do ADC.
 */
uint16_t Bsp_ReadAdc(void);

/**
 * @brief Retorna o estado da flag de amostragem (TIM6 - 5ms).
 * @param void
 * @retval bool 'true' se estourou, 'false' caso contrario.
 */
bool Bsp_GetSamplingFlag(void);

/**
 * @brief Limpa a flag de amostragem (TIM6).
 * @param void
 * @retval void
 */
void Bsp_ClearSamplingFlag(void);

/**
 * @brief Retorna o estado da flag de debounce (TIM7).
 * @param void
 * @retval bool 'true' se estourou, 'false' caso contrario.
 */
bool Bsp_GetDebounceFlag(void);

/**
 * @brief Limpa a flag de debounce (TIM7).
 * @param void
 * @retval void
 */
void Bsp_ClearDebounceFlag(void);

/**
 * @brief Retorna se o botao foi acionado (trigger via EXTI).
 * @param void
 * @retval bool 'true' se ocorreu a interrupcao, 'false' caso contrario.
 */
bool Bsp_GetButtonTrigger(void);

/**
 * @brief Limpa a flag de trigger do botao.
 * @param void
 * @retval void
 */
void Bsp_ClearButtonTrigger(void);

/**
 * @brief Transmite uma string (text/pacote) pela UART.
 * @param str Ponteiro para a string (terminada em nulo).
 * @retval void
 */
void Bsp_TransmitString(const char *str);

/**
 * @brief Tenta ler um caractere da UART de forma nao-bloqueante.
 * @param data Ponteiro onde o caractere lido sera armazenado.
 * @retval bool 'true' se um caractere for lido, 'false' se nao houver dados.
 */
bool Bsp_ReadUartChar(uint8_t *data);

#endif /* _BSP_H_ */
