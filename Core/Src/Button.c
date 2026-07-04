/*
 * @brief Implementacao do gerenciamento e debounce do botao de usuario.
 */

/* INCLUDES */
#include "Button.h"
#include "Bsp.h"

/* DEFINES LOCAIS */
/// Numero de "ticks" do timer de debounce que devemos ignorar novos acionamentos (Dead-time)
#define dDEBOUNCE_TICKS_LIMIT 10

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */
/// Enumeracao da maquina de estados de clique
typedef enum {
    eBUTTON_STATE_IDLE,
    eBUTTON_STATE_DEBOUNCE
} buttonState_t;

/* PROTOTIPOS LOCAIS */

/* FUNCOES PUBLICAS */

/// Variavel local que guarda se o sistema esta no estado congelado (alternado via botao)
static bool isSystemFrozen = false;

/// Estado atual da maquina de debounce
static buttonState_t currentState = eBUTTON_STATE_IDLE;

/// Contador de tempo para ignorar o ruido dinamico (bouncing)
static uint8_t debounceCounter = 0;

void Button_Init(void) {
    /* O hardware do pino (EXTI) e do Timer 7 ja foi inicializado no Bsp_Init.
       Aqui apenas restauramos a maquina de software para as condicoes iniciais. */
    isSystemFrozen = false;
    currentState = eBUTTON_STATE_IDLE;
    debounceCounter = 0;
}

void Button_Routine(void) {
    /* 1. Tratamento do Trigger do Botao (Sinal Assincrono do EXTI) */
    if (Bsp_GetButtonTrigger()) {
        /* Imediatamente limpa a flag da interrupcao abstraida */
        Bsp_ClearButtonTrigger();
        
        /* So aceita o clique se nao estivermos no periodo morto de debounce */
        if (currentState == eBUTTON_STATE_IDLE) {
            /* Inverte a logica de congelamento do sistema (Toggle) */
            isSystemFrozen = !isSystemFrozen;
            
            /* Muda de estado e zera a contagem para bloquear clicks ruidosos */
            currentState = eBUTTON_STATE_DEBOUNCE;
            debounceCounter = 0;
        }
    }
    
    /* 2. Tratamento da base de tempo do Debounce (Sinal Sincrono do TIM7) */
    if (Bsp_GetDebounceFlag()) {
        /* Limpa a flag do timer de debounce */
        Bsp_ClearDebounceFlag();
        
        /* Se estiver no periodo morto, comeca a contar ate recuperar a estabilidade */
        if (currentState == eBUTTON_STATE_DEBOUNCE) {
            debounceCounter++;
            
            if (debounceCounter >= dDEBOUNCE_TICKS_LIMIT) {
                /* Tempo morto superado, botao livre para registrar novo clique */
                currentState = eBUTTON_STATE_IDLE;
            }
        }
    }
}

bool Button_IsFrozen(void) {
    return isSystemFrozen;
}

/* FUNCOES LOCAIS */
