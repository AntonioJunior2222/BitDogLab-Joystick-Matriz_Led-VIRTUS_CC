#ifndef TEST_JOYSTICK_H
#define TEST_JOYSTICK_H

#include <math.h>              // Para funções matemáticas (ex.: fabs, sqrt)
#include <stdlib.h>            // Para funções de utilidade geral (ex.: abs, malloc)
#include "pico/stdlib.h"       // Biblioteca padrão do Raspberry Pi Pico (GPIO, timing)
#include "hardware/adc.h"      // Controle do conversor analógico-digital (ADC)
#include "libs/joystick_lib.h" // Biblioteca do joystick (leitura e normalização)
#include "libs/malha_led.h"    // Biblioteca da Malha de LED

// =============================================
// Protótipos das Funções de Teste
// =============================================

// Teste de inicialização do hardware
// Verifica se o ADC e GPIO foram configurados corretamente
// Exibe resultados no terminal e usa o LED para feedback visual
void test_init(void);

// Teste de leitura bruta do ADC
// Realiza múltiplas leituras dos eixos X e Y do joystick
// Verifica se os valores estão dentro da faixa esperada (0-4095 para 12 bits)
// Exibe os valores no terminal e usa o LED para indicar sucesso/falha
void test_adc_raw(void);

// Teste de normalização dos valores
// Verifica se os valores dos eixos X e Y estão sendo normalizados corretamente
// para o intervalo de -100 a 100
// Exibe os valores normalizados no terminal e usa o LED para feedback
void test_normalizacao(void);

// Teste de funcionamento do botão
// Verifica se o botão do joystick está sendo detectado corretamente
// Aguarda o pressionamento do botão por um tempo limite (5 segundos)
// Exibe o estado do botão no terminal e usa o LED para feedback
void test_botao(void);

#endif // TEST_JOYSTICK_H