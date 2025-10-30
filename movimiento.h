#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "control_tablero.h"
#include <stdbool.h>
#include "errores.h"

typedef enum{
    ARRIBA = 0,
    ABAJO,
    IZQUIERDA,
    DERECHA,
    NUM_DIREC = 4
}direcciones_t;

typedef struct
{
    bool movs[NUM_DIREC];
}move_disp_t;


/**
 * Esta función se encarga de definir en que direcciones se puede mover el GATO o el RATON.
 * 
 * @param matriz Puntero doble a la direccion de memoria del primer elemento de la matriz.
 * @param longitud La longitud de la matriz asignada.
 * @param ubix Ubicación en x del contenido que se desea mover.
 * @param ubiy Ubicación en y del contenido que se desea mover.
 * @param posible_move [out] Puntero a estructura donde se quiere guardar los movimientos posibles del contenido.
 * 
 * @pre
 * - La matriz ya debe estar inicializada con todos los contenidos correspondientes.
 * - Las estructuras move_disp_t y direcciones_t deben estar definidas.
 * @post
 * - Los valores apuntados por posible_mov seran alterados como efectos secundario de la función.
 */
void movimientos_disponibles(contenido_t** matriz, size_t longitud, size_t ubix, size_t ubiy, move_disp_t* posible_mov);

/**
 * Se encarga del movimiento de un contenido movil; GATO o RATON.
 * 
 * @param origen [in/out] Puntero a la casilla donde se ubica el contenido movil.
 * @param destino [in/out] Puntero a la casilla de destino del contenido movil.
 * @return OPERACION_EXITOSA en caso de funcionar correctamente,
 *         PUNTERO_NULO si alguno de los punteros apunta a NULL.
 * 
 * @pre
 * - Los punteros deben apuntar a casillas de la matriz dinámica.
 * - El header errores.h debe estar incluido.
 * @post
 * - Como efecto de la función el contenido de destino tendrá el contenido_t que contenía
 * origen mientras que origen tendrá LIBRE.
 * - Se retornará un error_t que subyase el resultado de la operación.
 */
error_t mover(contenido_t* origen, contenido_t* destino);


#endif