/*
 * @brief Arquivo de definicoes para o controle PWM de LEDs.
 */
#ifndef _LEDPWM_H_
#define _LEDPWM_H_

/* INCLUDES NECESSARIOS */
#include "Bsp.h"
#include <stdbool.h>
#include <stdint.h>

/* CONFIGURACOES */

/* DEFINES PUBLICOS */

/* TIPOS DE DADOS PUBLICOS */
/// Enumeracao para os modos de operacao do LED
typedef enum {
    eLED_MODE_AUTOMATIC,
    eLED_MODE_MANUAL
} ledMode_t;

/* PROTOTIPOS PUBLICOS */

/**
 * @brief Inicializa o modulo de controle PWM de LEDs.
 * @param void
 * @retval void
 */
void LedPwm_Init(void);

/**
 * @brief Rotina principal de controle dos LEDs.
 * @param void
 * @retval void
 */
void LedPwm_Routine(void);

/**
 * @brief Altera o modo de operacao.
 * @param mode Novo modo a ser configurado.
 * @retval void
 */
void LedPwm_SetMode(ledMode_t mode);

/**
 * @brief Define manualmente a porcentagem de um LED.
 * @param led O identificador do LED.
 * @param percentage Porcentagem de brilho (0 a 100).
 * @retval void
 */
void LedPwm_SetManualPercentage(ledId_t led, uint8_t percentage);

#endif /* _LEDPWM_H_ */
