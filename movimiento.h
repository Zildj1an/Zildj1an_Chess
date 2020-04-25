#ifndef _MOVIMENTO_H_
#define _MOVIMENTO_H_

typedef struct movimiento_type {

	int s_x;
	int s_y;
	int d_x;
	int d_y;

} movimiento_t;

movimiento_t movimientos_peon[MOVS_PEON] = {
	{
		.d_x = 0,
		.d_y = -1,
	},
	{    /* Movimientos de comer */
		.d_x = 1,
		.d_y = -1,
	},
	{
		.d_x = -1,
		.d_y = -1,
	},
	{
		.d_x = 0,
		.d_y = 2,
	},
	{
		.d_x = 0,
		.d_y = -2,
	},
};

movimiento_t movimientos_torre[MOVS_TORRE] = {
	{
		.d_x = 7, /* Avanza uno en el eje x */
		.d_y = 0,
	},
	{
		.d_x = 0,.d_y = 7,
	},
	{
		.d_x = -7, /* Avanza uno en el eje x */
		.d_y = 0,
	},
	{
		.d_x = 0,.d_y = -7,
	},
	/* Esto incluye los intermedios */
};

movimiento_t movimientos_caballo[MOVS_CABALLO] = {
	{.d_x=2,.d_y=2,},{.d_x=-1,.d_y=-2,},{.d_x=-2,.d_y=-1,},{.d_x=-2,.d_y=1,},
};

movimiento_t movimientos_alfil[MOVS_ALFIL] = {
	{.d_x=7,.d_y=7,},{.d_x=-7,.d_y=-7,},{.d_x=7,.d_y=-7,},{.d_x=-7,.d_y=7,},
};

movimiento_t movimientos_rey[MOVS_REY] = {
	{.d_x=1,.d_y=1,},{.d_x=1,.d_y=0,},{.d_x=1,.d_y=-1,},{.d_x=0,.d_y=1,},
	{.d_x=0,.d_y=-1,},{.d_x=-1,.d_y=1,},{.d_x=-1,.d_y=0,},{.d_x=-1,.d_y=-1,},
};

movimiento_t movimientos_reina[MOVS_REINA] = {
	
	/* Torre */
	{
		.d_x = 7, /* Avanza uno en el eje x */
		.d_y = 0,
	},
	{.d_x = 0,.d_y = 7,},

	/* Alfil */
	{.d_x=7,.d_y=7,},{.d_x=-7,.d_y=-7,},{.d_x=7,.d_y=-7,},{.d_x=-7,.d_y=7,},
	
	/* Rey */
	{.d_x=1,.d_y=1,},{.d_x=1,.d_y=0,},{.d_x=1,.d_y=-1,},{.d_x=0,.d_y=1,},
	{.d_x=0,.d_y=-1,},{.d_x=-1,.d_y=1,},{.d_x=-1,.d_y=0,},{.d_x=-1,.d_y=-1,},
};


#endif