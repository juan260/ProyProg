#include <stdio.h>
#include <stdlib.h>

#include "Maze.h"
#include <limits.h>


#define MAX 100000000

struct _Maze{
    Point *point[MAX];
    int rows, cols, size;
    Point *in;
    Point *out;
};

Maze * maze_ini(){
    Maze *pm = NULL;
    int i;
    
    pm = (Maze *) malloc (sizeof(Maze));
    if(!pm) return NULL;

    pm->rows = 0;
    pm->cols = 0;
    pm->size = 0;
    
    for (i = 0; i < MAX; ++i)
    {
        pm->point[i] = NULL;
    }
    
    return pm;
}


void maze_free(Maze *pm){
    int i;
    for(i=0; i<MAX; i++){
        point_free(pm->point[i]);
    }
    point_free(pm->in);
    point_free(pm->out);
    free(pm);
}

int maze_getNrows(const Maze *pm){
    if(!pm) return -1;
    return pm->rows;
}

int maze_getNcols(const Maze *pm){
    if(!pm) return -1;
    return pm->cols;
}

Point * maze_getInput(const Maze *pm){
    if(!pm) return NULL;
    
    return pm->in;
}

Point * maze_getOutput(const Maze *pm){
    if(!pm) return NULL;
    
    return pm->out;
}

Point * maze_getPoint(const Maze *pm, const int x, const int y){
    int posicion;
    
    if(!pm || x < 0 || x > pm->cols || y < 0 || y > pm->rows) return NULL;
    
    posicion = y*pm->cols + x;
    
    return pm->point[posicion];
}

Point * maze_getNeighborPoint(const Maze *pm, const Point *pp, const Move mov){
    int x, y;
    if(!pm || !pp) return NULL;
    x = point_getCoordinateX(pp); 
    y = point_getCoordinateY(pp);
    switch (mov){
        case(RIGHT):
            return maze_getPoint(pm, x+1, y);
                
        case(LEFT):
            return maze_getPoint(pm, x-1, y);
            
        case(UP):
            return maze_getPoint(pm, x, y-1);
            
        case(DOWN):
            return maze_getPoint(pm, x, y+1);
            
        case(STAY):
            return maze_getPoint(pm, x, y);
    }
    
    return NULL; 
}


Maze * maze_setSize(Maze *pm, int nrow, int ncol){
    if(!pm || nrow * ncol > MAX) return NULL;
    
    pm->cols = ncol;
    pm->rows = nrow;
    pm->size = nrow * ncol;
    
    return pm;
}

Maze * maze_addPoint(Maze *pm, const Point *pp){
    int x, y, posicion;
    
    if(!pm || !pp) return NULL;
    
    x = point_getCoordinateX(pp);
    if(x==-1) return NULL;
    
    y = point_getCoordinateY(pp);
    if(y==-1) return NULL;
    
    posicion = y * pm->cols + x;
    
    pm->point[posicion] = point_copy(pp);
    if(!pm->point[posicion]) return NULL;
    
    return pm;
}

int maze_print(FILE *f, const Maze *pm){
    int x, y, posicion, cantidad=0;
    char symbol;
    
    if(!f || !pm) return -1;
    
    for(y=0; y<pm->rows; y++){
        for(x=0; x<pm->cols; x++){
            posicion = y * pm->cols + x;
            symbol = point_getSymbol(pm->point[posicion]);
            cantidad += fprintf(f, "%c", symbol);
        }
        fprintf(f, "\r\n"); /*Introducimos \r para evitar problemas relacionados con la impresion de saltos de linea*/
    
    }
    return cantidad;
}

Maze *maze_read (FILE *f, Maze *pm){
    int x, y, nrows, ncols, posicion; /*La coordenada X se corresponde con el número de columnas (coordenada horizontal) y la Y se corresponde con el numero de filas*/
    char buff[MAX];
    Point *temp = NULL;
    
    if(!f || !pm) return NULL;
    
    temp = point_ini();
    if (temp==NULL) return NULL;
    
    fgets(buff, MAX, f);
    sscanf(buff, "%d %d", &nrows, &ncols);
    
    pm = maze_setSize (pm, nrows, ncols);
    if(!pm){
        point_free(temp);
        return NULL;
    }
    
    for(y=0; y<nrows; y++){
        fgets(buff, MAX, f);
        for(x=0; x<ncols; x++){
            point_setCoordinateX(temp, x);
            point_setCoordinateY(temp, y);
            point_setSymbol(temp, buff[x]);
            
            maze_addPoint(pm, temp);
            posicion = y * ncols + x;
            if(!pm->point[posicion]){
                point_free(temp);
                return NULL;
            }
            
            if(buff[x] == INPUT){
                pm->in = point_copy(pm->point[posicion]);
            }
            
            if(buff[x] == OUTPUT){
                pm->out = point_copy(pm->point[posicion]);
            }
        }
    }


    
    point_free(temp);
    return pm;
}

