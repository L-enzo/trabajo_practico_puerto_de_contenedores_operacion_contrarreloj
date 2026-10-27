#include "archivos.h"

int generar_archivo_puerto(const char* nombrearchivo)
{
    tPuerto p;
    int cant_buques, cant_contenedores, num_contenedor = 1, cant_camiones,
    total_contenedores = 0, pos, i, f;
    int * usados;
    FILE* pf = fopen(nombrearchivo,"rt");
    if(pf == NULL)
    {
        return ERROR_APERT_ARCH;
    }

    fscanf(pf, "duracion_jornada_minutos: %d\n", &p.duracion_jornada_minutos);
    fscanf(pf, "cantidad_muelles: %d\n", &p.muelles);
    fscanf(pf, "cantidad_zonas_almacenamiento: %d\n", &p.zonas);
    fscanf(pf, "capacidad_pila: %d\n", &p.capacidad_pila);
    fscanf(pf, "maximo_buques: %d\n", &p.maximo_buques);
    fscanf(pf, "maximo_contenedores_por_buque: %d\n", &p.maximo_cont_x_buque);
    fscanf(pf, "maximo_camiones: %d\n", &p.maximo_camiones);
    fscanf(pf, "tiempo_descarga_contenedor: %d\n", &p.tiempo_desc_contenedor);
    fscanf(pf, "tiempo_reubicacion_contenedor: %d\n", &p.tiempo_reub_contenedor);
    fscanf(pf, "tiempo_carga_camion: %d\n", &p.tiempo_carg_camion);

    fclose(pf);

    pf = fopen("puerto.txt","wt");
    if(pf == NULL)
    {
        return ERROR_APERT_ARCH;
    }

    fprintf(pf, "JORNADA: %d\n", p.duracion_jornada_minutos);
    fprintf(pf, "MUELLES: %d\n", p.muelles);
    fprintf(pf, "ZONAS: %d\n", p.zonas);
    fprintf(pf, "CAPACIDAD_PILA: %d\n", p.capacidad_pila);

    fprintf(pf, "\n[BUQUES]\n");
    cant_buques = rand() % p.maximo_buques + 1;

    for(i = 0; i < cant_buques; i++)
    {
        cant_contenedores = rand() % p.maximo_cont_x_buque + 1;

        fprintf(pf, "B%03d;T=%d;C=",
                                    i + 1,
                                    rand() % p.duracion_jornada_minutos);

        for(f = 0; f < cant_contenedores; f++)
        {
            fprintf(pf, "C%03d", num_contenedor);
            num_contenedor++;
            total_contenedores++;
            if(f < cant_contenedores - 1)
            {
                fprintf(pf, ",");
            }
        }
        fprintf(pf, "\n");
    }

    fprintf(pf, "\n[CAMIONES]\n");
    cant_camiones = rand() % p.maximo_camiones + 1;
    if(cant_camiones > total_contenedores)
    {
        cant_camiones = total_contenedores;
    }

    usados = malloc(total_contenedores * sizeof(int));
    if(usados == NULL)
    {
        fclose(pf);
        return ERROR_RESERV_MEM;
    }

    for( f = 0 ; f < total_contenedores ; f++)
    {
        *(usados + f) = 0;
    }

    for(i = 0 ; i < cant_camiones ; i++)
    {
        do
        {
            pos = rand() % total_contenedores;
        }while(*(usados + pos) == 1);
        *(usados + pos) = 1;
        fprintf(pf, "K%03d;T=%d;C=C%03d\n",
                    i + 1,
                    rand() % p.duracion_jornada_minutos,
                    pos + 1);
    }

    free(usados);
    fclose(pf);
    return TODO_OK_ARCH;
}
