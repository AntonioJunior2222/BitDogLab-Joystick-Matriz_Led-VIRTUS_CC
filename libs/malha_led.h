#ifndef MALHA_LED_H
#define MALHA_LED_H

#include "pico/stdlib.h"
#include "hardware/pio.h"


// Configurações da matriz
#define LED_COUNT 25 // Número total de LEDs na matriz (5x5)
#define LED_PIN 7    // Pino GPIO conectado ao barramento de dados dos LEDs NeoPixel

// Estrutura para representar um pixel GRB
// Cada pixel é composto por três valores de 8 bits: Verde (G), Vermelho (R) e Azul (B)
typedef struct {
    uint8_t G, R, B; // Ordem GRB é específica para LEDs WS2812B/NeoPixel
} npLED_t;

// Cor tema (R, G, B)
extern uint8_t tema_cor[3];

// Funções de inicialização e controle da matriz

// Inicializa a matriz de LEDs NeoPixel
// Configura o PIO e a máquina de estados para controlar os LEDs
void npInit();

// Define a cor de um LED específico na matriz
// Parâmetros:
// - index: Índice do LED (0 a LED_COUNT-1)
// - r: Valor de vermelho (0-255)
// - g: Valor de verde (0-255)
// - b: Valor de azul (0-255)
void npSetLED(uint index, uint8_t intensidade);

// Limpa a matriz de LEDs, definindo todas as cores como preto (0, 0, 0)
void npClear();

// Envia os dados do buffer de pixels para os LEDs NeoPixel
// Esta função deve ser chamada após definir as cores dos LEDs para atualizar a matriz
void npWrite();

// Função para exibir sprites na matriz de LEDs
// Parâmetros:
// - sprite: Matriz 5x5x3 contendo os valores de cor (R, G, B) para cada LED
void display_sprite(const int sprite[5][5][3]);

// Função para converter coordenadas (x, y) em um índice linear
// Útil para mapear coordenadas de uma matriz 5x5 para o vetor de LEDs
// Parâmetros:
// - x: Coordenada X (0 a 4)
// - y: Coordenada Y (0 a 4)
// Retorna:
// - Índice linear correspondente (0 a LED_COUNT-1)
int getIndex(int x, int y);

#endif