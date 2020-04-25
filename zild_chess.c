#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "movimiento.h"
#include "tablero.h"
#include "jugada.h"


int main(void){

	movimiento_t mov;

	init_tablero();
	print_tablero();

	while (!jaque_mate){
user:
		scanf("%d %d %d %d",&mov.s_x,&mov.s_y,&mov.d_x,&mov.d_y);
		
		if (invalid_movement(&mov, BLANCO)){
			fprintf(stderr, "No puedes mover esa pieza ahi!\n");
			continue;
		}

		update_tablero(mov);
		print_tablero();

		/* Enter */
		scanf("%d",&mov.s_x);

		/* Use zero to restore previous board */
		if (!mov.s_x){
			backup();
			print_tablero();
			printf("Board restored.\n");
			goto user;
		}

		if (make_move(&mov)) {
			update_tablero(mov);
			print_tablero();
			printf("Mov: (%d,%d)->(%d,%d)\n",mov.s_x,mov.s_y,mov.d_x,mov.d_y);
		}
		else { // TODO movimiento jaque
			printf("No se me ocurre nada...\n");
			break;
		}
	}

	exit(0);
}
