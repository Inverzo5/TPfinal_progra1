#include "control_tablero.h"

size_t solicit_len(void)
{
    char buffer[20];
    int numero = 0;

    do{
        printf("Ingrese la cantidad de filas y columnas con las que desea jugar.\n");
        printf("Recuerde que el mínimo es %i y el máximo es %i: ", MIN_LONGITUD, MAX_LONGITUD);

        if (fgets(buffer, sizeof(buffer), stdin))
        {
            if (isdigit((unsigned char)buffer[0])) //Control si la primera letra es numérica.
            {
                numero = atoi(buffer);

                if (numero >= MIN_LONGITUD && numero <= MAX_LONGITUD)
                {
                    printf("Excelente, %i líneas me parece una gran opción\n", numero);
                } else
                {
                    printf("Recuerda que el mínimo de líneas es %i y el máximo %i.\nPRUEBA NUEVAMENTE\n", MIN_LONGITUD, MAX_LONGITUD);
                    numero = 0;
                }
            }
            else
            {
                printf("Recuerda que debes ingresar un número.\nPRUEBA NUEVAMENTE\n");
            }
        } else //No se leyó correctamente el fgets o no se entregó nada.
        {
            printf("Error al leer la entrada o no se ingresó nada. Inténtalo nuevamente.\n");
            clearerr(stdin);
        }
        

    } while (numero == 0);

    return (size_t)numero;
}

contenido_t** crear_matriz(size_t longitud)
{
    if (longitud < MIN_LONGITUD || longitud > MAX_LONGITUD)
    {
        return NULL;
    }
    
    
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

error_t ubi_elements(contenido_t** matriz, size_t longitud, size_t posx_init_cat, size_t posy_init_cat, size_t cant_piedra, size_t cant_llave)
{
    matriz[POSX_INIT_RATON][POSY_INIT_RATON] = RATON;
    matriz[posx_init_cat][posy_init_cat] = GATO;
    matriz[longitud - 1][longitud / 2] = SALIDA;
    
    error_t verif_error = OPERACION_EXITOSA;
    while (cant_piedra > 0 && verif_error != NO_ESPACIO_MAT)
    {
        verif_error = ubi_rndm(matriz, longitud, PIEDRA, CANTIDAD_PRUEBAS_RAND);
        cant_piedra--;
    }
    while (cant_llave > 0 && verif_error != NO_ESPACIO_MAT)
    {
        verif_error = ubi_rndm(matriz, longitud, LLAVE, CANTIDAD_PRUEBAS_RAND);
        cant_llave--;
    }
    
    return verif_error;
}

void print_tablero(contenido_t** matriz, size_t longitud)
{
    for (size_t i = 0; i < longitud; i++)
    {
        for (size_t j = 0; j < longitud; j++)
        {
            switch (matriz[i][j])
            {
            case LIBRE:  printf("⚪"); break;
            case RATON:  printf("🐭"); break;
            case GATO:   printf("🐱"); break;
            case PIEDRA: printf("🪨"); break;
            case LLAVE:  printf("🔑"); break;
            case SALIDA: printf("🏁"); break;
            }
        }
        printf("\n");
    }
    
}