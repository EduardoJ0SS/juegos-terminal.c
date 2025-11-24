// obstaculosPR.c

#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>    
#include "puntajesPR.h"

#define MAX_TUBES 100
#define FLOPPY_RADIUS 24
#define TUBES_WIDTH 80

/*--Variables globales--*/
static const int screenWidth = 800;
static const int screenHeight = 450;

static int finJuego = 0;
static int pausa = 0;
static int puntaje = 0;
static int mejorPuntaje = 0;

/*--Estructuras--*/
typedef struct Disco {
    Vector2 posicion;
    float radio;
    Color color;
} Disco;

typedef struct Tubo {
    Rectangle rec;
    Color color;
    int activo;
} Tubo;

static Disco disco = {0};
static Tubo tubos[MAX_TUBES * 2] = {0};
static Vector2 posTubos[MAX_TUBES] = {0};

static float velTubos = 0;
static int efectoSuper = 0;

/*--Enum Pantalla--*/
typedef enum PantallaJuego { MENU_PRINCIPAL, JUGANDO, PANTALLA_PUNTAJES, SALIR }
PantallaJuego;

static PantallaJuego pantallaActual = MENU_PRINCIPAL;

/*--Prototipos--*/
void iniciarJuego(void);
void actualizarJuego(void);
void dibujarJuego(void);
int  juegoDebeCerrar(void);
void actualizarDibujarFrame(void);

/*--IMPLEMENTACIONES--*/
void iniciarJuego(void)
{
    int i;

    disco.radio = (float)FLOPPY_RADIUS;
    disco.posicion.x = 80;
    disco.posicion.y = screenHeight / 2.0f - disco.radio;

    velTubos = 200.0f;
    puntaje = 0;
    finJuego = 0;
    efectoSuper = 0;
    pausa = 0;

    /* inicializar posiciones */
    for (i = 0; i < MAX_TUBES; i++) {
        posTubos[i].x = (float)(400 + 280 * i);
        posTubos[i].y = -(float)GetRandomValue(0, 120);
    }

    for (i = 0; i < MAX_TUBES * 2; i += 2) {
        int idx = i / 2;

        /* tubo arriba */
        tubos[i].rec.x = posTubos[idx].x;
        tubos[i].rec.y = posTubos[idx].y;
        tubos[i].rec.width = TUBES_WIDTH;
        tubos[i].rec.height = 255;
        tubos[i].activo = 1;

        /* tubo abajo */
        tubos[i + 1].rec.x = posTubos[idx].x;
        tubos[i + 1].rec.y = 640 + posTubos[idx].y - 255;
        tubos[i + 1].rec.width = TUBES_WIDTH;
        tubos[i + 1].rec.height = 255;
        tubos[i + 1].activo = 1;
    }
}

void actualizarJuego(void)
{
    int i;

    if (!finJuego) {

        if (IsKeyPressed('P'))
            pausa = !pausa;

        if (!pausa) {

            float dt = GetFrameTime();

            /* mover tubos */
            for (i = 0; i < MAX_TUBES; i++) {
                posTubos[i].x -= velTubos * dt;
            }

            /* actualizar rectángulos */
            for (i = 0; i < MAX_TUBES; i++) {
                tubos[i * 2].rec.x = posTubos[i].x;
                tubos[i * 2 + 1].rec.x = posTubos[i].x;
            }

            /* movimiento del disco */
            if (IsKeyDown(KEY_SPACE))
                disco.posicion.y -= 350 * dt;
            else
                disco.posicion.y += 350 * dt;

            if (disco.posicion.y < 0)
                disco.posicion.y = 0;

            if (disco.posicion.y > screenHeight)
                disco.posicion.y = (float)screenHeight;

            /* reciclar tubos */
            for (i = 0; i < MAX_TUBES; i++) {

                if (posTubos[i].x + TUBES_WIDTH < -50) {

                    int anterior = (i == 0) ? MAX_TUBES - 1 : i - 1;

                    posTubos[i].x = posTubos[anterior].x + 280;
                    posTubos[i].y = -(float)GetRandomValue(0, 120);

                    tubos[i * 2].rec.y = posTubos[i].y;
                    tubos[i * 2 + 1].rec.y = 640 + posTubos[i].y - 255;

                    tubos[i * 2].activo = 1;
                    tubos[i * 2 + 1].activo = 1;
                }
            }

            /* colisiones */
            for (i = 0; i < MAX_TUBES; i++) {

                float tx = posTubos[i].x;
                int colA, colB;

                if (tx < screenWidth && tx > -100) {

                    colA = CheckCollisionCircleRec(disco.posicion, disco.radio, tubos[i * 2].rec);
                    colB = CheckCollisionCircleRec(disco.posicion, disco.radio, tubos[i * 2 + 1].rec);

                    if (colA || colB) {
                        finJuego = 1;
                        pausa = 0;
                        agregarPuntaje(puntaje);

                        if (puntaje > mejorPuntaje)
                            mejorPuntaje = puntaje;
                    }

                    if ((tx < disco.posicion.x - disco.radio) &&
                        tubos[i * 2].activo &&
                        !finJuego)
                    {
                        puntaje += 100;
                        tubos[i * 2].activo = 0;
                        tubos[i * 2 + 1].activo = 0;

                        efectoSuper = 1;
                        velTubos += 2.0f;
                    }
                }
            }
        }

    } else {

        if (IsKeyPressed(KEY_ENTER)) {
            iniciarJuego();
        }
        else if (IsKeyPressed(KEY_BACKSPACE)) {
            pantallaActual = MENU_PRINCIPAL;
        }
    }
}

void dibujarJuego(void)
{
    int i;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!finJuego) {

        DrawCircleV(disco.posicion, disco.radio, MAROON);

        for (i = 0; i < MAX_TUBES; i++) {
            DrawRectangleRec(tubos[i * 2].rec, DARKGRAY);
            DrawRectangleRec(tubos[i * 2 + 1].rec, DARKGRAY);
            DrawRectangleLinesEx(tubos[i * 2].rec, 2, BLACK);
            DrawRectangleLinesEx(tubos[i * 2 + 1].rec, 2, BLACK);
        }

        if (efectoSuper) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(SKYBLUE, 0.4f));
            efectoSuper = 0;
        }

        DrawText(TextFormat("PUNTAJE: %04i", puntaje), 20, 20, 30, BLACK);
        DrawText(TextFormat("MEJOR: %04i", mejorPuntaje), 20, 60, 20, DARKGRAY);

        if (pausa)
            DrawText("PAUSA", 350, 200, 40, RED);

    } else {

        DrawText("GAME OVER", 280, 150, 50, RED);
        DrawText(TextFormat("Puntaje Final: %04i", puntaje), 300, 220, 30, BLACK);
        DrawText("ENTER: Reiniciar  |  BACKSPACE: Menu", 190, 300, 20, DARKGRAY);
    }

    EndDrawing();
}

int juegoDebeCerrar(void)
{
    return (pantallaActual == SALIR);
}

void actualizarDibujarFrame(void)
{
    BeginDrawing();

    switch (pantallaActual) {

    case MENU_PRINCIPAL:

        ClearBackground(RAYWHITE);
        DrawText("FLOPPY BIRD", 260, 80, 50, MAROON);
        DrawText("1 - JUGAR", 350, 200, 20, DARKGRAY);
        DrawText("2 - PUNTAJES", 350, 240, 20, DARKGRAY);
        DrawText("3 - SALIR", 350, 280, 20, DARKGRAY);
        DrawText("UNNE - Kavid Edition", 10, 420, 10, LIGHTGRAY);

        if (IsKeyPressed(KEY_ONE)) {
            iniciarJuego();
            pantallaActual = JUGANDO;
        }
        else if (IsKeyPressed(KEY_TWO)) {
            pantallaActual = PANTALLA_PUNTAJES;
        }
        else if (IsKeyPressed(KEY_THREE)) {
            pantallaActual = SALIR;
        }

        break;

    case JUGANDO:
        EndDrawing();  /* cerrar Begin previo */
        actualizarJuego();
        dibujarJuego();
        return;        /* evita segundo EndDrawing */

    case PANTALLA_PUNTAJES:

        EndDrawing();  /* cerrar Begin previo */
        dibujarPuntajes();

        if (IsKeyPressed(KEY_BACKSPACE))
            pantallaActual = MENU_PRINCIPAL;

        return;

    case SALIR:
        /* no dibuja nada */
        break;
    }

    EndDrawing();
}

#endif

