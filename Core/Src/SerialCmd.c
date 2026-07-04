/*
 * @brief Implementacao do parser e orquestracao de comandos seriais.
 */

/* INCLUDES */
#include "SerialCmd.h"
#include "Bsp.h"
#include "LedPwm.h"
#include "Sampler.h"
#include "Button.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* DEFINES LOCAIS */
/// Tamanho maximo reservado para o buffer de recepcao da porta serial
#define dRX_BUFFER_SIZE 64

/* CONSTANTES */

/* ESTRUTURAS DE DADOS LOCAIS */

/* PROTOTIPOS LOCAIS */
/**
 * @brief Interpreta e executa a string de comando recebida validando as regras.
 * @param command Ponteiro para a string pura recebida via UART.
 * @retval void
 */
static void processCommand(const char *command);

/* FUNCOES PUBLICAS */

/// Buffer (array de caracteres) para armazenar a string em construcao
static char rxBuffer[dRX_BUFFER_SIZE];

/// Indice que aponta a proxima posicao livre no buffer
static uint8_t rxIndex = 0;

void SerialCmd_Init(void) {
    rxIndex = 0;
    memset(rxBuffer, 0, dRX_BUFFER_SIZE);
}

void SerialCmd_Routine(void) {
    uint8_t receivedChar = 0;
    
    /* Le freneticamente todos os caracteres que chegaram na UART (não-bloqueante) */
    while (Bsp_ReadUartChar(&receivedChar)) {
        
        /* Se recebeu quebra de linha ('Enter'), a palavra foi finalizada. Bora processar! */
        if (receivedChar == '\n' || receivedChar == '\r') {
            
            /* Evita acoes caso a string esteja vazia */
            if (rxIndex > 0) {
                rxBuffer[rxIndex] = '\0'; /* Finaliza a string no padrao C com nulo */
                processCommand(rxBuffer);
                rxIndex = 0; /* Zera o indice limpando o buffer implicitamente */
            }
        } 
        else {
            /* Acumula o caractere validando o limite maximo para barrar o famoso Buffer Overflow! */
            if (rxIndex < (dRX_BUFFER_SIZE - 1)) {
                rxBuffer[rxIndex] = (char)receivedChar;
                rxIndex++;
            }
        }
    }
}

/* FUNCOES LOCAIS */

static void processCommand(const char *command) {
    char responseBuffer[128];
    
    /* REGRA: Mudar o modulo LedPwm para o modo AUTOMATICO */
    if (strncmp(command, "MODE AUTO", 9) == 0) {
        LedPwm_SetMode(eLED_MODE_AUTOMATIC);
        Bsp_TransmitString("OK: Modo Automatico Ativado\r\n");
    }
    
    /* REGRA: Mudar o modulo LedPwm para o modo MANUAL */
    else if (strncmp(command, "MODE MANUAL", 11) == 0) {
        LedPwm_SetMode(eLED_MODE_MANUAL);
        Bsp_TransmitString("OK: Modo Manual Ativado\r\n");
    }
    
    /* REGRA: Relatorio dinamico do estado atual (Consome Sampler e Button) */
    else if (strncmp(command, "STATUS", 6) == 0) {
        snprintf(responseBuffer, sizeof(responseBuffer), 
                 "ADC Raw: %lu | PCT: %u%% | Congelado: %s\r\n", 
                 (unsigned long)Sampler_GetRawAdc(), 
                 Sampler_GetPercentage(), 
                 Button_IsFrozen() ? "SIM" : "NAO");
        Bsp_TransmitString(responseBuffer);
    }
    
    /* REGRA: Controle cirurgico manual de um unico LED (Ex: "LED 1 50") */
    else if (strncmp(command, "LED ", 4) == 0) {
        int ledNum = 0;
        int pct = 0;
        
        /* Quebra (Parse) a string extraindo os inteiros via sscanf */
        if (sscanf(command, "LED %d %d", &ledNum, &pct) == 2) {
            ledId_t targetLed;
            bool valid = true;
            
            /* Valida os limites para nao enviar sujeira na camada baixa */
            switch (ledNum) {
                case 1: targetLed = eLED_1; break;
                case 2: targetLed = eLED_2; break;
                case 3: targetLed = eLED_3; break;
                default: valid = false; break;
            }
            
            if (valid) {
                LedPwm_SetManualPercentage(targetLed, (uint8_t)pct);
                snprintf(responseBuffer, sizeof(responseBuffer), "OK: LED %d ajustado para %d%%\r\n", ledNum, pct);
                Bsp_TransmitString(responseBuffer);
            } else {
                Bsp_TransmitString("ERRO: O sistema apenas reconhece LED 1, 2 ou 3\r\n");
            }
        } else {
            Bsp_TransmitString("ERRO: Sintaxe. Utilize o padrao 'LED <id> <porcentagem>'\r\n");
        }
    }
    
    /* Nao eh igual a nenhuma das regras? Bad Request */
    else {
        Bsp_TransmitString("ERRO: Comando nao reconhecido pelo sistema.\r\n");
    }
}
