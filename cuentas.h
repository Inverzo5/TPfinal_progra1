#ifndef CUENTAS_H
#define CUENTAS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TABLA_MAX 100
#define TABLA_MIN 5

/**
 * Se solicita al usuario cual es la tabla de multiplicar máxima que desea que aparezca en el problema.
 * 
 * @return Entero entre TABLA_MAX y TABLA_MIN que simboliza la tabla máxima deseada por el usuario.
 * 
 * @pre
 * - Las librerías stdio.h y stdlib.h deben estar incluidas.
 * - Los macros TABLA_MAX y TABLA_MIN deben estar definidos.
 * @post
 * - Es una función que se comunicará con el usuario a travez de la terminal y obtendrá el entero de
 * retorno a travez de lo ingresado por el usuario.
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

bool ope_player();

#endif