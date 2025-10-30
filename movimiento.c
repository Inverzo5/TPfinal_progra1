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