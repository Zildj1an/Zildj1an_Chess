#ifndef _MOVIMENTO_H_
#define _MOVIMENTO_H_

void moverse_sin_jaque(pieza_t tab[8][8],movimiento_t *movimientos)
{

}

void make_move(pieza_t tab[8][8],movimiento_t movimiento)
{
	movimiento_t movimientos[piezas_blancas_vivas];

	moverse_sin_jaque(tab,movimientos);
	// A Las que puedan moverse sin que me den jaque.
	// A y B Que coman una de mas peso
	// A y B y que no sea comida.
}

#endif