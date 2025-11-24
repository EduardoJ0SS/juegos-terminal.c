//puntajesPR.h
#ifndef PUNTAJES_H
#define PUNTAJES_H

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCORE_FILE "scores.dat"

// CORRECCIÓN: Definición correcta de struct recursivo
typedef struct nodo {
    int puntaje;
    struct nodo *siguiente;
} tNodo;

// Variable global estática para la lista
static tNodo *listaPuntajes = NULL;

// --- agregarPuntaje ---
void agregarPuntaje(int puntos) {
    // CORRECCIÓN: Sintaxis correcta de malloc
    tNodo *nuevo = (tNodo*)malloc(sizeof(tNodo));
    if (!nuevo) return;
    
    nuevo->puntaje = puntos;
    nuevo->siguiente = NULL;

    // Si la lista está vacía o el nuevo es mayor al primero (orden descendente)
    if (listaPuntajes == NULL || puntos >= listaPuntajes->puntaje) {
        nuevo->siguiente = listaPuntajes;
        listaPuntajes = nuevo;
        return;
    }

    tNodo *act = listaPuntajes;
    while (act->siguiente != NULL && act->siguiente->puntaje > puntos) {
        act = act->siguiente;
    }

    nuevo->siguiente = act->siguiente;
    act->siguiente = nuevo;
}

// --- destruirPuntajes (Libera memoria) ---
void destruirPuntajes(void) {
    tNodo *temp;
    while (listaPuntajes != NULL) {
        temp = listaPuntajes;
        listaPuntajes = listaPuntajes->siguiente;
        free(temp);
    }
    listaPuntajes = NULL;
}

// --- dibujarPuntajes ---
void dibujarPuntajes(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("PUNTAJES GUARDADOS:", 260, 40, 25, BLACK);

    int y = 100;
    tNodo *act = listaPuntajes;
    int n = 1;

    if (act == NULL) {
        DrawText("No hay puntajes guardados.", 250, 150, 20, DARKGRAY);
    }

    while (act != NULL) {
        DrawText(TextFormat("%d) %d puntos", n, act->puntaje), 320, y, 20, GRAY);
        act = act->siguiente;
        y += 30;
        n++;
        if (y > 400) break; // Evitar escribir fuera de pantalla
    }

    DrawText("BACKSPACE para volver", 280, 420, 20, GRAY);
    EndDrawing();
}

// --- guardarPuntajes ---
void guardarPuntajes(void) {
    FILE *f = fopen(SCORE_FILE, "wb");
    if (!f) return;

    tNodo *act = listaPuntajes;
    while (act != NULL) {
        fwrite(&act->puntaje, sizeof(int), 1, f);
        act = act->siguiente;
    }

    fclose(f);
}

// --- cargarPuntajes ---
void cargarPuntajes(void) {
    FILE *f = fopen(SCORE_FILE, "rb");
    if (!f) return; // Si no existe el archivo, no pasa nada

    // Aseguramos que la lista esté limpia antes de cargar
    destruirPuntajes(); 

    int puntos;
    while (fread(&puntos, sizeof(int), 1, f) == 1) {
        agregarPuntaje(puntos);
    }

    fclose(f);
}

#endif
