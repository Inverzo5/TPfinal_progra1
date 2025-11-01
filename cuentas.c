#include "cuentas.h"

int soli_max_numero(void)
{
    char buffer[20];
    int tabla_max = 0;

    do {
        printf("Elegí que entre hasta la tabla de multiplicar que más te guste...\n"
               "Recordá que la minima posible es %i y la máxima es %i", TABLA_MIN, TABLA_MAX);

        if (fgets(buffer, sizeof(buffer), stdin))
        {
            if (isdigit((unsigned char)buffer[0])) //Control si la primera letra es numérica.
            {
                tabla_max = atoi(buffer);

                if (tabla_max >= TABLA_MIN && tabla_max <= TABLA_MAX)
                {
                    printf("Que valiente!!! Hasta la tabla del %i es una gran elección\n", tabla_max);
                } else
                {
                    printf("No ingresaste un número entre los parámetros.\nPRUEBA NUEVAMENTE\n");
                    tabla_max = 0;
                }
            }
            else
            {
                printf("Recuerda que debes ingresar un número.\nPRUEBA NUEVAMENTE\n");
            }
        } else
        {
            printf("Error al leer la entrada o no se ingresó nada. Inténtalo nuevamente.\n");
            clearerr(stdin);
        }
    } while (tabla_max == 0);

    return tabla_max;
}

int consult_result(int num1, int num2)
{
    char buffer[20];
    int resultado = -1;

    do {
        printf("\nDebes calcular el resultado de:\n"
               "%i x %i = ", num1, num2);

        if (fgets(buffer, sizeof(buffer), stdin))
        {
            if (isdigit((unsigned char)buffer[0])) 
            {
                resultado = atoi(buffer); 
            }
            else
            {
                printf("EY! Donde has visto que el resultado de multiplicar dos números es una letra.\n"
                       "PRUEBA NUEVAMENTE\n");
            }
        } else
        {
            printf("Error alleer la entrada o no se ingresó nada.\nPRUEBA NUEVAMENTE.\n");
            clearerr(stdin);
        }
    } while (resultado == -1);

    printf("\n");
    return resultado;
}

bool ope_player(int tabla_max)
{
    int num1 = 1 + (rand() % tabla_max); //Le agregamos 1 para que vaya de 1 a tabla_max
    int num2 = 1 + (rand() % tabla_max);

    int result_player = consult_result(num1, num2);
    if (result_player == num1 * num2)
    {
        printf("Has resuelto correctamente la operación!!!\n");
        return true;
    } else
    {
        printf("UPS! Parece que ese no es el resultado");
        return false;
    }
    
    
}
