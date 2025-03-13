#include "Testjoystick.h"
#include "libs/joystick_lib.h"
#include "libs/direcoes.h"

// Teste 1: Verifica inicialização do ADC e GPIO
void test_init() {
    set_cor(0,255,0);
    printf("\n=== Teste 1: Inicializacao ===\n");
    
    // Verifica configuração ADC
    adc_init();
    printf("ADC inicializado: %s\n", adc_hw->cs & ADC_CS_EN_BITS ? "OK" : "FALHA");

    // Verifica GPIO do botão
    bool sw_state = gpio_get(SW);
    printf("Botao SW (GPIO22): %s\n", sw_state ? "HIGH (OK)" : "LOW (FALHA)");
    if(sw_state == 1){
        set_cor(0,255,0);
        npSetLED(12,100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }else {
        set_cor(255, 0, 0);
        npSetLED(12,100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }
    
}

// Teste 2: Verifica leitura bruta do ADC
void test_adc_raw() {
    printf("\n=== Teste 2: Leitura Bruta ADC ===\n");
    bool success = true;
    
    for(int i = 0; i < 10; i++) {
        joystick_captura();
        uint16_t x = get_joystick_x_puro();
        uint16_t y = get_joystick_y_puro();
        
        printf("Leitura %d: X=%4u, Y=%4u\n", i+1, x, y);
        
        if(x == 0 || x > 4095 || y == 0 || y > 4095) {
            success = false;  
        }
    }
    
    printf("Resultado: %s\n", success ? "OK" : "FALHA");
    if(success == 1){
        set_cor(0,255,0);
        npSetLED(12,100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }else {
        set_cor(255, 0, 0);
        npSetLED(12,100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }
}

// Teste 3: Verifica normalização dos valores
void test_normalizacao() {
    printf("\n=== Teste 3: Normalizacao ===\n");
    
    joystick_captura();
    normalizar_joystick();
    
    int16_t x_norm = get_joystick_x_norm();
    int16_t y_norm = get_joystick_y_norm();
    
    printf("Valores Normalizados: X=%4d, Y=%4d\n", x_norm, y_norm);
    
    bool success = (abs(x_norm) <= 100) && (abs(y_norm) <= 100);
    printf("Resultado: %s\n", success ? "OK" : "FALHA");
    
    if(success == 1){
        set_cor(0,255,0);
        npSetLED(12, 100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }else {
        set_cor(255, 0, 0);
        npSetLED(12, 100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }
}

// Teste 4: Verifica detecção do botão
void test_botao() {
    printf("\n=== Teste 4: Botao ===\n");
    printf("Pressione e solte o botao SW...\n");
    
    bool pressed = false;
    absolute_time_t start = get_absolute_time();
    
    while(absolute_time_diff_us(start, get_absolute_time()) < 5000000) { // 5 segundos
        if(!gpio_get(SW)) {
            pressed = true;
            break;
        }
    }
    
    printf("Botao %s\n", pressed ? "PRESSIONADO (OK)" : "NAO DETECTADO (FALHA)");
    if(pressed == 1){
        set_cor(0,255,0);
        npSetLED(12, 100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }else {
        set_cor(255, 0, 0);
        npSetLED(12, 100);
        npWrite();
        sleep_ms(1500);
        npSetLED(12, 0);
        npWrite();
        sleep_ms(3000);
    }
}

void test_completo(){
    while(true){
        if(testing == 0) break;
        test_init();
        if(testing == 0) break;
        test_adc_raw();
        if(testing == 0) break;
        test_normalizacao();
        if(testing == 0) break;
        test_botao();
        printf("\n=== Ciclo de Testes Concluido ===\n");
        sleep_ms(2000);
    }
}

void test_display(){
    while(true){
        if(testing == 1) break;
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
