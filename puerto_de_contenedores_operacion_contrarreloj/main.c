#include "archivos.h"

int main()
{
    srand(time(NULL));
    if((generar_archivo_puerto("config.txt")) == -1)
        printf("error apertura");
    return 0;
}
