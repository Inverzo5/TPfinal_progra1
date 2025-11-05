#ifndef CONTROL_GENERAL_H
#define CONTROL_GENERAL_H

#define MAX_BUFFER 20

/**
 * Enumeración que administra los diferentes tipos de errores que pueden suceder en el manejo del programa. 
 * */
typedef enum{
    OPERACION_EXITOSA,    //La operación funcionó como se espera.
    OPERACION_EN_PROCESO, //La operación esta en proceso.

    NO_ESPACIO_MAT,       //La matriz no tiene espacio para ubicar algun contenido.

    PUNTERO_NULO,         //Un puntero asignado apunta a NULL.

    CONTENIDO_BLOQUEADO   //Un contenido movil no puede moverse.
}error_t;

/**
 * Estado del juego en el momento.
 */
typedef enum{
    EN_JUEGO, //Se está desarrollando la partida.
    VICTORIA, //El usuario resulto ganador.
    DERROTA,  //El usuario resulto perdedor.
}estado_t;

#endif