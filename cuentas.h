#ifndef CUENTAS_H
#define CUENTAS_H

#include <stdbool.h>
#include <stdio.h>

#define TABLA_MAX 100
#define TABLA_MIN 5

/**
 * Se solicita al usuario cual es la tabla de multiplicar máxima que desea que aparezca en el problema.
 * 
 * @return Entero entre TABLA_MAX y TABLA_MIN que simboliza la tabla máxima deseada por el usuario.
 * 
 * @pre
 * - La librería stdio.h debe estar incluida.
 * - Los macros TABLA_MAX y TABLA_MIN deben estar definidos.
 * @post
 * - Es una función que se comunicará con el usuario a travez de la terminal y obtendrá el entero de
 * retorno a travez de lo ingresado por el usuario.
 */
int soli_max_numero(void);

#endif