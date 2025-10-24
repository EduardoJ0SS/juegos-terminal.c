#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sistema.h"
#include "movimientos.h"

int iniciarJuego(char avatar[8], int ancho, int alto) {
    int posX = ancho / 2;
    int puntaje = 0;
    int obstX = rand() % (ancho - 2) + 1;
    int obstY = 0;

    srand(time(NULL));

    while (1) {
        limpiarPantalla();

        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                if (x == 0 || x == ancho - 1) printf("|");
                else if (y == obstY && x == obstX) printf("X");
                else if (y == alto - 1 && x == posX) printf("%s", avatar);
                else printf(" ");
            }
            printf("\n");
        }

        esperar(150);
        posX = moverJugador(posX, ancho);

        obstY++;
        if (obstY >= alto) {
            obstY = 0;
            obstX = rand() % (ancho - 2) + 1;
            puntaje++;
        }

        if (obstY == alto - 1 && obstX == posX) {
            printf("\n¡Colisión! Puntaje final: %d\n", puntaje);
            esperar(1000);
            break;
        }
    }

    return puntaje;
}

#endif
