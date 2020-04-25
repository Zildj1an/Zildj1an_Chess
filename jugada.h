#ifndef _JUGADA_H_
#define _JUGADA_H_

#define pieza_negra(x,y) \
	tablero[x][y].color == NEGRO && tablero[x][y].viva 

static inline int invalid_movement(movimiento_t *movimiento, int color){

	int x,y,s_x,s_y,d_x,d_y;
	s_x = movimiento->s_x;
	s_y = movimiento->s_y;
	d_x = movimiento->d_x;
	d_y = movimiento->d_y;

	if (s_x > 7 || s_x < 0 || d_x > 7 || d_x < 0 ||
		s_y > 7 || s_y < 0 || d_y > 7 || d_y < 0 ||
		d_x > 7 || d_x < 0 || d_x > 7 || d_x < 0 ||
		d_y > 7 || d_y < 0 || d_y > 7 || d_y < 0 ||
		(s_x == d_x && s_y == d_y)){
		return 1;
	}

	if (!(tablero[s_x][s_y].viva)||(tablero[s_x][s_y].color != color)){
		return 1;
	}

	if (tablero[d_x][d_y].color == color && tablero[d_x][d_y].viva){
		return 1;
	}

	/* Check that there is no obstacle in between */
	if (tablero[s_x][s_y].tipo != CABALLO){

		for (x = s_x + 1; x < d_x; ++x){
			if (tablero[x][d_y].viva){
				return 1;
			}
		}
		for (y = s_y + 1; y < d_y; ++y){
			if (tablero[d_x][y].viva){
				return 1;
			}
		}
		for (x = s_x - 1; x > d_x; --x){
			if (tablero[x][d_y].viva){
				return 1;
			}
		}
		for (y = s_y - 1; y > d_y; --y){
			if (tablero[d_x][y].viva){
				return 1;
			}
		}
	}

	if (tablero[s_x][s_y].tipo == PEON){
		/* Only to eat */
		if (s_x != d_x && !tablero[d_x][d_y].viva){
			return 1;
		}
		/* Only 2 at the start */
		if (s_y + 2 == d_y){
			if (tablero[s_x][s_y].color != BLANCO) return 1;
			if (s_y != 1) return 1;
		}
		if (s_y - 2 == d_y){
			if (tablero[s_x][s_y].color != NEGRO) return 1;
			if (s_y != 6) return 1;
		}
	}

	/* TODO invalidez por pieza (usuario) */

	return 0;
}

static inline int siguiente_negra(int *x, int *y)
{
	static int i = 0,j = 0;

	for(; i < COLUMNS;++i){
		for (; j < ROWS;j++){
			if (pieza_negra(i,j)){
				*x = i;
				*y = j++;
				if (j == ROWS) {
					j = 0;
					i++;
				}
				return 1;
			}
		}
		j = 0;
	}

	i = 0;
	j = 0;

	return 0;
}

int moverse(movimiento_t *movimientos, nivel_gamer nivel)
{
	int i = 0, j = 0, s = 0, add = 0;
	movimiento_t intento;

	while (siguiente_negra(&i,&j)){
		for (; s < tablero[i][j].num_movs; s++){
			
			intento = tablero[i][j].movimientos[s];
			intento.s_x = i;
			intento.s_y = j;
			intento.d_x = intento.s_x + intento.d_x;
			intento.d_y = intento.s_y + intento.d_y;

			/* TODO ver intentos */
try:		if (!invalid_movement(&intento,NEGRO)){
				// TODO check que no me den jaque
				switch(nivel){
				case NO_JAQUE:
					movimientos[add++] = intento;
					break;
				case EAT:
					if (tablero[intento.d_x][intento.d_y].viva){
						movimientos[add++] = intento;
						return 1; // Hasta que lo haga mas rapido
					}
					break;

				}
			}

			/* Intentar valores intermedios */
			if (tablero[i][j].tipo == TORRE || tablero[i][j].tipo == ALFIL){
				if (i == intento.d_x){
					if (intento.d_y){
						intento.d_y--;
						goto try;
					}
				}
				else {
					if (intento.d_x){
						intento.d_x--;
						goto try;
					}
				}
			}
		}
	}
	return add;
}

/* Elige movimiento en las negras */
int make_move(movimiento_t *movimiento)
{
	int ret;
	movimiento_t movimientos[piezas_negras_vivas];

	/* Try to eat something of more weight and no chess mate */

	// TODO

	/* Try to eat something and no chess mate */

	ret = moverse(movimientos,EAT);
	if (ret) goto success;

	/* Try to move it without chess mate */

	ret = moverse(movimientos,NO_JAQUE);

	if (ret){
success:	movimiento->s_x = movimientos[0].s_x;
			movimiento->d_x = movimientos[0].d_x;
			movimiento->s_y = movimientos[0].s_y;
			movimiento->d_y = movimientos[0].d_y;
			return 1;
	}
	return 0;
}

#endif