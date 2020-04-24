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
} pieza_t;

typedef struct movimiento_type {

	int s_x;
	int s_y;
	int d_x;
	int d_y;

} movimiento_t;

static pieza_t tablero[8][8];
static movimiento_t blancas[16]; 
static int jaque_mate;
static int piezas_blancas_vivas;
static int piezas_negras_vivas;

static inline void init_pieza(int x, int y, int color, int tipo)
{
	static int blanca_index = 0;
	pieza_t *p = &tablero[x][y];

	p->color = color;
	p->tipo = tipo;

	switch(tipo){
		case PEON:
			sprintf(p->descripcion," P");
		break;
		case TORRE:
			sprintf(p->descripcion," T");
		break;
		case CABALLO:
			sprintf(p->descripcion," C");
		break;
		case ALFIL:
			sprintf(p->descripcion," A");
		break;
		case REY:
			sprintf(p->descripcion," R");
		break;
		case REINA:
			sprintf(p->descripcion,"Ra");
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

	/* Mantener las blancas localizadas */
	if (p->color == BLANCO && p->tipo != VACIO){
		blancas[blanca_index++].s_x = x;
		blancas[blanca_index++].s_y = y;
	}
}

static inline void update_tablero(movimiento_t movimiento)
{
	int d_x = movimiento.d_x;
	int s_x = movimiento.s_x;
	int d_y = movimiento.d_y;
	int s_y = movimiento.s_y;

	if (tablero[d_x][d_y].tipo != VACIO){
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
	int i = 0, j = 7;

	printf("  ");

	for (i = 0; i < 8; ++i){
			printf("---|");	
	}

	printf("\n");

	/* Primero van las negras */
	for (; j >= 0; j--){
		printf("%d|",j);
		for (i = 0; i < 8; ++i){
			printf("%s|",tablero[j][i].descripcion);	
		}
		printf("\n  ");
		for (i = 0; i < 8; ++i){
			printf("---|");	
		}
		printf("\n");
	}

	printf("  ");

	for (i = 0; i < 8; ++i){
		printf(" %d  ",i);	
	}
	printf("\n");
}

static void init_tablero(void)
{
	int i = 0,j;

	jaque_mate = 0;
	piezas_blancas_vivas = piezas_negras_vivas = 16;

	for(; i < 8; i++){
		for(j = 0; j < 8; j++){
			init_pieza(i,j,BLANCO,VACIO);
		}
	}

	/* Peones */
	for (i = 0; i < 8; ++i){
		init_pieza(1,i,BLANCO,PEON);
		init_pieza(6,i,NEGRO,PEON);
	}
	
	/* Torres,caballos,alfiles izda */
	for (i = 0; i < 3; i++){
		init_pieza(0,i,BLANCO,i+1);
		init_pieza(7,i,NEGRO,i+1);
	}
	
	j = 2;
	/* Torres,caballos,alfiles dcha*/
	for (i = 5; i < 8; i++ && j--){
		init_pieza(0,i,BLANCO,j+1);
		init_pieza(7,i,NEGRO,j+1);
	}

	/* Rey */
	init_pieza(0,4,BLANCO,REY);
	init_pieza(7,4,NEGRO,REY);

	/* Reinas */
	init_pieza(0,3,NEGRO,REINA);
	init_pieza(7,3,BLANCO,REINA);
}


#endif