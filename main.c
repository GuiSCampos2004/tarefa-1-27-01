#include <stdio.h>
#include "pico/stdlib.h"
#include "pixel.h"

const uint botao_a = 5;
const uint botao_b = 6;
const uint pixel = 7;
const uint led_r = 13;

uint8_t contador=0;

static volatile uint32_t ultimo_tempo = 0;

//-----------------------------------------------------------------------------------------------------------
static void gpio_irq_handler(uint gpio, uint32_t events){ //Função para interrupção

    uint32_t tempo_atual = to_us_since_boot(get_absolute_time());

    if (tempo_atual - ultimo_tempo > 200000){ //Debounce evitando que algo seja realizado caso a interrupção ocorra numa frequencia alta
        ultimo_tempo = tempo_atual;
        if(gpio==5){ //Caso o botão A seja apertado, entra nesse if
            if (contador<9){//Impede que a contagem exceda o numero 9
                contador++;
                write(matriz[contador]);//Escreve na matriz de LED's
            }
        }else{ //Caso o botão B seja apertado, entra nesse else
            if (contador>0){//Impede que a contagem fique abaixo do numero 0
                contador--;
                write(matriz[contador]);//Escreve na matriz de LED's
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------------------
int main(){
    //------------------------------ Inicialização de portas
    pixel_init(pixel);

    gpio_init(botao_a);
    gpio_set_dir(botao_a, GPIO_IN);
    gpio_pull_up(botao_a);

    gpio_init(botao_b);
    gpio_set_dir(botao_a, GPIO_IN);
    gpio_pull_up(botao_b);
    
    
    gpio_init(led_r);
    gpio_set_dir(led_r, GPIO_OUT);
    gpio_put(led_r,0);
    //------------------------------
    
    //Configuração de interrupção
    gpio_set_irq_enabled_with_callback(botao_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botao_b, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    write(matriz[contador]);//Escreve na matriz de LED's

    while (true)
    {
        gpio_put(led_r, 1);
        sleep_ms(100);
        gpio_put(led_r, 0);
        sleep_ms(100);
    }
}