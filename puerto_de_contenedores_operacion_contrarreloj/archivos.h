#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TODO_OK_ARCH 1
#define ERROR_APERT_ARCH -1
#define ERROR_RESERV_MEM -2

typedef struct {
                int duracion_jornada_minutos,
                    muelles,
                    zonas,
                    capacidad_pila,
                    maximo_buques,
                    maximo_cont_x_buque,
                    maximo_camiones,
                    tiempo_desc_contenedor,
                    tiempo_reub_contenedor,
                    tiempo_carg_camion;
}tPuerto;

int generar_archivo_puerto(const char *nombrearchivo);
#endif // ARCHIVOS_H_INCLUDED
