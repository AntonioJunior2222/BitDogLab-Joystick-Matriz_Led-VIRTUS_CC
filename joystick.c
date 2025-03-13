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