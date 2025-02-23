#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "inc/matriz_rgb.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

// Definições para a comunicação I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C // Endereço do display OLED

const uint led_pin_red = 13;   // LED vermelho na GPIO13
const uint microfone = 28;     // GPIO28 para ADC2 (Microfone)
const uint limiar = 2200;      // Limiar para o LED vermelho
const uint button_A = 5; // Botão A = 5, Botão B = 6 
const uint button_B = 6; // Botão A = 5, Botão B = 6 

const uint amostras_por_segundo = 8000; // Frequência de amostragem (8 kHz)

bool estado_pisca = false;
uint64_t tempo_anterior = 0;
const uint64_t intervalo_pisca = 100000; // 500ms (tempo de piscar)

bool estado_automatico = true;
int estado_matriz = 0;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 350000) // 350 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        if (gpio == button_A) {
            estado_automatico = !estado_automatico;
            if (estado_automatico) printf("Estado automático \n ");
            else  printf("Estado manual \n ");
        }
        else if (gpio == button_B) {
            if (estado_automatico == 0) {
                if (estado_matriz == 0 ) estado_matriz = 1;
                else if (estado_matriz == 1 ) estado_matriz = 2;
                else if (estado_matriz == 2 ) estado_matriz = 0;
            }
        }                             
    }
}

int main() {
    // Inicializa a comunicação serial
    stdio_init_all();
    
    // Inicializa o LED vermelho
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    // Inicializa a matriz de LEDs
    npInit(LED_PIN);

    // Inicializa o ADC
    adc_init();
    adc_gpio_init(microfone);

    // Inicializa o botão
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_A);          // Habilita o pull-up interno

    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_B);          // Habilita o pull-up interno

    // Inicializa a comunicação I2C a 400 kHz
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização do display OLED
    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd);

    bool cor = true;

    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Define o intervalo entre amostras
    uint64_t intervalo_us = 1000000 / amostras_por_segundo;

    while (true) {

        // estado automatico (variando com a leitura do microfone)
        if (estado_automatico == true) {
            // Leitura do microfone
            adc_select_input(2);
            uint16_t mic_value = adc_read();

            // Exibe o valor do microfone no monitor serial
            // printf("Microfone ADC: %d\n", mic_value);

            uint64_t tempo_atual = time_us_64();

            // Controle do LED vermelho baseado no valor do microfone
            if (mic_value < limiar-100) {
                gpio_put(led_pin_red, false);  // LED vermelho apagado
                acender_matriz();  // Matriz apagada
            }
            else {
                gpio_put(led_pin_red, true);   // LED vermelho aceso
                
                // Controla o piscar do LED vermelho sem bloquear a leitura do microfone
                if (tempo_atual - tempo_anterior >= intervalo_pisca) {
                    estado_pisca = !estado_pisca;  // Alterna entre ligado/desligado
                    tempo_anterior = tempo_atual;

                    if (estado_pisca) {
                        acender_matriz();
                    } else {
                        apagar_matriz();
                    }
                }
            }
            // Delay para manter a taxa de amostragem do microfone
            sleep_us(intervalo_us);

            // Atualiza o conteúdo do display com animações
            ssd1306_fill(&ssd, !cor); // Limpa o display
            ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 0); // Desenha uma string
            ssd1306_draw_string(&ssd, "MODO", 15, 18); // Desenha uma string      
            ssd1306_draw_string(&ssd, "AUTOMATICO", 15, 28); // Desenha uma string 
            ssd1306_send_data(&ssd); // Atualiza o display
        }

        //estado manual (botão B seleciona modo da matriz)
        else {
            // Atualiza o conteúdo do display com animações
            ssd1306_fill(&ssd, !cor); // Limpa o display
            ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 0); // Desenha uma string
            ssd1306_draw_string(&ssd, "MODO MANUAL", 15, 18); // Desenha uma string  

            if (estado_matriz == 0) {
                gpio_put(led_pin_red, true);
                printf("Matriz ligada \n ");
                acender_matriz();

                ssd1306_draw_string(&ssd, "FAROL ON", 15, 28); // Desenha uma string 
            } else if (estado_matriz == 1) {
                
                printf("Matriz piscando \n ");
                
                uint64_t tempo_atual = time_us_64();

                // Controla o piscar do LED vermelho sem bloquear a leitura do microfone
                if (tempo_atual - tempo_anterior >= intervalo_pisca) {
                    estado_pisca = !estado_pisca;  // Alterna entre ligado/desligado
                    tempo_anterior = tempo_atual;

                    if (estado_pisca) {
                        gpio_put(led_pin_red, true);   // LED vermelho aceso
                        acender_matriz();
                    } else {
                        gpio_put(led_pin_red, false);   // LED vermelho aceso
                        apagar_matriz();
                    }
                }
                ssd1306_draw_string(&ssd, "FAROL PISCA", 15, 28); // Desenha uma string

            } else if (estado_matriz == 2) {
                gpio_put(led_pin_red, false);
                printf("Matriz apagada \n ");
                apagar_matriz();
                ssd1306_draw_string(&ssd, "FAROL OFF", 15, 28); // Desenha uma string
            }
                
            ssd1306_send_data(&ssd); // Atualiza o display
        }
    }
    return 0;
}
