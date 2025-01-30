#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>

// Definição do pixel/LED
extern uint8_t matriz[10][5][5][3];

//Declaraão de funções
void pixel_init(uint8_t pin);
void write(uint8_t matriz[5][5][3]);

#endif // PIXEL_H
