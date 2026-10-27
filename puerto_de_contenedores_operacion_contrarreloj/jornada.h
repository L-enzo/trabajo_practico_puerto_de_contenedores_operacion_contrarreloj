#ifndef JORNADA_H_INCLUDED
#define JORNADA_H_INCLUDED

#include "coladinamica.h"
#include "lista_enlazada_simple.h"

#define LIM_INF_MENU 0
#define LIM_SUP_MENU 2
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
void jornada();
int cargarPuerto(tJornada *j);
void asignarBuque(char* linea, tLista * lista);
#endif // JORNADA_H_INCLUDED
