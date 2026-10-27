#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define ERROR_MEM -1
#define ERROR_COLA_VACIA -2

typedef struct sNodo {
                        void* info;
                        unsigned tam;
                        struct sNodo* sig;
}tNodo;

typedef struct{
                tNodo* pri, *ult;
} tCola;

void crearCola(tCola *pc);
void vaciarCola(tCola *pc);
int siColaLlena(const tCola *pc, unsigned tam);
int siColaVacia(const tCola *pc);
int acolar(tCola *pc, const void *dato, unsigned tam);
int desAcolar(tCola *pc, void *dato, unsigned tam);
int verPrimero(const tCola *pc, void *dato, unsigned tam);


#endif // COLADINAMICA_H_INCLUDED
