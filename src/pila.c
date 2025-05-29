#include <stdio.h>
#include "pila.h"

void inicializar(Pila *p) {
    p->tope = -1;
}

int estaVacia(Pila *p) {
    return p->tope == -1;
}

int estaLlena(Pila *p) {
    return p->tope == TAM_MAX - 1;
}

int apilar(Pila *p, int x, int y) {
    if (estaLlena(p)) {
        return 0;
    }
    p->tope++;
    p->elementos[p->tope].x = x;
    p->elementos[p->tope].y = y;
    return 1;
}

int desapilar(Pila *p, ParEnteros *salida) {
    if (estaVacia(p)) {
        return 0;
    }
    *salida = p->elementos[p->tope];
    p->tope--;
    return 1;
}
int tamanio(const Pila *p)
{
    /*  Si la pila está vacía, p->tope == -1.
        El número de elementos siempre es tope + 1. */
    return p->tope + 1;
}

int verTope(Pila *p, ParEnteros *salida) {
    if (estaVacia(p)) {
        return 0;
    }
    *salida = p->elementos[p->tope];
    return 1;
}