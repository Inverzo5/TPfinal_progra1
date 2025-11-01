#include "control_tablero.h"
#include "cuentas.h"
#include "errores.h"
#include "movimiento.h"
#include <time.h>

int main(void) {
    error_t control_errores = OPERACION_EXITOSA;
    srand((unsigned int) time(NULL));

    size_t len_tablero = solicit_len();
    int tabla_max = soli_max_numero();
    contenido_t** ptr_tablero = NULL;
    ptr_tablero = crear_matriz(len_tablero);
    if (ptr_tablero == NULL) //No hay lugar en el heap para crear la matriz.
    {
        printf("Parece que no tienes suficiente memoria dinámica para correr este juego en tu terminal.\n"
               "Prueba cambiar la cantidad de memoria dinámica disponible o abrir una nueva terminal.\n");
        return 1;
    }

    size_t posx_init_gato = len_tablero - 1; //Inicializamos el gato en la esquina inferior.
    size_t posy_init_gato = len_tablero - 1;
    
    /**
     * Elejimos que la cantidad de piedras sea una menos que la de todo el tablero y la cantidad de llaves la mitad mas 1.
     */
    control_errores = ubi_elements(ptr_tablero, len_tablero, posx_init_gato, posy_init_gato,
                                   len_tablero - 1, len_tablero / 2 + 1); 
    if (control_errores == NO_ESPACIO_MAT)
    {
        printf("Parece que la cantidad de obstaculos asignados sobrepasan la capacidad./n"
               "Prueba cambiar estas cantidades\n");
        return 1;
    }
    print_tablero(ptr_tablero, len_tablero);

    bool sigue_jugando = true; //Flag que controla que se mantiene el juego en marcha.
    
    size_t* pos_actual_raton = (size_t*) malloc(sizeof(size_t) * 2); //Creamos un seguimiento especifico al gato y al raton
    if (pos_actual_raton == NULL)
    {
        printf("Parece que no tienes suficiente memoria dinámica para correr este juego en tu terminal.\n"
               "Prueba cambiar la cantidad de memoria dinámica disponible o abrir una nueva terminal.\n");
        return 1;
    }
    *pos_actual_raton = POSY_INIT_RATON;
    *(pos_actual_raton + 1) = POSX_INIT_RATON;
    size_t* pos_actual_gato = (size_t*) malloc(sizeof(size_t) * 2);
    if (pos_actual_gato == NULL)
    {
        printf("Parece que no tienes suficiente memoria dinámica para correr este juego en tu terminal.\n"
               "Prueba cambiar la cantidad de memoria dinámica disponible o abrir una nueva terminal.\n");
        return 1;
    }
    *pos_actual_gato = posy_init_gato;
    *(pos_actual_gato + 1) = posx_init_gato;



    while (sigue_jugando)
    {
        /* code */
    }
    
    
    free(pos_actual_gato);
    free(pos_actual_raton);
    free_matriz(ptr_tablero, len_tablero);
}
    