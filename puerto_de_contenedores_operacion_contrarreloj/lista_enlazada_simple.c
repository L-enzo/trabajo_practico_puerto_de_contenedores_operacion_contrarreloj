#include "lista_enlazada_simple.h"

#define MINIMO(X,Y) ((X)<=(Y) ? (X) : (Y))

void crearLista(tLista *pl)
{
    *pl = NULL;
}

int listaVacia(const tLista *pl)
{
    return *pl == NULL;
}


int listaLlena(const tLista *pl, unsigned cantBytes)
{
    return 0;
}

void vaciarLista(tLista *pl)
{
    tNodoLista *aux;

    while(*pl)
    {
        aux = *pl;
        *pl = (*pl)->sig;
        free(aux->info);
        free(aux);
    }
}

int ponerAlFinal(tLista *pl, const void *dato, unsigned tam)
{
    tNodoLista* nuevo;

    while(*pl)
    {
        pl = &(*pl)->sig;
    }
    nuevo = malloc(sizeof(tNodoLista));
    if(nuevo == NULL)
    {
        return SIN_MEM;
    }
    nuevo->info = malloc(tam);
    if(nuevo->info == NULL)
    {
        free(nuevo);
        return SIN_MEM;
    }

    nuevo->sig = NULL;
    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo=tam;
    *pl = nuevo;
    return TODO_OK_LISTA;
}

int mostrarLista(const tLista *pl, void (*mostrar)(const void*))
{
    if(*pl == NULL)
    {
        return SIN_ELEM;
    }
    while(*pl)
    {
        mostrar((*pl)->info);
        pl = &(*pl)->sig;
    }
    printf("\n");
    return TODO_OK_LISTA;
}

int insertarOrdenado(tLista *pl, const void *dato, unsigned tam,int (*cmp)(const void *, const void *),
                     void (*accion)(void*), unsigned duplicado)
{
    tNodoLista* nodo;
    while(*pl && cmp(dato, (*pl)->info) > 0)
    {
        pl = &(*pl)->sig;
    }
    if(*pl && duplicado && cmp(dato, (*pl)->info) == 0)
    {
        if(accion)
        {
            accion((*pl)->info);
        }
        return ERROR_DUPLICADO;
    }
    nodo = malloc(sizeof(tNodoLista));
    if(nodo == NULL)
    {
        return SIN_MEM;
    }
    nodo->info = malloc(tam);
    if(nodo->info == NULL)
    {
        free(nodo);
        return SIN_MEM;
    }

    memcpy(nodo->info, dato, tam);
    nodo->tamInfo = tam;

    nodo->sig = *pl;
    *pl= nodo;

    return TODO_OK_LISTA;
}

void mapeoLista(tLista *pl, void (*accion)(void*))
{
    while(*pl)
    {
        accion((*pl)->info);
        pl = &(*pl)->sig;
    }
}
