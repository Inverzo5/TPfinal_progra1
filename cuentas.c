#include "cuentas.h"

int soli_max_numero(void)
{
    char buffer[MAX_BUFFER];
    int tabla_max = 0;

    do {
        printf("\nElegí jugar con la tabla de multiplicar que más te guste...\n"
               "Recordá que la tabla mas chica posible es %i y la más grande es %i:\n",
               TABLA_MIN, TABLA_MAX);
        if (fgets(buffer, sizeof(buffer), stdin))
        {
            if (isdigit((unsigned char)buffer[0]))
            {
                tabla_max = atoi(buffer);
                if (tabla_max >= TABLA_MIN && tabla_max <= TABLA_MAX)
                {
                    printf("Que valiente!!!\nHasta la tabla del %i es una gran elección\n", tabla_max);
                } 
                else
                {
                    printf("ERROR!!!\nNo ingresaste un número entre los parámetros.\n");
                    tabla_max = 0;
                }
            }
            else
            {
                printf("ERROR!!!\nRecuerda que debes ingresar un número.\n");
            }
        } else
        {
            printf("Tuvimos un error al leer el valor ingresado.\nInténtalo nuevamente.\n");
            clearerr(stdin);
        }
    } while (tabla_max == 0);

    return tabla_max;
}

int consult_result(int num1, int num2)
{
    char buffer[MAX_BUFFER];
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
        } 
        else
        {
            printf("Tuvimos un error al leer lo que ingresaste.\nPRUEBA NUEVAMENTE.\n");
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
    }
    else
    {
        printf("UPS! Parece que ese no es el resultado\n");
        return false;
    }
}
