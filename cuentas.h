#ifndef CUENTAS_H
#define CUENTAS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "extras.h"

#define TABLA_MAX 10000
#define TABLA_MIN 5

/**
 * Se solicita al usuario que indique la tabla de multiplicar más alta que desea que aparezca en el juego.
 * 
 * @return Entero entre TABLA_MAX y TABLA_MIN que representa la tabla más alta deseada por el usuario.
 * 
 * @pre
 * - Las librerías ctype.h, stdio.h y stdlib.h deben estar incluidas.
 * - Los macros TABLA_MAX y TABLA_MIN deben estar definidos.
 * - El header local extras.h debe estar incluido.
 * @post
 *  - Se retornará un entero obtenido a traves de comunicación con el usuario.
 */
int soli_max_numero(void);

/**
 * Se le consulta al jugador el resultado de la cuenta necesaria para mover al ratón.
 * 
 * @param num1 El primer número entero que forma parte de la cuenta.
 * @param num2 El segundo número entero que forma parte de la cuenta.
 * @return El resultado de la operación que cree correcta el jugador.
 * 
 * @pre
 * - Las librerías <stdio.h> y <stdlib.h> deben estar incluidas.
 * - Tanto num1 como num2 tienen que ser enteros positivos.
 * @post
 * - Es una función que se comunicará con el usuario a travez de la terminal y obtendrá el entero de
 * retorno a travez de lo ingresado por el usuario.
 */
int consult_result(int num1, int num2);

/**
 * Se le hace la cuenta matemática al usuario.
 * 
 * @param tabla_max El número más grande que puede aparecer en la cuenta.
 * @return true en caso de haber resuelto correctamente la cuenta
 *         false en caso de que se haya equivocado.
 * 
 * @pre
 * - La librería stdlib.h y stdio.h deben estar incluidas.
 * - La semilla de rand debe estar inicializada.
 * - La función consult_result debe estar declarada.
 * @post
 * - Se comunica con el usuario a travez de la terminal.
 */
bool ope_player(int tabla_max);

#endif