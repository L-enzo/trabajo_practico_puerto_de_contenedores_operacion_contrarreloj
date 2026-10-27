#include "coladinamica.h"

#define MINIMO(X,Y) ((X)<=(Y)?(X):(Y))

void crearCola(tCola* pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}

void vaciarCola(tCola* pc)
{
    tNodo * aux;
    while(pc->pri)
    {
        aux = pc->pri;
        pc->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    pc->ult = NULL;
}

int siColaLlena(const tCola* pc, unsigned tam)
{
    return 0;
}

int siColaVacia(const tCola* pc)
{
    return pc->pri == NULL;
}


int acolar(tCola* pc, const void* dato, unsigned tam)
{
    tNodo* nodo = malloc(sizeof(tNodo));
    if(nodo == NULL)
    {
        return ERROR_MEM;
    }
    nodo->info = malloc(tam);
    if(nodo->info == NULL)
    {
        free(nodo);
        return ERROR_MEM;
    }
    memcpy(nodo->info, dato, tam);
    nodo->tam = tam;
    nodo->sig = NULL;
    if(pc->ult)
    {
        pc->ult->sig = nodo;
    }
    else
    {
        pc->pri = nodo;
    }
    pc->ult = nodo;
    return TODO_OK;
}

int desAcolar(tCola* pc, void* dato, unsigned tam)
{
    tNodo* aux = pc->pri;
    if(aux == NULL)
    {
        return ERROR_COLA_VACIA;
    }
    memcpy(dato, aux->info, MINIMO(tam, aux->tam));
    pc->pri = aux->sig;
    free(aux->info);
    free(aux);
    if(pc->pri == NULL)
    {
        pc->ult = NULL;
    }
    return TODO_OK;
}

int verPrimero(const tCola* pc, void* dato, unsigned tam)
{
    if(pc->pri == NULL)
    {
        return ERROR_COLA_VACIA;
    }
    memcpy(dato, pc->pri->info, MINIMO(tam, pc->pri->tam));
    return TODO_OK;
}
