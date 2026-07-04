/*
 * @brief Implementacao das funcoes de leitura e gerenciamento de estados dos botoes.
 */

/* INCLUDES */
#include "Button.h"

/* DEFINES LOCAIS */

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */

/* PROTOTIPOS LOCAIS */

/* FUNCOES PUBLICAS */

void Button_Init(void) {
    /* Configuracao do GPIO com pull-ups internos ou interrupcoes */
}

void Button_Routine(void) {
    /* Filtro de debounce e maquina de estados de clique */
}

bool Button_IsFrozen(void) {
    bool isSystemFrozen = false;
    /* Retorna a flag de estado global alterada por algum dos botoes */
    return isSystemFrozen;
}

/* FUNCOES LOCAIS */
