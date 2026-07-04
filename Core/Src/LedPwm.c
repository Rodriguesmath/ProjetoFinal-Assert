/*
 * @brief Implementacao do controle PWM dos LEDs (Automatico e Manual).
 */

/* INCLUDES */
#include "LedPwm.h"
#include "Sampler.h"
#include "Button.h"

/* DEFINES LOCAIS */

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */

/* PROTOTIPOS LOCAIS */

/* FUNCOES PUBLICAS */

/// Armazena qual o LED atualmente selecionado para ser controlado
static ledId_t selectedLed = eLED_1;

/// Armazena o duty atual de cada LED para consulta
static uint8_t ledDuties[3] = {0, 0, 0};

void LedPwm_Init(void) {
    selectedLed = eLED_1;
    ledDuties[0] = 0;
    ledDuties[1] = 0;
    ledDuties[2] = 0;
}

void LedPwm_Routine(void) {
    /* So atualizamos a amostragem se o sistema NAO estiver congelado (Toggle do Botao) */
    if (!Button_IsFrozen()) {
        uint8_t currentAdcPercentage = Sampler_GetPercentage();
        
        /* Otimizacao: envia comando para a HAL/BSP apenas se o valor mudou de fato */
        if (currentAdcPercentage != ledDuties[selectedLed]) {
            ledDuties[selectedLed] = currentAdcPercentage;
            
            /* Replica o valor percentual apenas para o LED selecionado */
            Bsp_SetLedPwm(selectedLed, currentAdcPercentage);
        }
    }
}

void LedPwm_SetSelectedLed(ledId_t led) {
    if (led >= eLED_1 && led <= eLED_3) {
        selectedLed = led;
    }
}

/* FUNCOES LOCAIS */

uint8_t LedPwm_GetDuty(ledId_t led) {
    if (led >= eLED_1 && led <= eLED_3) {
        return ledDuties[led];
    }
    return 0;
}
