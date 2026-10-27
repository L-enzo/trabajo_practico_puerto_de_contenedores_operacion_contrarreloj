#include "jornada.h"
#include "instrucciones.h"
#include "archivos.h"


void menu()
{
    int error;
    int opcion = 1;
    while(opcion)
    {
    printf("--------------------------------------\n");
    printf("0- Salir.\n");
    printf("1- Iniciar jornada.\n");
    printf("2- Ver ranking histórico de operarios.\n");
    printf("--------------------------------------\n");
    scanf("%d",&opcion);
    while(opcion < LIM_INF_MENU || opcion > LIM_SUP_MENU)
    {
        printf("Opcion incorrecta. Reingrese.\n");
        scanf("%d",&opcion);
    }
    switch(opcion)
    {
        case 1:
            {
            if((error = jornada()) != TODO_OK_JORNADA)
            {
                //funcionerrores
            }
            break;
            }
        case 2:
            {
            break;
            }
    }
    system("cls");
    }
}

int jornada()
{
    int error;
    tJornada j;
    tLista listaBuques, listaCamiones;
    crearLista(&listaBuques);
    crearLista(&listaCamiones);
    if((error = cargarPuerto(&j, &listaBuques, &listaCamiones)) != TODO_OK_JORNADA)
       {
           mapeoLista(&listaBuques, liberarColaVehiculo);
           vaciarLista(&listaBuques);
           mapeoLista(&listaCamiones, liberarColaVehiculo);
           vaciarLista(&listaCamiones);
           return error;
       }

    mapeoLista(&listaBuques, liberarColaVehiculo);
    vaciarLista(&listaBuques);
    mapeoLista(&listaCamiones, liberarColaVehiculo);
    vaciarLista(&listaCamiones);
    return TODO_OK_JORNADA;
}

int cargarPuerto(tJornada * j, tLista* listaBuques, tLista* listaCamiones)
{
    char linea[100];
    int error;
    FILE *pf = fopen("puerto.txt","rt");
    if(!pf)
    {
        return ERROR_APERT_ARCH;
    }

    fscanf(pf, "JORNADA: %d\n", &j->Jor);
    fscanf(pf, "MUELLES: %d\n", &j->Mue);
    fscanf(pf, "ZONAS: %d\n", &j->Zon);
    fscanf(pf, "CAPACIDAD_PILA: %d\n", &j->capPila);

    fscanf(pf, "\n[BUQUES]\n");

    while((fgets(linea, sizeof(linea),pf)) != NULL && strcmp(linea, "[CAMIONES]\n") != 0)
    {
        linea[strcspn(linea, "\r\n")] = '\0';
        if(linea[0] != '\0')
        {
            if((error = asignarBuque(linea, listaBuques)) != TODO_OK_JORNADA)
            {
                fclose(pf);
                return error;
            }
        }
    }

    while((fgets(linea, sizeof(linea),pf)) != NULL)
    {
        linea[strcspn(linea, "\r\n")] = '\0';
        if(linea[0] != '\0')
        {
            if((error = AsignarCamion(linea, listaCamiones)) != TODO_OK_JORNADA)
            {
                fclose(pf);
                return error;
            }
        }
    }
    fclose(pf);
    return TODO_OK_JORNADA;
}

int asignarBuque(char* linea, tLista *listaBuques)
{
    char* aux;
    int error;
    tVehiculo buque;
    aux = strtok(linea, ";");
    strcpy(buque.codigo, aux);
    aux = strtok(NULL, ";");
    sscanf(aux, "T=%u", &buque.tiempo);
    aux = strtok(NULL, ";");
    aux += 2;
    crearCola(&buque.cola);
    aux = strtok(aux,",");
    while(aux != NULL)
    {
        if((error = acolar(&buque.cola, aux, strlen(aux)+1)) != TODO_OK)
        {
            vaciarCola(&buque.cola);
            return error;
        }
        aux = strtok(NULL,",");
    }
    if((error = ponerAlFinal(listaBuques, &buque, sizeof(buque))) != TODO_OK_LISTA)
    {
        vaciarCola(&buque.cola);
        return error;
    }
    return TODO_OK_JORNADA;
}

int AsignarCamion(char* linea, tLista * listaCamiones)
{
    char* aux;
    int error;
    tVehiculo camion;
    aux = strtok(linea, ";");
    strcpy(camion.codigo, aux);
    aux = strtok(NULL, ";");
    sscanf(aux, "T=%u", &camion.tiempo);
    aux = strtok(NULL, ";");
    aux += 2;
    crearCola(&camion.cola);
    if((error = acolar(&camion.cola, aux, strlen(aux)+1)) != TODO_OK)
    {
        vaciarCola(&camion.cola);
        return error;
    }
    if((error = ponerAlFinal(listaCamiones, &camion, sizeof(camion))) != TODO_OK_LISTA)
    {
        vaciarCola(&camion.cola);
        return error;
    }
    return TODO_OK_JORNADA;
}

void liberarColaVehiculo(void *dato)
{
    tVehiculo *vehiculo = dato;
    vaciarCola(&vehiculo->cola);
}
