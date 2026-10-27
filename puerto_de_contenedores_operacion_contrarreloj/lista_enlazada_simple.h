#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK_LISTA 1
#define SIN_MEM -1
#define SIN_ELEM -2
#define DUPLI_SI 1
#define DUPLI_NO 0
#define ERROR_DUPLICADO -3

typedef struct sNodoLista
{
    void *info;
    unsigned tamInfo;
    struct sNodoLista *sig;
}tNodoLista;

typedef tNodoLista *tLista;

void crearLista(tLista *pl);
void vaciarLista(tLista *pl);

int listaVacia(const tLista *pl);
int listaLlena(const tLista *pl, unsigned cantBytes);

int mostrarLista(const tLista *pl, void (*mostrar)(const void*));
int ponerAlFinal(tLista *pl, const void *dato, unsigned tam);
int insertarOrdenado(tLista *pl, const void *dato, unsigned tam, int (*cmp)(const void *, const void *), void (*accion)(void*), unsigned duplicado);
void mapeoLista(tLista *pl, void (*accion)(void*));
#endif // HEADER_H_INCLUDED
