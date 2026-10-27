#ifndef JORNADA_H_INCLUDED
#define JORNADA_H_INCLUDED

#include "coladinamica.h"
#include "lista_enlazada_simple.h"

#define LIM_INF_MENU 0
#define LIM_SUP_MENU 2
#define TODO_OK_JORNADA 1
typedef struct {
                int Jor,
                    Mue,
                    Zon,
                    capPila;
} tJornada;

typedef struct
{
    char codigo[5];
    unsigned tiempo;
    tCola cola;
} tVehiculo;

void menu();
int jornada();
int cargarPuerto(tJornada* j, tLista* listaBuques, tLista* listaCamiones);
int asignarBuque(char* linea, tLista* listaBuques);
int AsignarCamion(char* linea, tLista* listaCamiones);
void liberarColaVehiculo(void *dato);
#endif // JORNADA_H_INCLUDED
