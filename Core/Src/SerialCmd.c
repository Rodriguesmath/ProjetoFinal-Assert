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
/// Tamanho maximo reservado para o buffer de transmissao da resposta
#define dRESPONSE_BUFFER_SIZE 128
/// Comando para selecionar LED1
#define dCMD_LED1 "LED1"
#define dCMD_LED1_LEN 4
/// Comando para selecionar LED2
#define dCMD_LED2 "LED2"
#define dCMD_LED2_LEN 4
/// Comando para selecionar LED3
#define dCMD_LED3 "LED3"
#define dCMD_LED3_LEN 4

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
    
    /* REGRA: Selecionar LED 1 */
    if (strncmp(command, dCMD_LED1, dCMD_LED1_LEN) == 0) {
        LedPwm_SetSelectedLed(eLED_1);
        Bsp_TransmitString("OK: LED1 selecionado.\r\n");
    }
    
    /* REGRA: Selecionar LED 2 */
    else if (strncmp(command, dCMD_LED2, dCMD_LED2_LEN) == 0) {
        LedPwm_SetSelectedLed(eLED_2);
        Bsp_TransmitString("OK: LED2 selecionado.\r\n");
    }
    
    /* REGRA: Selecionar LED 3 */
    else if (strncmp(command, dCMD_LED3, dCMD_LED3_LEN) == 0) {
        LedPwm_SetSelectedLed(eLED_3);
        Bsp_TransmitString("OK: LED3 selecionado.\r\n");
    }
    
    /* Nao eh igual a nenhuma das regras? Bad Request */
    else {
        Bsp_TransmitString("ERRO: Comando nao reconhecido. Utilize LED1, LED2 ou LED3.\r\n");
    }
}
