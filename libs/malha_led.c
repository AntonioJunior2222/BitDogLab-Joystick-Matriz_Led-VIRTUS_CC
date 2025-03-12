#include "malha_led.h"
#include "ws2818b.pio.h"

// Variáveis globais (visíveis apenas neste arquivo)
static PIO np_pio;       // Instância do PIO usada para controlar os LEDs
static uint sm;          // Máquina de estados do PIO
static npLED_t leds[LED_COUNT]; // Buffer de pixels para os LEDs
uint8_t tema_cor[3] = {255, 0, 0}; // Verde (R=255, G=0, B=0)

// Inicializa a matriz de LEDs
void npInit() {
    uint offset = pio_add_program(pio0, &ws2818b_program); // Adiciona o programa PIO
    np_pio = pio0; // Usa PIO0 como padrão

    sm = pio_claim_unused_sm(np_pio, false); // Tenta obter uma máquina de estados livre
    if (sm < 0) { // Se não houver máquinas livres no PIO0, usa PIO1
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true); // Obtém uma máquina no PIO1 (panico se não houver)
    }

    // Inicializa o programa PIO na máquina de estados
    ws2818b_program_init(np_pio, sm, offset, LED_PIN, 800000.f);
    npClear(); // Limpa a matriz de LEDs
}

// Define a cor de um LED específico
void npSetLED(uint index, uint8_t intensidade) {
    leds[index].R = (tema_cor[0] * intensidade) / 255;
    leds[index].G = (tema_cor[1] * intensidade) / 255;
    leds[index].B = (tema_cor[2] * intensidade) / 255;
}
// Limpa todos os LEDs (define todas as cores como preto)
void npClear() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        npSetLED(i, 0);
    }
}

// Envia os dados do buffer para os LEDs
void npWrite() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G); // Envia componente verde
        pio_sm_put_blocking(np_pio, sm, leds[i].R); // Envia componente vermelho
        pio_sm_put_blocking(np_pio, sm, leds[i].B); // Envia componente azul
    }
    sleep_us(100); // Aguarda o sinal de RESET do protocolo WS2812B
}

// Converte coordenadas (x, y) em um índice linear
int getIndex(int x, int y) {
    if (y % 2 == 0) {
        return 24 - (y * 5 + x); // Linhas pares: esquerda para direita
    } else {
        return 24 - (y * 5 + (4 - x)); // Linhas ímpares: direita para esquerda
    }
}

// Exibe um sprite na matriz de LEDs
void display_sprite(const int sprite[5][5][3]) {
    for (int linha = 0; linha < 5; linha++) {
        for (int coluna = 0; coluna < 5; coluna++) {
            int posicao = getIndex(linha, coluna);
            uint8_t intensidade = sprite[coluna][linha][0]; // Assume que o sprite usa o primeiro valor para intensidade
            npSetLED(posicao, intensidade);
        }
    }
    npWrite();
}


void set_cor(uint8_t r, uint8_t g, uint8_t b){
    tema_cor[0] = r;   // R
    tema_cor[1] = g; // G
    tema_cor[2] = b;   // B
}