/*
 * @brief Arquivo de definicoes para debounce de botoes.
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
 * @brief Inicializa o modulo de botoes.
 * @param void
 * @retval void
 */
void Button_Init(void);

/**
 * @brief Rotina de leitura e debounce de botoes.
 * @param void
 * @retval void
 */
void Button_Routine(void);

/**
 * @brief Retorna se o sistema esta congelado.
 * @param void
 * @retval bool 'true' se congelado, 'false' senao.
 */
bool Button_IsFrozen(void);

#endif /* _BUTTON_H_ */
