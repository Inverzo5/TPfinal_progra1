#include "movimiento.h"

void movimientos_disponibles(contenido_t** matriz, size_t longitud, size_t ubix, size_t ubiy, move_disp_t* posible_mov)
{
    for (size_t i = 0; i < NUM_DIREC; i++) //limpiamos posible_mov primero.
    {
        posible_mov->movs[i] = false;
    }


    const int direct_incr[NUM_DIREC][2] = {
        {0,  1}, // Derecha
        {0, -1}, // Izquierda
        {-1, 0}, // Arriba
        {1,  0}  // Abajo
    };

    for (size_t i = 0; i < NUM_DIREC; i++)
    {
        bool direc_en_tablero = true; //Variable flag que controla si la dirección pretendida salta del tablero.

        if ((ubix == 0 && direct_incr[i][0] < 0) || (ubiy == 0 && direct_incr[i][1] < 0))
        {
            direc_en_tablero = false;
        }
        if ((ubix == longitud - 1 && direct_incr[i][0] > 0) || (ubiy == longitud - 1 && direct_incr[i][1] > 0))
        {
            direc_en_tablero = false;
        }        

        if (direc_en_tablero && matriz[ubiy + direct_incr[i][1]][ubix + direct_incr[i][0]] != PIEDRA)
        {
            posible_mov->movs[i] = true;
        }
    }
}

error_t mover(contenido_t* origen, contenido_t* destino, bool* is_llave)
{
    if (origen == NULL || destino == NULL)
    {
        return PUNTERO_NULO;
    } else
    {
        if (*destino == LLAVE)
        {
            *is_llave = true;
        }
        *destino = *origen;
        *origen = LIBRE;
        return OPERACION_EXITOSA;
    }
}

priority_t calc_priority(size_t ubix_cat, size_t ubiy_cat, size_t ubix_raton, size_t ubiy_raton)
{
    size_t dif_x;
    size_t dif_y;
    direcciones_t max_priority = NO_DIR;
    direcciones_t segunda_priority = NO_DIR;
    
    if (ubix_cat > ubix_raton && ubiy_cat > ubiy_raton) //El gato está al sureste del ratón.
    {
        dif_x = ubix_cat - ubix_raton;
        dif_y = ubiy_cat - ubiy_raton;
        max_priority = (dif_x > dif_y) ? IZQUIERDA : ARRIBA;
        segunda_priority = (max_priority == IZQUIERDA) ? ARRIBA : IZQUIERDA;
    } else if(ubix_cat > ubix_raton && ubiy_cat < ubiy_raton) { //El gato está al noreste del ratón.
        dif_x = ubix_cat - ubix_raton;
        dif_y = ubiy_raton - ubiy_cat;
        max_priority = (dif_x > dif_y) ? IZQUIERDA : ABAJO;
        segunda_priority = (max_priority == IZQUIERDA) ? ABAJO : IZQUIERDA;
    } else if(ubix_cat < ubix_raton && ubiy_cat > ubiy_raton) { //El gato está al suroeste del ratón.
        dif_x = ubix_raton - ubix_cat;
        dif_y = ubiy_cat - ubiy_raton;
        max_priority = (dif_x > dif_y) ? DERECHA : ARRIBA;
        segunda_priority = (max_priority == DERECHA) ? ARRIBA : DERECHA;
    } else { //El gato está al noroeste del ratón.
        dif_x = ubix_raton - ubix_cat;
        dif_y = ubiy_raton - ubiy_cat;
        max_priority = (dif_x > dif_y) ? DERECHA : ABAJO;
        segunda_priority = (max_priority == DERECHA) ? ABAJO : DERECHA;
    }
    
    direcciones_t tercera_priority = NO_DIR;
    direcciones_t ultima_priority = NO_DIR;

    switch(max_priority) {
        case ARRIBA:    ultima_priority = ABAJO; break;
        case ABAJO:     ultima_priority = ARRIBA; break;
        case IZQUIERDA: ultima_priority = DERECHA; break;
        case DERECHA:   ultima_priority = IZQUIERDA; break;
    }
    switch(segunda_priority) {
        case ARRIBA:    tercera_priority = ABAJO; break;
        case ABAJO:     tercera_priority = ARRIBA; break;
        case IZQUIERDA: tercera_priority = DERECHA; break;
        case DERECHA:   tercera_priority = IZQUIERDA; break;
    }
    priority_t orden_priority = {.orden = {max_priority, segunda_priority, tercera_priority, ultima_priority}};
    return orden_priority;
}

error_t move_cat(contenido_t** matriz, size_t longitud, size_t ubix_cat, size_t ubiy_cat, size_t ubix_raton, size_t ubiy_raton)
{
    move_disp_t disp_cat; //No hace falta inicializarla puesto que se limpia en la función.
    movimientos_disponibles(matriz, longitud, ubix_cat, ubiy_cat, &disp_cat);

    priority_t prioridad = calc_priority(ubix_cat, ubiy_cat, ubix_raton, ubiy_raton);

    direcciones_t mov_resultante = NO_DIR;

    for (size_t i = 0; i < NUM_DIREC; i++)
    {
        if (prioridad.orden[i] != NO_DIR && disp_cat.movs[prioridad.orden[i]])
        {
            mov_resultante = prioridad.orden[i];
        }    
    }

    if (mov_resultante == NO_DIR) // Si no se encontró una dirección válida, hay un bug lógico o el gato está bloqueado.
    {
        for (size_t i = 0; i < NUM_DIREC; i++)
        {
            if ((disp_cat.movs[i]))
            {
                mov_resultante = (direcciones_t) i;
            }
        }
    }
    
    if (mov_resultante == NO_DIR)
    {
        return CONTENIDO_BLOQUEADO;
    } else
    {
        bool llave = false; //El gato ignora el hecho de que haya llave, ignoramos esta variable.

        switch(mov_resultante) {
        case ARRIBA:    mover(matriz[ubiy_cat][ubix_cat], matriz[ubiy_cat - 1][ubix_cat], &llave); break;
        case ABAJO:     mover(matriz[ubiy_cat][ubix_cat], matriz[ubiy_cat + 1][ubix_cat], &llave); break;
        case IZQUIERDA: mover(matriz[ubiy_cat][ubix_cat], matriz[ubiy_cat][ubix_cat - 1], &llave); break;
        case DERECHA:   mover(matriz[ubiy_cat][ubix_cat], matriz[ubiy_cat][ubix_cat + 1], &llave); break;
        }
        return OPERACION_EXITOSA;
    }
}