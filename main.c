#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sistema.h"
#include "movimientos.h"
#include "obstaculos.h"

#define ANCHO 20
#define ALTO 15

int main() {
    char avatar[8];
    char eleccion;
    int puntaje = 0;
    int salir = 0;

    printf("=== JUEGO TERMINAL ===\n");

    while (!salir) {
        printf("\nMenu principal:\n");
        printf("1. Elegir avatar\n");
        printf("2. Jugar\n");
        printf("3. Ver puntaje\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf(" %c", &eleccion);

        switch (eleccion) {
            case '1':
                elegirAvatar(avatar);
                break;
            case '2':
                puntaje = iniciarJuego(avatar, ANCHO, ALTO);
                break;
            case '3':
                printf("Puntaje actual: %d\n", puntaje);
                break;
            case '4':
                salir = 1;
                printf("Saliendo del juego...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    }

    return 0;
}
