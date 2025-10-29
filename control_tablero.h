#ifndef CONTROL_TABLERO_H
#define CONTROL_TABLERO_H

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MIN_LONGITUD 5
#define MAX_LONGITUD 9
#define POSX_INIT_RATON 0
#define POSY_INIT_RATON 0

/**
 * Enumeración que dicta las diferentes cosas que pueden haber en una casilla.
 */
typedef enum{
    LIBRE, //Casilla que puede ser ocupada tanto por RATON como por GATO.
    RATON, //Casilla donde se ubica el RATON, una vez que se mueve el RATON será LIBRE.
    GATO, //Casilla donde se ubica el GATO, una vez que se mueve el GATO será LIBRE.
    PIEDRA, //Casilla donde se ubica una piedra, no puede tener GATO ni RATON.
    LLAVE, //Casilla donde se ubica llave. Elemento con el cual se puede matar al gato.
    SALIDA //Casilla de SALIDA, si el GATO llega a ella se termina el juego.
}contenido_t;

typedef enum{
    OPERACION_EXITOSA,
    NO_ESPACIO_MAT,
}error_t;

/**
 * Función que solicita al usuario la longitud de la matriz del tablero.
 * 
 * @return Entero sin signo obtenido del usuario entre 5 y 9.
 * 
 * @pre
 *  - Las librerias ctype.h, stdio.h y stdbool.h deben estar incluidas.
 *  - El marco MIN_LONGITUD debe estar definido.
 * @post
 *  - Se retornará un entero sin signo.
 * 
 * @warning
 *  - FUNCIÓN IMPURA: Se comunica con el usuario a travez de getchar.
 */
size_t solicit_len(void);

/**
 * Crea una matriz dinámica del tipo contenido_t de NxN.
 * 
 * @param longitud Longitud de las filas y columnas de la matriz dinámica.
 * @return puntero doble de contendio_t a la dirección de memoria al primer elemento de la matriz,
 *         NULL en caso de no poder crearse la matriz.
 * 
 * @pre
 *  - La enumeración contenido_t debe estar definida.
 *  - Las librerías stdlib.h y stdio.h deben estar incluidas.
 * @post
 *  - Se retorna un puntero doble.
 *  - Se utiliza memoria del heap disponible.
 * 
 * @warning
 * Esta matriz fue hecha dinamicamente, es necesario liberar la memoria utilizada una vez
 * que se haya terminado de usar para evitar fugas de memoria.
 * Función designada: free_matriz.
 */
contenido_t** creacion_matriz(size_t longitud);

/**
 * Libera matriz dinámica dentada de tipo contenido_t de NxN.
 * 
 * @param matriz Puntero doble a la dirección de memoria del primer elemento de la matriz dinámica.
 * @param longitud Longitud de la matriz dinámica creada.
 * 
 * @pre
 *  - La matriz dinámica de NxN ya debe haber sido creada.
 *  - La enumeración contenido_t debe estar definida.
 *  - Las librerías stdio.h y stddef.h deben estar incluidas.
 * @post
 *  - La memoria dinámica asignada será liberada.
 * 
 * @warning
 * Esta función no se encarga de reasignar el puntero doble a un puntero NULL.
 * Esto último es necesario hacerlo a continuación de ser llamada la función con matriz para evitar dangling pointer.
 */
void free_matriz(contenido_t** matriz, size_t longitud);

/**
 * Se remplaza el valor de un elemento LIBRE aleatorio de una matriz de NxN.
 * 
 * @param matriz Puntero doble a la direccion de memoria del primer elemento de una matriz de NxN.
 * @param longitud La longitud de la matriz asignada.
 * @param content El valor de contenido_t que quiere ser ubicado en la matriz.
 * @param cant_pruebas Cantidad de pruebas aleatorias hasta verificar que hay espacio libre.
 * @return OPERACION_EXITOSA si todo funcionó correctamente.
 *         NO_ESPACIO_MAT la matriz no tiene lugar para ubicar un objeto.
 * 
 * @pre
 *  - La semilla de generador de números aleatorios debe estar inicializada.
 *  - Las librerías time.h y stdlib.h deben estar incluidas.
 *  - Las enumeraciónes contenido_t y error_t deben estar definidas.
 * @post
 *  - La matriz será modificada como efecto secundario de la función.
 *  - Se retornará un mensaje codificado como error_t.
 */
error_t ubi_rndm(contenido_t** matriz, size_t longitud, contenido_t content, size_t cant_pruebas);

/**
 * Función que ubica todos los contenidos del juego en la matriz dinámica.
 * 
 * @param matriz Puntero doble a la dirección de memoria al primer elemento de la matriz.
 * @param longitud La longitud de la matriz asignada.
 * @param posx_init_cat La posicion inicial en x (filas) del gato.
 * @param posy_init_cat La posicion inicial en y (columnas) del gato.
 * @param cant_piedra La cantidad de contenidos_t PIEDRA que quieren ser colocadas en la matriz.
 * @param cant_llave La cantidad de contenidos_t LLAVE que quieren ser colocadas en la matriz.
 * @return OPERACION_EXITOSA si se pudieron asignar los contenidos correctamente.
 *         NO_ESPACIO_MAT si no hubo suficiente lugar en a matriz para asignar la cantidad de contenidos proporcionados.
 * 
 * @pre
 * - La semilla de generador de números aleatorios debe estar inicializada.
 * - Las librerías time.h y stdlib.h deben estar incluidas.
 * - Las enumeraciónes contenido_t y error_t deben estar definidas.
 * - Los macros POSX_INIT_RATON y POSY_INIT_RATON deben estar definidos.
 * @post
 * - La matriz será modificada como efecto secundario de la función.
 * - Se retornará un mensaje de proceso en forma de error_t.
 */
error_t ubi_elements(contenido_t** matriz, size_t longitud, size_t posx_init_cat, size_t posy_init_cat, size_t cant_piedra, size_t cant_llave);

#endif