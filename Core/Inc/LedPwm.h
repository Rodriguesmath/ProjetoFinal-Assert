/*
 * @brief Arquivo de definicoes para o controle PWM de LEDs.
 */
#ifndef _LEDPWM_H_
#define _LEDPWM_H_

/* INCLUDES NECESSARIOS */
#include <stdbool.h>
#include <stdint.h>

/* CONFIGURACOES */

/* DEFINES PUBLICOS */

/* TIPOS DE DADOS PUBLICOS */

/// Enumeracao que define os modos de operacao do controle de LED.
typedef enum {
    eLED_MODE_AUTOMATIC,
    eLED_MODE_MANUAL
} ledMode_t;

/* PROTOTIPOS PUBLICOS */

/**
 * @brief Inicializa o hardware de PWM associado aos LEDs.
 * @param void
 * @retval void
 */
void LedPwm_Init(void);

/**
 * @brief Rotina principal de controle de intensidade e atualizacao dos LEDs.
 * @param void
 * @retval void
 */
void LedPwm_Routine(void);

/**
 * @brief Altera o modo de operacao dos LEDs.
 * @param mode Novo modo a ser configurado (Automatico ou Manual).
 * @retval void
 */
void LedPwm_SetMode(ledMode_t mode);

/**
 * @brief Define manualmente a porcentagem de brilho de um LED especifico.
 * @param ledIndex Indice identificador do LED.
 * @param percentage Porcentagem de brilho desejada (0 a 100).
 * @retval void
 */
void LedPwm_SetManualPercentage(uint8_t ledIndex, uint8_t percentage);

#endif /* _LEDPWM_H_ */
