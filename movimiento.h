#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "control_tablero.h"
#include <stdbool.h>
#include "errores.h"

/**
 * Enumeración que le da un valor entero a las direcciones posibles de movimiento
 * de un contenido movil.
 */
typedef enum{
    ARRIBA = 0, //Desplazarse hacia arriba (+y)
    ABAJO, //Desplazarse hacia abajo (-y)
    IZQUIERDA, //Desplazarse hacia izquierda (-x)
    DERECHA, //Desplazarse hacia derecha (+x)
    NUM_DIREC = 4,
    NO_DIR //Se crea con la intención de poder inicializar las variables a algo o manejar errores.
}direcciones_t;

/**
 * Define los movimientos posibles de un contenido_t movil.
 * true significa que esa dirección está disponible y false que no.
 * El orden de las direcciones se corresponde con el orden de las direcciones declaradas en
 * la enumeración direcciones_t. Es decir:
 * 0 -> ARRIBA 1 -> ABAJO 2 -> IZQUIERDA 3 -> DERECHA
 */
typedef struct{
    bool movs[NUM_DIREC]; //Direcciones posibles ordenadas en el orden de direcciones_t
}move_disp_t;

/**
 * Se define un orden de prioridad en los movimientos del gato.
 * El gato sigue un sistema de acercamiento al raton en el que se acerca en la direccion (x o y)
 * donde más alejado está de él. Ej: si esta a 3 en x y a 2 en y se acerca por x al ser 3 > 2.
 * No obstante pueden haber obstaculos en el camino del gato que no le permiten ir en la dirección que él pretende.
 * Por esto creamos esta estructura que ordena los movimientos de mayor orden de importancia a menor orden.
 * Ej: gato se tiene que mover hacia arriba, pero hay una piedra, entonces salta al segundo orden y se mueve en esa dirección.
 */
typedef struct{
    direcciones_t orden[NUM_DIREC]; //Lista de mayor prioridad en los movimientos.
}priority_t;


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
 * @param is_llave [out] Puntero que pondrá su valor en true en caso de que el contenido movil
 * entre en contacto con una llave, es decir, que el puntero destino apunte a una LLAVE.
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
 * - En caso de que no haya llave el valor de is_llave no sufre cambios.
 */
error_t mover(contenido_t* origen, contenido_t* destino, bool* is_llave);

/**
 * Se ordena en importancia decreciente la dirección más conveniente para el gato.
 * 
 * @param ubix_cat Ubicación en x del gato.
 * @param ubiy_cat Ubicación en y del gato.
 * @param ubix_raton Ubicación en x del raton.
 * @param ubiy_raton Ubicación en y del raton.
 * @return Estructura priority_t que ordena en orden decreciente las direcciones prioritarias del gato.
 * 
 * @pre
 * - Las direcciones del gato y el raton deben ser sobre la matriz dinámica creada.
 * - La librería stdlib.h debe estar incluida.
 * @post
 * - Se retornará una estructura priority.
 * @warning
 * - La función no retorna un código de error, pero cualquier tipo de error se puede verificar facilmente
 * evaluando si algunas de las prioridades dice NO_DIR puesto que no se asignaron correctamente. 
 */
priority_t calc_priority(size_t ubix_cat, size_t ubiy_cat, size_t ubix_raton, size_t ubiy_raton);

/**
 * Se encarga de mover el gato a la casilla de mayor conveniencia.
 * 
 * @param matriz Puntero doble a la direccion de memoria del primer elemento de la matriz.
 * @param longitud La longitud de la matriz asignada.
 * @param ubix_cat Ubicación en x del gato.
 * @param ubiy_cat Ubicación en y del gato.
 * @param ubix_raton Ubicación en x del raton.
 * @param ubiy_raton Ubicación en y del raton.
 * @return OPERACION_EXITOSA en caso de hacer el movimiento con exito.
 *         CONTENIDO_BLOQUEADO en caso de que haya ningun movimiento posible para el gato.
 * 
 * @pre
 * - Los headers errores.h y control_tablero.h deben estar incluidos.
 * - Las funciones calc_priority, mover y movimientos_disponibles deben estar definidas.
 * - El puntero matriz debe apuntar al tablero de NxN creado.
 * - Las librerías stdbool.h, stdlib.h y stdio.h deben estar incluidas.
 * @post
 * - La función generará un cambio en la matriz asignada como efecto secundario de la función.
 * En caso de que el retorno sea OPERACION_EXITOSA.
 * - En caso de retornar CONTENIDO_BLOQUEADO no se efectuan cambios en la matriz.
 */
error_t move_cat(contenido_t** matriz, size_t longitud, size_t ubix_cat, size_t ubiy_cat, size_t ubix_raton, size_t ubiy_raton);

/** */
direcciones_t eleccion_dir_raton();

#endif