#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "hardware/adc.h"
#include "libs/joystick_lib.h"
#include "libs/malha_led.h"
#include "libs/direcoes.h"
#include "tests/Testjoystick.h"

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5



int main()
{
    stdio_init_all();
    npInit();
    init_joystick();
    
    while(true) {
        test_completo();
        npClear();
        npWrite(); // Escreve os dados nos LEDs.
        test_display();
        npClear();
        npWrite(); // Escreve os dados nos LEDs.
    }
}

/*
int main(){
    stdio_init_all();
    init_joystick();
    npInit();
    npClear();
    npWrite(); // Escreve os dados nos LEDs.

    while (true) {
        joystick_captura();
        normalizar_joystick();
        npClear();
        npWrite(); // Escreve os dados nos LEDs.
        sleep_ms(1);

        switch (get_direcao()) {
            // Direções principais
            case CIMA1: display_sprite(cima1); break;
            case CIMA2: display_sprite(cima2); break;
            case BAIXO1: display_sprite(bai1); break;
            case BAIXO2: display_sprite(bai2); break;
            case DIREITA1: display_sprite(dir1); break;
            case DIREITA2: display_sprite(dir2); break;
            case ESQUERDA1: display_sprite(esq1); break;
            case ESQUERDA2: display_sprite(esq2); break;
        
            // Diagonais
            case DIAG_CIMA_DIREITA1: display_sprite(dircim1); break;
            case DIAG_CIMA_DIREITA2: display_sprite(dircim2); break;
            case DIAG_CIMA_ESQUERDA1: display_sprite(esqcim1); break;
            case DIAG_CIMA_ESQUERDA2: display_sprite(esqcim2); break;
            case DIAG_BAIXO_DIREITA1: display_sprite(dirbax1); break;
            case DIAG_BAIXO_DIREITA2: display_sprite(dirbax2); break;
            case DIAG_BAIXO_ESQUERDA1: display_sprite(esqbax1); break;
            case DIAG_BAIXO_ESQUERDA2: display_sprite(esqbax2); break;
        
            case NEUTRO: display_sprite(neutro); break;
        }
        npWrite();  
    }
}
*/