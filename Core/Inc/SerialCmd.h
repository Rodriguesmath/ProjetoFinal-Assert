/*
 * @brief Arquivo de definicoes para comandos seriais.
 */
#ifndef _SERIALCMD_H_
#define _SERIALCMD_H_

/* INCLUDES NECESSARIOS */
#include <stdbool.h>
#include <stdint.h>

/* CONFIGURACOES */

/* DEFINES PUBLICOS */

/* TIPOS DE DADOS PUBLICOS */

/* PROTOTIPOS PUBLICOS */

/**
 * @brief Inicializa o modulo de comandos seriais.
 * @param void
 * @retval void
 */
void SerialCmd_Init(void);

/**
 * @brief Rotina de processamento de comandos.
 * @param void
 * @retval void
 */
void SerialCmd_Routine(void);

/**
 * @brief Imprime o status do sistema a cada 1 segundo (orquestrado).
 * @param void
 * @retval void
 */
void SerialCmd_PrintStatus1Hz(void);

#endif /* _SERIALCMD_H_ */
