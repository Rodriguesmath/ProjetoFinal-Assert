/*
 * @brief Arquivo de definicoes para recebimento e processamento de comandos seriais.
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
 * @brief Inicializa a comunicacao serial e os buffers de comando.
 * @param void
 * @retval void
 */
void SerialCmd_Init(void);

/**
 * @brief Processa os comandos recebidos na rotina principal.
 * @param void
 * @retval void
 */
void SerialCmd_Routine(void);

#endif /* _SERIALCMD_H_ */
