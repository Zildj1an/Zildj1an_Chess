#include <stdio.h>
#include <stdlib.h>

#include "tablero.h"
#include "movimiento.h"


int main(void){

	movimiento_t movimiento;

	init_tablero();

//printf("hola\n");
	// TODO COLE

	while (!jaque_mate){

		print_tablero();
		scanf("%d %d %d %d",&movimiento.s_y,&movimiento.s_x,&movimiento.d_y,&movimiento.d_x);
		update_tablero(movimiento);
		print_tablero();

		//make_move(movimiento);
		//update_tablero(movimiento);
	}

	exit(0);
}
