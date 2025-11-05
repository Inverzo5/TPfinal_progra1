#ifndef CONTROL_TABLERO_H
#define CONTROL_TABLERO_H

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "extras.h"

#define MIN_LONGITUD 5
#define MAX_LONGITUD 20
#define POSX_INIT_RATON 0
#define POSY_INIT_RATON 0
#define CANTIDAD_PRUEBAS_RAND 20

/**
 * Llamaremos contenidos (type contenido_t) a los diferentes tipos de objetos o animales que puede contener
 * una casilla del tablero.
 */
typedef enum{
    LIBRE,  //Casilla que no contiene nada y puede ser potencialmente ocupada por el GATO o el RATON.
    RATON,  //Casilla donde se ubica el RATON, una vez que se mueve el RATON quedará LIBRE.
    GATO,   //Casilla donde se ubica el GATO, una vez que se mueve el GATO quedará LIBRE.
    PIEDRA, //Casilla donde se ubica una piedra, precenta un obstaculo para el RATON y el GATO.
    LLAVE,  //Casilla donde se ubica llave. Elemento con el cual se puede matar al gato.
    SALIDA  //Casilla de SALIDA, si el RATON llega a ella se termina el juego.
}contenido_t;

/**
 * Se solicita al usuario el tamaño del tablero.
 * 
 * @return Entero sin signo (size_t) obtenido del usuario entre MIN_LONGITUD y MAX_LONGITUD.
 * 
 * @pre
 * - Las librerias ctype.h, stdio.h y stdbool.h deben estar incluidas.
 * - El marco MIN_LONGITUD y MAX_LONGITUD debe estar definido.
 * - El header local extras.h debe estar incluido.
 * @post
 *  - Se retornará un entero sin signo obtenido a traves de comunicación con el usuario.
 */
size_t solicit_len(void);

/**
 * Crea matriz dentada dinámica del tipo contenido_t de NxN.
 * 
 * @param longitud Longitud de las filas y columnas de la matriz dinámica (el tablero).
 * @return puntero doble de tipo contendio_t que apunta al primer elemento de la matriz creada,
 *         NULL en caso de no poder crearse la matriz debido a falta de memoria dinámica.
 * 
 * @warning Esta matriz fue hecha dinamicamente, es necesario liberar la memoria utilizada una vez
 * que se haya terminado de usar para evitar fugas de memoria.
 * Función designada: free_matriz.
 * 
 * @pre
 * - La enumeración contenido_t debe estar definida.
 * - Las librerías stdlib.h y stdio.h deben estar incluidas.
 * @post
 * - Se retorna un puntero doble de tipo contenido_t.
 * - Se utiliza memoria del heap disponible.
 * - TOdas las celdas de la matriz son inicializadas con el valor LIBRE.
 */
contenido_t** crear_matriz(size_t longitud);

/**
 * Libera matriz dentada dinámica de tipo contenido_t de NxN.
 * 
 * @param matriz Puntero doble al primer elemento de la matriz dinámica.
 * @param longitud Longitud de la matriz dinámica.
 * 
 * @warning Esta función no se encarga de reasignar el puntero doble a un puntero NULL.
 * Es necesario hacerlo a continuación de ser llamada la función para evitar dangling pointer.
 * 
 * @pre
 *  - La matriz dinámica de NxN ya debe haber sido creada.
 *  - La enumeración contenido_t debe estar definida.
 *  - La librería stdlib.h debe estar incluida.
 * @post
 *  - La memoria dinámica asignada será liberada.
 */
void free_matriz(contenido_t** matriz, size_t longitud);

/**
 * Se remplaza el valor de una casilla LIBRE aleatorio del tablero por uno asignado.
 * 
 * @param matriz Puntero doble al primer elemento de la matriz dinámica.
 * @param longitud Longitud de la matriz dinámica.
 * @param content El valor del contenido_t que quiere ser ubicado en la matriz.
 * @param cant_pruebas Cantidad de pruebas aleatorias hasta verificar que hay espacio libre.
 * @return OPERACION_EXITOSA si se ubico el contenido correctamente en una casilla,
 *         NO_ESPACIO_MAT la matriz no tiene lugar para ubicar un contenido.
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
 * Se ubica todos los contenidos del juego en la matriz dinámica.
 * 
 * @param matriz Puntero doble al primer elemento de la matriz dinámica.
 * @param longitud Longitud de la matriz dinámica.
 * @param posx_init_cat La posicion inicial en x (filas) del gato.
 * @param posy_init_cat La posicion inicial en y (columnas) del gato.
 * @param cant_piedra La cantidad de PIEDRA que quieren ser colocadas en la matriz.
 * @param cant_llave La cantidad de LLAVE que quieren ser colocadas en la matriz.
 * @return OPERACION_EXITOSA si se pudieron asignar los contenidos correctamente.
 *         NO_ESPACIO_MAT si no hubo suficiente lugar en a matriz para asignar la 
 *         cantidad de contenidos pretendidos.
 * 
 * @pre
 * - La semilla de generador de números aleatorios debe estar inicializada.
 * - Las librerías time.h y stdlib.h deben estar incluidas.
 * - Las enumeraciónes contenido_t y error_t deben estar definidas.
 * - Los macros POSX_INIT_RATON y POSY_INIT_RATON deben estar definidos.
 * - La función ubi_rndm debe estar definida.
 * @post
 * - La matriz será modificada como efecto secundario de la función.
 * - Se retornará un mensaje del resultado del proceso en forma de error_t.
 */
error_t ubi_elements(contenido_t** matriz, size_t longitud, size_t posx_init_cat, size_t posy_init_cat,
                     size_t cant_piedra, size_t cant_llave);

/**
 * Imprime el tablero en la terminal.
 * 
 * @param matriz Puntero doble al primer elemento de la matriz dinámica.
 * @param longitud Longitud de la matriz dinámica.
 * 
 * @warning Esta función imprimirá emojis, esto es correspondiente al UTF-8. Terminales viejas pueden
 * llegar a funcionar mal con esta función. 
 * 
 * @pre
 * - La enumeración contenido_t debe estar definida.
 * - La librería stdio.h debe estar incluida.
 * @post
 * - Se imprimirá en la terinal la matriz que simboliza el tablero.
 */
void print_tablero(contenido_t** matriz, size_t longitud);

#endif