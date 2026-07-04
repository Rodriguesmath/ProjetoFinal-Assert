/*
 * @brief Arquivo de definicoes para gerenciamento e debounce de botoes.
 */
#ifndef _BUTTON_H_
#define _BUTTON_H_

/* INCLUDES NECESSARIOS */
#include <stdbool.h>
#include <stdint.h>

/* CONFIGURACOES */

/* DEFINES PUBLICOS */

/* TIPOS DE DADOS PUBLICOS */

/* PROTOTIPOS PUBLICOS */

/**
 * @brief Inicializa o modulo e os pinos GPIO configurados como entrada para os botoes.
 * @param void
 * @retval void
 */
void Button_Init(void);

/**
 * @brief Executa o tratamento de debounce e identifica cliques ou eventos longos.
 * @param void
 * @retval void
 */
void Button_Routine(void);

/**
 * @brief Retorna uma indicacao booleana se o sistema esta em estado congelado.
 * @param void
 * @retval bool 'true' se estiver congelado, caso contrario 'false'.
 */
bool Button_IsFrozen(void);

#endif /* _BUTTON_H_ */
