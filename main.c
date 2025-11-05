#include "control_tablero.h"
#include "cuentas.h"
#include "extras.h"
#include "movimiento.h"
#include <time.h>

int main(void) {
    srand((unsigned int) time(NULL));
    error_t control_errores = OPERACION_EXITOSA;

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

    size_t posx_init_gato = len_tablero - 1;
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

    estado_t estado_juego = EN_JUEGO; //Flag que controla que se mantiene el juego en marcha.
    
    size_t* pos_actual_raton = (size_t*) malloc(sizeof(size_t) * 2); //Creamos un seguimiento especifico al gato y al raton
    if (pos_actual_raton == NULL)
    {
        printf("Parece que no tienes suficiente memoria dinámica para correr este juego en tu terminal.\n"
               "Prueba cambiar la cantidad de memoria dinámica disponible o abrir una nueva terminal.\n");
        return 1;
    }
    *pos_actual_raton       = POSY_INIT_RATON;
    *(pos_actual_raton + 1) = POSX_INIT_RATON;
    size_t* pos_actual_gato = (size_t*) malloc(sizeof(size_t) * 2);
    if (pos_actual_gato == NULL)
    {
        printf("Parece que no tienes suficiente memoria dinámica para correr este juego en tu terminal.\n"
               "Prueba cambiar la cantidad de memoria dinámica disponible o abrir una nueva terminal.\n");
        return 1;
    }
    *pos_actual_gato       = posy_init_gato;
    *(pos_actual_gato + 1) = posx_init_gato;

    bool raton_has_key = false;
    bool raton_in_salida = false;
    bool cat_in_salida = false;

    while (estado_juego == EN_JUEGO)
    {
        direcciones_t dir_selec = eleccion_dir_raton(ptr_tablero, len_tablero, *(pos_actual_raton + 1), *pos_actual_raton);
        if (dir_selec == NO_DIR)
        {
            printf("Parece que el raton no tiene donde ir.\nEsto no te permite seguir jugando, prueba nuevamente\n");
            estado_juego = DERROTA;
        }
        
        if (ope_player(tabla_max) && estado_juego == EN_JUEGO) //Resolvió correctamente!!!
        {
            size_t posx_prev_raton = *(pos_actual_raton + 1);
            size_t posy_prev_raton = *pos_actual_raton;
            dir_elegida(dir_selec, (pos_actual_raton + 1), pos_actual_raton);
            mover(&ptr_tablero[posy_prev_raton][posx_prev_raton], &ptr_tablero[pos_actual_raton[0]][pos_actual_raton[1]],
                &raton_has_key, &raton_in_salida, false);
        }
        if (raton_in_salida)
        {
            printf("\nLlegaste a la linea de meta\nHAS GANADO!!!\n");
            estado_juego = VICTORIA;
        } else if (pos_actual_gato[0] == pos_actual_raton[0] && pos_actual_gato[1] == pos_actual_raton[1] && raton_has_key)
        {
            printf("\nHas matado al gato con tu llave!!!\n");
            raton_has_key = false;
            ptr_tablero[len_tablero - 1][len_tablero - 1] = GATO;
            *pos_actual_gato = len_tablero - 1;
            *(pos_actual_gato + 1) = len_tablero - 1;
        } else if ((pos_actual_gato[0] == pos_actual_raton[0] && pos_actual_gato[1] == pos_actual_raton[1] && !raton_has_key))
        {
            printf("\nOH NO!!!\nHas entrado en la boca del gato!!!\nHas perdido!!!\n");
            estado_juego = DERROTA;
        }else if (raton_has_key)
        {
            printf("\nNo te olvides que tienes la llave en tus manos!!!\n");
        }

        if (estado_juego == EN_JUEGO)
        {
            print_tablero(ptr_tablero, len_tablero);
            printf("\nAtención!!!\nEl gato se está moviendo.\n");
            direcciones_t dir_gato = NO_DIR;
            control_errores =  move_cat(ptr_tablero, len_tablero, pos_actual_gato[1], pos_actual_gato[0], pos_actual_raton[1],
                                        pos_actual_raton[0], &cat_in_salida, cat_in_salida, &dir_gato);
            if (control_errores == OPERACION_EXITOSA)
            {
                dir_elegida(dir_gato, (pos_actual_gato + 1), pos_actual_gato);
            } else //El gato está encerrado. Se utiliza una transportación hacia arriba para salir.
            {
                bool basura1;
                bool basura2;
                mover(&ptr_tablero[pos_actual_gato[1]][pos_actual_gato[0]], &ptr_tablero[pos_actual_gato[1]][pos_actual_gato[0] - 1],
                      &basura1, &basura2, false);
                dir_elegida(ARRIBA, &pos_actual_gato[1], &pos_actual_gato[0]);
            }
            if (pos_actual_gato[0] == pos_actual_raton[0] && pos_actual_gato[1] == pos_actual_raton[1])
            {
                printf("OH NO!!!\nEl gato te a comido.\nPERDISTE\n");
                estado_juego = DERROTA;
            }
        }
        print_tablero(ptr_tablero, len_tablero);
    }
    
    
    free(pos_actual_gato);
    free(pos_actual_raton);
    free_matriz(ptr_tablero, len_tablero);
}
    