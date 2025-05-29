#ifndef PILA_H
#define PILA_H

#define TAM_MAX 100

// Estructura que almacena dos valores enteros
typedef struct {
    int x;
    int y;
} ParEnteros;

// Estructura para la pila
typedef struct {
    ParEnteros elementos[TAM_MAX];
    int tope;
} Pila;

// Funciones disponibles
void inicializar(Pila *p);
int estaVacia(Pila *p);
int estaLlena(Pila *p);
int apilar(Pila *p, int x, int y);
int desapilar(Pila *p, ParEnteros *salida);
int verTope(Pila *p, ParEnteros *salida);
int tamanio(const Pila *p); 
#endif
