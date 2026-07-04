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
 * @brief Retorna o estado da flag de estouro do timer de 5ms.
 * @param void
 * @retval bool 'true' se estourou, 'false' caso contrario.
 */
bool Bsp_GetTimerFlag(void);

/**
 * @brief Limpa a flag de estouro do timer de 5ms.
 * @param void
 * @retval void
 */
void Bsp_ClearTimerFlag(void);

#endif /* _BSP_H_ */
