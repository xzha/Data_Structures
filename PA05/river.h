#ifndef RIVER_H
#define RIVER_H

typedef struct _node{
    int r; //row
    int c; //column
}Board;

typedef int bool;
#define true 1
#define false 0

int min(int x,int y);
int ** river_load(const char * filename, int * size);
void river_build(int ** river, int size);
Board * addtof(Board * f, int * k, int r, int c);
int checkboard(int ** river, int r, int c, int size);
void configureboard(Board * f, int * k, int bd, int ** river, int r, int c, int size, int weight);

#endif
