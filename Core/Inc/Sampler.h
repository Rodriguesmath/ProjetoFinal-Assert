/*
 * @brief Arquivo de definicoes para o modulo de amostragem ADC.
 */
#ifndef _SAMPLER_H_
#define _SAMPLER_H_

/* INCLUDES NECESSARIOS */
#include <stdbool.h>
#include <stdint.h>

/* CONFIGURACOES */

/* DEFINES PUBLICOS */

/* TIPOS DE DADOS PUBLICOS */

/* PROTOTIPOS PUBLICOS */

/**
 * @brief Inicializa o modulo de amostragem.
 * @param void
 * @retval void
 */
void Sampler_Init(void);

/**
 * @brief Rotina principal do modulo de amostragem para o laco principal.
 * @param void
 * @retval void
 */
void Sampler_Routine(void);

/**
 * @brief Retorna o valor cru (raw) lido do ADC.
 * @param void
 * @retval uint32_t Valor cru do ADC.
 */
uint32_t Sampler_GetRawAdc(void);

/**
 * @brief Retorna o valor de amostragem convertido em porcentagem.
 * @param void
 * @retval uint8_t Valor em porcentagem (0 a 100).
 */
uint8_t Sampler_GetPercentage(void);

#endif /* _SAMPLER_H_ */
