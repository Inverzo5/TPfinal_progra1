#include "control_tablero.h"

size_t solicit_len(void)
{
    int numero;
    bool bucle = true;

    while(bucle)
    {
        printf("Ingrese la cantidad de filas y columnas con las que desea jugar.\nRecuerde que el minimo es %i y el máximo es %i: ", MIN_LONGITUD, MAX_LONGITUD);
        char caracter = getchar();
        
        if (isdigit(caracter))
        {
            numero = caracter - '0';

            if (numero >= MIN_LONGITUD && MAX_LONGITUD >= numero)
            {
                printf("Excelente, %i lineas me parece una gran opción\n", numero);
                bucle = false;
            } else
            {
                printf("Recuerda que el mínimo de lineas es %i y el máximo %i.\nPRUEBA NUEVAMENTE\n", MIN_LONGITUD, MAX_LONGITUD);
            }
        } else
        {
            printf("Recuerda que debes ingresar un número.\nPRUEBA NUEVAMENTE\n");
        }    
    }
    return (size_t)numero;
}

contenido_t** crear_matriz(size_t longitud)
{
    contenido_t** matriz = (contenido_t**) malloc(longitud * sizeof(contenido_t*));
    
    if (matriz == NULL)
    {
        return NULL;
    }
    

    for (size_t i = 0; i < longitud; i++)
    {
        matriz[i] = (contenido_t*) malloc(longitud * sizeof(contenido_t));

        if (matriz[i] == NULL) //ERROR generando uno de los dientes. Tenemos que liberar lo que ya creamos.
        {
            for (size_t j = 0; j < i; j++) //Liberamos primero los dientes que ya hicimos.
            {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
        
        for (size_t j = 0; j < longitud; j++) //Inicialización
        {
            matriz[i][j] = LIBRE;
        }
        
    }
    
    return matriz;
}

void free_matriz(contenido_t** matriz, size_t longitud)
{
    for (size_t i = 0; i < longitud; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

error_t ubi_rndm(contenido_t** matriz, size_t longitud, contenido_t content, size_t cant_pruebas)
{
    size_t cant_bucles = 0; //Controlamos la cantidad de bucles.

    do
    {
        int fila = rand() % longitud;
        int colum = rand() % longitud;
        
        if (matriz[fila][colum] == LIBRE)
        {
            matriz[fila][colum] = content;
            content = LIBRE; //El contenido a ubicar fue ubicado. Mision cumplida.
            return OPERACION_EXITOSA;
        }

        cant_bucles++;
    } while ((content != LIBRE) && (cant_bucles < cant_pruebas));

    //Se supero la cantidad de pruebas, asignemos el contenido en el primer espacio LIBRE.

    for (size_t fila = 0; fila < longitud; fila++)
    {
        for (size_t colum = 0; colum < longitud; colum++)
        {
            if (matriz[fila][colum] == LIBRE)
            {
                matriz[fila][colum] = content;
                content = LIBRE; //El contenido a ubicar fue ubicado. Mision cumplida.
                return OPERACION_EXITOSA;
            }
        }
    }        

    return NO_ESPACIO_MAT; //No hay espacio en la matriz para ubicar el contenido.
}
