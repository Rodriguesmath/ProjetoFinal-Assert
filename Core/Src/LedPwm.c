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

/// Variavel que armazena o modo de operacao atual (Auto ou Manual)
static ledMode_t currentMode = eLED_MODE_AUTOMATIC;

/// Cache da ultima porcentagem lida para evitar atualizacoes de hardware desnecessarias
static uint8_t lastAutoPercentage = 255; 

void LedPwm_Init(void) {
    currentMode = eLED_MODE_AUTOMATIC;
    lastAutoPercentage = 255; /* Valor propositalmente fora de 0-100 para forcar o primeiro update */
}

void LedPwm_Routine(void) {
    /* No modo automatico, os 3 LEDs acompanham o ADC do Sampler */
    if (currentMode == eLED_MODE_AUTOMATIC) {
        
        /* So atualizamos a amostragem se o sistema NAO estiver congelado (Toggle do Botao) */
        if (!Button_IsFrozen()) {
            uint8_t currentAdcPercentage = Sampler_GetPercentage();
            
            /* Otimizacao: envia comando para a HAL/BSP apenas se o valor mudou de fato */
            if (currentAdcPercentage != lastAutoPercentage) {
                lastAutoPercentage = currentAdcPercentage;
                
                /* Replica o valor percentual para todos os LEDs mapeados no Bsp */
                Bsp_SetLedPwm(eLED_1, currentAdcPercentage);
                Bsp_SetLedPwm(eLED_2, currentAdcPercentage);
                Bsp_SetLedPwm(eLED_3, currentAdcPercentage);
            }
        }
    }
    /* Obs: No modo manual, nao fazemos nada na rotina continua. O brilho 
            eh ajustado cirurgicamente apenas quando a Serial chama o Setter. */
}

void LedPwm_SetMode(ledMode_t mode) {
    currentMode = mode;
    
    /* Ao voltar para o modo automatico, forca uma atualizacao no proximo ciclo */
    if (mode == eLED_MODE_AUTOMATIC) {
        lastAutoPercentage = 255; 
    }
}

void LedPwm_SetManualPercentage(ledId_t led, uint8_t percentage) {
    /* Como premissa de seguranca do contrato, so envia ao hardware se 
       a placa realmente estiver configurada para controle manual */
    if (currentMode == eLED_MODE_MANUAL) {
        Bsp_SetLedPwm(led, percentage);
    }
}

/* FUNCOES LOCAIS */
