#include "control_tablero.h"

size_t solicit_len(void)
{
    char buffer[MAX_BUFFER];
    int longitud = 0;

    do{
        printf("Este juego requiere de un tablero cuadrado.\n"
               "Ingrese la longitud del tablero con el que desea jugar.\n"
               "Recuerde que el tamaño mínimo es %i y el máximo es %i: \n", 
               MIN_LONGITUD, MAX_LONGITUD);

        if (fgets(buffer, sizeof(buffer), stdin))
        {
            if (isdigit((unsigned char)buffer[0]))
            {
                longitud = atoi(buffer);

                if (longitud >= MIN_LONGITUD && longitud <= MAX_LONGITUD)
                {
                    printf("Excelente, %i líneas me parece una gran opción.\n", longitud);
                } 
                else
                {
                    printf("ERROR!!!\nRecuerda que el mínimo de líneas es %i y el máximo es %i.\n",
                            MIN_LONGITUD, MAX_LONGITUD);
                    longitud = 0;
                }
            }
            else
            {
                printf("ERROR!!!\nRecuerda que debes ingresar un número.\n");
            }
        } 
        else //fgets no leyó correctamente.
        {
            printf("Tuvimos un error leyendo tu entrada.\nInténtalo nuevamente.\n");
            clearerr(stdin);
        }
    } while (longitud == 0);

    return (size_t)longitud;
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
            for (size_t j = 0; j < i; j++) 
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
    for (size_t i = 0; i < longitud; i++) //Liberamos los dientes primero.
    {
        free(matriz[i]);
    }
    free(matriz);
}

error_t ubi_rndm(contenido_t** matriz, size_t longitud, contenido_t content, size_t cant_pruebas)
{
    error_t estado_process = OPERACION_EN_PROCESO;
    size_t cant_bucles = 0;
    do
    {
        int fila  = rand() % longitud;
        int colum = rand() % longitud;   
        if (matriz[fila][colum] == LIBRE)
        {
            matriz[fila][colum] = content;
            estado_process = OPERACION_EXITOSA;
        }
        cant_bucles++;
    } while ((estado_process == OPERACION_EN_PROCESO) && (cant_bucles < cant_pruebas));
    //Se supero la cantidad de pruebas, asignemos el contenido en el primer espacio LIBRE.
    if (estado_process == OPERACION_EN_PROCESO)
    {    
        for (size_t fila = 0; fila < longitud; fila++)
        {
            for (size_t colum = 0; colum < longitud && estado_process == OPERACION_EN_PROCESO; colum++)
            {
                if (matriz[fila][colum] == LIBRE)
                {
                    matriz[fila][colum] = content;
                    estado_process = OPERACION_EXITOSA;
                }
            }
        }        
    }
    if (estado_process == OPERACION_EN_PROCESO)
    {
        estado_process = NO_ESPACIO_MAT;
    }
    return estado_process;
}

error_t ubi_elements(contenido_t** matriz, size_t longitud, size_t posx_init_cat, size_t posy_init_cat,
                     size_t cant_piedra, size_t cant_llave)
{
    matriz[POSY_INIT_RATON][POSX_INIT_RATON] = RATON;
    matriz[posy_init_cat]  [posx_init_cat]   = GATO;
    matriz[longitud - 1]   [longitud / 2]    = SALIDA;
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
    printf("\n");
    for (size_t i = 0; i < longitud; i++)
    {
        for (size_t j = 0; j < longitud; j++)
        {
            switch (matriz[i][j])
            {
            case LIBRE:  printf(" ⚪");  break;
            case RATON:  printf(" 🐭");  break;
            case GATO:   printf(" 🐱");  break;
            case PIEDRA: printf(" 🪨 "); break;
            case LLAVE:  printf(" 🔑");  break;
            case SALIDA: printf(" 🏁");  break;
            }
        }
        printf("\n");
    }
    
}