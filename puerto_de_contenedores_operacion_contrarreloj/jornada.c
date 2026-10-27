#include "jornada.h"
#include "instrucciones.h"
#include "archivos.h"


void menu()
{
    int opcion = 1;
    while(opcion)
    {
    printf("--------------------------------------\n");
    printf("0- Salir.\n");
    printf("1- Iniciar jornada.\n");
    printf("2- Ver ranking histórico de operarios.\n");
    printf("--------------------------------------\n");
    scanf("%d",&opcion);
    if(opcion < LIM_INF_MENU || opcion > LIM_SUP_MENU)
    {
        printf("Opcion incorrecta. Reingrese.\n");
        scanf("%d",&opcion);
    }
    switch(opcion)
    {
        case 1:
            {
            jornada();
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

void jornada()
{
    tJornada j;
    cargarPuerto(&j);

}

int cargarPuerto(tJornada * j)
{
    char linea[100];
    tLista lista;
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
    crearLista(&lista);

    while((fgets(linea, sizeof(linea),pf)) != NULL && strcmp(linea, "[CAMIONES]\n") != 0)
    {
        asignarBuque(linea, &lista);
    }

    fclose(pf);
    return TODO_OK;
}

void asignarBuque(char* linea, tLista *lista)
{
    char* aux;
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
        acolar(&buque.cola, aux, strlen(aux)+1);
        aux = strtok(NULL,",");
    }
    ponerAlFinal(lista, &buque, sizeof(buque));
}
