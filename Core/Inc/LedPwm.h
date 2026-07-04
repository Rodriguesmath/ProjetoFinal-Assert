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
 * @brief Define qual LED sera controlado pelo potenciometro.
 * @param led O identificador do LED.
 * @retval void
 */
void LedPwm_SetSelectedLed(ledId_t led);

/**
 * @brief Retorna o valor percentual atual do duty cycle de um LED especifico.
 * @param led O identificador do LED.
 * @retval uint8_t Porcentagem de brilho (0 a 100).
 */
uint8_t LedPwm_GetDuty(ledId_t led);

#endif /* _LEDPWM_H_ */
