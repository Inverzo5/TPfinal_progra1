#ifndef ERRORES_H
#define ERRORES_H

/**
 * Enumeración que administra los diferentes tipos de errores que pueden suceder en el manejo del programa. 
 * */
typedef enum{
    OPERACION_EXITOSA, //La operación funcionó como se espera.

    NO_ESPACIO_MAT, //La matriz no tiene espacio para ubicar algun contenido.

    PUNTERO_NULO, //Un puntero asignado apunta a NULL.
}error_t;

#endif