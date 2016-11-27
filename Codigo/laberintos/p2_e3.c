#include "Maze.h"
#include "stack.h"

Bool maze_recorrer(Maze *pm, Point *pp){
	Stack *pstack;
	EleStack *pele, *paux;
	Point *ppoint, *pnb; /*pnb es puntero a neighborPoint*/
	char symbol;
	int x, y, i;
	if(!pm || !pp) goto ERR1;

	pstack = stack_ini();
	if(!pstack) goto ERR1;

	pele = elestack_ini();
	if(!pele) goto ERR2;

	pele = elestack_setInfo(pele, pp);
	if(!pele) goto ERR2;

	pstack = stack_push(pstack, pele);
	if(!pstack) goto ERR3;

	elestack_free(pele);

	while(stack_isEmpty(pstack) == FALSE){
		pele = stack_pop(pstack);
		if(!pele) goto ERR2;

		symbol = point_getSymbol(elestack_getInfo(pele));
		if(symbol == ERRORCHAR) goto ERR3;

		if(symbol == OUTPUT){
			goto RES;
		}
		
		x = point_getCoordinateX(elestack_getInfo(pele));
		y = point_getCoordinateY(elestack_getInfo(pele));
		if (x==-1||y==-1) goto ERR3;

		elestack_free(pele);



		ppoint = point_setSymbol(maze_getPoint(pm, x, y), VISITED);
		if(!ppoint) goto ERR2;

		for(i=0; i<=3; i++){
			pnb = maze_getNeighborPoint(pm, ppoint, i);
			if(!pnb) goto ERR2;

			/*point_print(stdout, ppoint);
			fprintf(stdout, "%d", i);
			fprintf(stdout, "\n");
			point_print(stdout, pnb);
			
			fprintf(stdout, "\n");*/

			symbol = point_getSymbol(pnb);
			if(symbol == ERRORCHAR) goto ERR2;


			if(symbol != BARRIER && symbol!=VISITED){
				paux = elestack_ini();
				if(!paux) goto ERR2;

				paux = elestack_setInfo(paux, pnb);
				if(!paux) goto ERR2;

				pstack = stack_push(pstack, paux);
				if(!pstack){
					elestack_free(paux);
					goto ERR2;
				}

				elestack_free(paux);
			}
			
		}

	}	

	goto ERR2;

	RES:
		stack_free(pstack);
		return TRUE;
	ERR3:
		elestack_free(pele);
	ERR2:
		stack_free(pstack);
	ERR1:
		stack_free(pstack);
		return FALSE;

}

int main(int argc, char *argv[]){
	Maze *pm;
	Point *pinput = NULL;
	FILE *f;

	f = fopen(argv[1], "r");


	pm = maze_ini();
	if(!pm) goto ERR1;
	
	pm = maze_read(f, pm);
	if(!pm) goto ERR2;

	pinput = maze_getInput(pm);
	if(!pinput) goto ERR2;

	if(maze_recorrer(pm, pinput) == TRUE){
		maze_free(pm);
		fprintf(stdout, "Es posible encontrar un camino\n");
		fclose(f);
		return 0;
	}

		maze_free(pm);
		fprintf(stdout, "No es posible encontrar un camino\n");
		fclose(f);
		return 0;



	ERR2:	
		printf ("flag");
		maze_free(pm);
	ERR1:
		fclose(f);
		return -1;
}