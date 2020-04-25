#ifndef _CHESS_H_
#define _CHESS_H_

typedef enum {

	PEON,TORRE,CABALLO,ALFIL,REY,REINA,VACIO,NUM_PIEZAS

} tipo_pieza_t;

typedef enum color_pieza_t {

	BLANCO,NEGRO

} color_pieza_t;

typedef struct pieza_type {

	tipo_pieza_t tipo;
	char descripcion[3];
	color_pieza_t color;
	int viva;
	int num_movs;
	movimiento_t *movimientos;
	
} pieza_t;

static pieza_t tablero[ROWS][COLUMNS];
static pieza_t backup_tablero[ROWS][COLUMNS];
static int jaque_mate;
static int piezas_blancas_vivas;
static int piezas_negras_vivas;

static inline void backup(void){
	memcpy(tablero,backup_tablero,sizeof(tablero));
}

static void init_pieza(int x, int y, int color, int tipo)
{
	static int blanca_index = 0, negra_index = 0;
	pieza_t *p = &tablero[x][y];

	p->color = color;
	p->tipo = tipo;
	p->viva = (p->tipo == VACIO) ? 0 : 1;
	
	switch(tipo){
		case PEON:
			sprintf(p->descripcion," P");
			p->num_movs = MOVS_PEON;
			p->movimientos = movimientos_peon;
		break;
		case TORRE:
			sprintf(p->descripcion," T");
			// TODO mejorar y mucho los movimientos
			p->num_movs = MOVS_TORRE;
			p->movimientos = movimientos_torre;
		break;
		case CABALLO:
			sprintf(p->descripcion," C");
			p->num_movs = MOVS_CABALLO;
			p->movimientos = malloc(sizeof(movimiento_t) * p->num_movs);
			p->movimientos = movimientos_caballo;
		break;
		case ALFIL:
			sprintf(p->descripcion," A");
			p->num_movs = MOVS_ALFIL;
			p->movimientos = movimientos_alfil;
			/* Estos incluyen los intermedios */
		break;
		case REY:
			sprintf(p->descripcion," R");
			p->num_movs = MOVS_REY;
			p->movimientos = movimientos_rey;
		break;
		case REINA:
			sprintf(p->descripcion,"Ra");
			p->num_movs = MOVS_REINA;
			p->movimientos = movimientos_reina;
		break;
		case VACIO:
			sprintf(p->descripcion,"   ");
		break;
		default:
			fprintf(stderr,"Tipo de pieza %d desconocido.\n",tipo);
			return;
	}

	if (p->color == BLANCO && p->tipo != VACIO){
		sprintf(p->descripcion, "%sb",p->descripcion);
	}
	else if (p->tipo != VACIO){
		sprintf(p->descripcion, "%sn",p->descripcion);
	}
}

static inline void update_tablero(movimiento_t movimiento)
{
	int d_x = movimiento.d_x;
	int s_x = movimiento.s_x;
	int d_y = movimiento.d_y;
	int s_y = movimiento.s_y;

	memcpy(backup_tablero,tablero,sizeof(tablero));

	if (tablero[d_x][d_y].tipo != VACIO)
	{
		tablero[d_x][d_y].viva = 0;

		if (tablero[d_x][d_y].color == BLANCO){
			piezas_blancas_vivas--;

		}
		else piezas_negras_vivas--;
	}

	init_pieza(d_x,d_y,tablero[s_x][s_y].color,tablero[s_x][s_y].tipo);
	init_pieza(s_x,s_y,BLANCO,VACIO);
}

void print_tablero(void)
{
	int i = 0, j = COLUMNS - 1;

	printf("  ");

	for (i = 0; i < COLUMNS; ++i){
			printf("---|");	
	}

	printf("\n");

	/* Primero van las negras */
	for (; j >= 0; j--){
		printf("%d|",j);
		for (i = 0; i < COLUMNS; ++i){
			printf("%s|",tablero[i][j].descripcion);	
		}
		printf("\n  ");
		for (i = 0; i < COLUMNS; ++i){
			printf("---|");	
		}
		printf("\n");
	}

	printf("  ");

	for (i = 0; i < COLUMNS; ++i){
		printf(" %d  ",i);	
	}
	printf("\n  WHITE = %d   BLACK = %d \n", 
				piezas_blancas_vivas,piezas_negras_vivas);
	printf("\n");
}

static void init_tablero(void)
{
	int i = 0,j;

	jaque_mate = 0;
	piezas_blancas_vivas = TOTAL_PIEZAS;
	piezas_negras_vivas = TOTAL_PIEZAS;

	for(; i < COLUMNS; i++){
		for(j = 0; j < ROWS; j++){
			init_pieza(i,j,BLANCO,VACIO);
		}
	}

	/* Peones */
	for (i = 0; i < COLUMNS; ++i){
		init_pieza(i,1,BLANCO,PEON);
		init_pieza(i,6,NEGRO,PEON);
	}
	
	/* Torres,caballos,alfiles izda */
	for (i = 0; i < 3; i++){
		init_pieza(i,0,BLANCO,i+1);
		init_pieza(i,7,NEGRO,i+1);
	}
	
	j = 2;
	/* Torres,caballos,alfiles dcha*/
	for (i = 5; i < COLUMNS; i++ && j--){
		init_pieza(i,0,BLANCO,j+1);
		init_pieza(i,7,NEGRO,j+1);
	}

	/* Rey */
	init_pieza(4,0,BLANCO,REY);
	init_pieza(4,7,NEGRO,REY);

	/* Reinas */
	init_pieza(3,0,BLANCO,REINA);
	init_pieza(3,7,NEGRO,REINA);
}


#endif