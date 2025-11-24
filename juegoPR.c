// juegoPR.c (C89 compatible)
#include "raylib.h"
#include "obstaculosPR.h"
#include <stdio.h>

/*  
   No usamos stdbool.h porque C89 no lo soporta.
   Reemplazamos bool con int.
*/

int main(void)
{
    /* Inicializa ventana */
    InitWindow(800, 450, "FloppyBird UNNE - Fixed");
    SetTargetFPS(60);

    /* Inicializa sistema de puntajes y juego */
    cargarPuntajes();    /* Carga lista desde disco */
    iniciarJuego();      /* Prepara variables iniciales */

    /* Bucle principal */
    while (!WindowShouldClose() && !juegoDebeCerrar())
    {
        actualizarDibujarFrame();
    }

    /* Al salir del bucle */
    guardarPuntajes();    /* Guarda el archivo */
    destruirPuntajes();   /* Libera la memoria */

    CloseWindow();        /* Cierra Raylib */

    return 0;
}
