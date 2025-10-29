#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "control_tablero.h"
#include <stdbool.h>

typedef struct
{
    bool arriba;
    bool abajo;
    bool derecha;
    bool izquierda;
}move_disp_t;


/**
 * Esta función se encarga de definir en que direcciones se puede mover el GATO o el RATON.
 * 
 * @param matriz Puntero doble a la direccion de memoria del primer elemento de la matriz
 */
move_disp_t movimientos_disponibles(contenido_t** matriz, size_t ubix, size_t ubiy);

#endif