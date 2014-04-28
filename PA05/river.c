#include <stdio.h>
#include <stdlib.h>
#include "river.h"
#define INT16_MAX 34561

int main(int argc, const char * argv[])
{
    //VALIDATE INPUT
    if (argc != 2)
    {
        printf("ERROR\n");
        printf("FORMAT: ./proj4 <input>\n");
        return EXIT_FAILURE;
    }
    
    int size = 0;
    int r;
    int c;
    int ** river = river_load(argv[1], &size);
    if (river == NULL)
    {
        return EXIT_FAILURE;
    }
    
    river_build(river, size);
    
    //FIND MINIMUM
    c = size - 1;
    int minimum = 100000;
    for (r = 1; r < (2*size)-1; r += 2)
    {
        if (river[r][c] < minimum)
        {
            minimum = river[r][c];
        }
    }
    printf("%d \n", minimum + 1);
    
    for (r = 0; r < (2*size) - 1; r ++)
    {
        free(river[r]);
    }
    free(river);
    
    return EXIT_SUCCESS;
}

void river_build(int ** river, int size)
{
    int r = 0;
    int c = 0;
    Board * b = malloc(sizeof(Board) * (size * size)); //FIX MALLOC
    Board * f = malloc(sizeof(Board) * (size * size)); //FIX MALLOC
    int p = 0;
    int k = 0;
    int temp;
    
    //INITIALIZE FIRST COLUMN
    for (r = 0; r < (2*size -1); r ++)
    {
        if (r % 2 == 0)
        {
            river[r][c] = 0;
            b[p].r = r;
            b[p].c = c;
            p ++;
        }
        else if (river[r][c] == INT16_MAX)
        {
            river[r][c] = min(river[r-1][c], river[r+1][c]);
            b[p].r = r;
            b[p].c = c;
            p ++;
        }
    }
    
    temp = p; //size of p;
    
    //CONSTRUCT BY TURNS
    int turns = 0;
    int weight = 1;
    int k2;
    k = 0;
    p = 0;
    int bd; //board direction
    int change;
    bool jane = true;
    
    while (jane)
    {
        while (p < temp)
        {
            //SIFT THROUGH ARRAY FORWARD
            if (b[p].r % 2 == 0) //HORIZONTAL BOARD
            {
                if(b[p].r == 0)
                {
                    /* FIRST TRY
                     river[b[p].r + 1][b[p].c] = min(river[b[p].r + 1][b[p].c], weight);
                    
                    if (river[b[p].r + 1][b[p].c] == weight)
                    {
                        f = addtof(f, &k, b[p].r + 1, b[p].c);
                    }*/
                    
                    if (b[p].c == 0)
                    {
                        change = river[b[p].r + 1][b[p].c] - weight;
                        
                        if (change > 0)
                        {
                            river[b[p].r + 1][b[p].c] = weight;
                            f = addtof(f, &k, b[p].r+1, b[p].c);
                        }
                    }
                    else
                    {
                        change = river[b[p].r + 1][b[p].c] - weight;
                        
                        if (change > 0)
                        {
                            river[b[p].r + 1][b[p].c] = weight;
                            f = addtof(f, &k, b[p].r+1, b[p].c);
                            
                            //ADD BOARDS
                            bd = checkboard(river, b[p].r + 2, b[p].c, (2*size -2));
                            configureboard(f, &k, bd, river, b[p].r + 2, b[p].c, (2*size-2), weight);
                        }
                        
                        change = river[b[p].r + 1][b[p].c - 1] - weight;
                        
                        if (change > 0)
                        {
                            river[b[p].r + 1][b[p].c - 1] = weight;
                            f = addtof(f, &k, b[p].r+1, b[p].c - 1);
                            
                            
                            //ADD BOARDS
                            bd = checkboard(river, b[p].r + 2, b[p].c - 1, (2*size -2));
                            configureboard(f, &k, bd, river, b[p].r + 2, b[p].c - 1, (2*size-2), weight);
                        }
                    }
                }
                else if (b[p].r == (2*size -2))
                {
                    /* FIRST TRY
                    river[b[p].r - 1][b[p].c] = min(river[b[p].r - 1][b[p].c], weight);
                    
                    if (river[b[p].r - 1][b[p].c] == weight)
                    {
                        f = addtof(f, &k, b[p].r - 1, b[p].c);
                    }*/
                    
                    if (b[p].c == 0)
                    {
                        change = river[b[p].r - 1][b[p].c] - weight;
                        
                        if (change > 0)
                        {
                            river[b[p].r - 1][b[p].c] = weight;
                            f = addtof(f, &k, b[p].r-1, b[p].c);
                        }
                    }
                    else
                    {
                        change = river[b[p].r - 1][b[p].c] - weight;
                        
                        if (change > 0)
                        {
                            river[b[p].r - 1][b[p].c] = weight;
                            f = addtof(f, &k, b[p].r-1, b[p].c);
                            
                            
                            //ADD BOARDS
                            bd = checkboard(river, b[p].r - 2, b[p].c, (2*size -2));
                            configureboard(f, &k, bd, river, b[p].r - 2, b[p].c, (2*size-2), weight);
                            
                        }
                        
                        change = river[b[p].r - 1][b[p].c - 1] - weight;
                        
                        if (change > 0)
                        {
                            river[b[p].r - 1][b[p].c - 1] = weight;
                            f = addtof(f, &k, b[p].r-1, b[p].c - 1);
                            
                            
                            //ADD BOARDS
                            bd = checkboard(river, b[p].r - 2, b[p].c, (2*size -2));
                            configureboard(f, &k, bd, river, b[p].r - 2, b[p].c, (2*size-2), weight);
                        }
                    }
                }

                else if (b[p].c == 0)
                {
                    change = river[b[p].r - 1][b[p].c] - weight;
                    if (change > 0)
                    {
                        river[b[p].r - 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r-1, b[p].c);
                    }
                    
                    change = river[b[p].r + 1][b[p].c] - weight;
                    if (change > 0)
                    {
                        river[b[p].r + 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r+1, b[p].c);
                    }
                }
                else
                {
                    /* FIRST TRY
                     river[b[p].r + 1][b[p].c] = min(river[b[p].r + 1][b[p].c], weight);
                    river[b[p].r - 1][b[p].c] = min(river[b[p].r - 1][b[p].c], weight);
                    
                    if (river[b[p].r + 1][b[p].c] == weight)
                    {
                        f = addtof(f, &k, b[p].r + 1, b[p].c);
                    }
                    if (river[b[p].r - 1][b[p].c] == weight)
                    {
                        f = addtof(f, &k, b[p].r - 1, b[p].c);
                    }*/
                    
                    
                    change = river[b[p].r - 1][b[p].c - 1] - weight;
                    
                    if (change > 0)
                    {
                        river[b[p].r - 1][b[p].c - 1] = weight;
                        f = addtof(f, &k, b[p].r-1, b[p].c-1);
                        
                        //ADD BOARDS
                        bd = checkboard(river, b[p].r - 2, b[p].c - 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r - 2, b[p].c - 1, (2*size-2), weight);
                    }
                    
                    change = river[b[p].r + 1][b[p].c - 1] - weight;
                    
                    if (change > 0)
                    {
                        river[b[p].r + 1][b[p].c - 1] = weight;
                        f = addtof(f, &k, b[p].r+1, b[p].c-1);
                        
                        //ADD BOARDS
                        bd = checkboard(river, b[p].r + 2, b[p].c - 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r + 2, b[p].c - 1, (2*size-2), weight);
                    }
                    
                    change = river[b[p].r - 1][b[p].c] - weight; // change
                    
                    if (change > 0)
                    {
                        river[b[p].r - 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r-1, b[p].c);
                        
                        
                        //ADD BOARDS
                        bd = checkboard(river, b[p].r - 2, b[p].c, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r - 2, b[p].c, (2*size-2), weight);
                    }
                    
                    change = river[b[p].r + 1][b[p].c] - weight;
                    
                    if (change > 0)
                    {
                        river[b[p].r + 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r+1, b[p].c);
                        
                        
                        //ADD BOARDS
                        bd = checkboard(river, b[p].r + 2, b[p].c, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r + 2, b[p].c, (2*size-2), weight);
                    }
                }
            }
            else if (b[p].r % 2 == 1) //VERTICAL BOARD
            {
                if(b[p].c == 0) //COLUMN
                {
                    change = river[b[p].r - 1][b[p].c + 1] - weight;
                    
                    if (change > 0)
                    {
                        river[b[p].r - 1][b[p].c + 1] = weight;
                        f = addtof(f, &k, b[p].r-1, b[p].c+1);
                        bd = checkboard(river, b[p].r - 1, b[p].c + 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r-1, b[p].c+1, (2*size-2), weight);
                    }
                    
                    change =river[b[p].r + 1][b[p].c + 1] - weight;
                    if (change > 0)
                    {
                        river[b[p].r + 1][b[p].c + 1] = weight;
                        f = addtof(f, &k, b[p].r+1, b[p].c+1);
                        bd = checkboard(river, b[p].r + 1, b[p].c + 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r + 1, b[p].c + 1, (2*size-2), weight);
                    }
                    
                }
                else if (b[p].c == size - 1) // change
                {
                    change =river[b[p].r - 1][b[p].c] - weight;
                    
                    if (change > 0)
                    {
                        
                        river[b[p].r - 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r-1, b[p].c);
                        bd = checkboard(river, b[p].r - 1, b[p].c - 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r - 1, b[p].c - 1, (2*size-2), weight);

                    }
                    
                    change =river[b[p].r + 1][b[p].c] - weight;
                    
                    if(change > 0)
                    {
                        river[b[p].r + 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r+1, b[p].c);
                        bd = checkboard(river, b[p].r + 1, b[p].c - 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r + 1, b[p].c - 1, (2*size-2), weight);
                    }
                    
                }
                else
                {
                    change = river[b[p].r - 1][b[p].c + 1] - weight;
                    
                    if (change > 0)
                    {
                        river[b[p].r - 1][b[p].c + 1] = weight;
                        f = addtof(f, &k, b[p].r-1, b[p].c+1);
                        bd = checkboard(river, b[p].r - 1, b[p].c + 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r - 1, b[p].c + 1, (2*size-2), weight);
                    }
                    
                    change = river[b[p].r + 1][b[p].c + 1] - weight;
                    
                    if (change > 0)
                    {
                        river[b[p].r + 1][b[p].c + 1] = weight;
                        f = addtof(f, &k, b[p].r+1, b[p].c+1);
                        bd = checkboard(river, b[p].r + 1, b[p].c + 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r + 1, b[p].c + 1, (2*size-2), weight);
                    }
                    
                    change = river[b[p].r - 1][b[p].c] - weight; // change
                    
                    if (change > 0)
                    {
                        river[b[p].r - 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r-1, b[p].c);
                        bd = checkboard(river, b[p].r - 1, b[p].c - 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r - 1, b[p].c - 1, (2*size-2), weight);
                    }
                    
                    change = river[b[p].r + 1][b[p].c] - weight;
                    
                    if (change > 0)
                    {
                        river[b[p].r + 1][b[p].c] = weight;
                        f = addtof(f, &k, b[p].r+1, b[p].c);
                        bd = checkboard(river, b[p].r + 1, b[p].c - 1, (2*size -2));
                        configureboard(f, &k, bd, river, b[p].r + 1, b[p].c - 1, (2*size-2), weight);
                    }
                }
                
            }
            
            p++;
        }
        
        //MOVE CONTENT FROM F TO B
        p = 0;
        k2 = k;
        int count = 0;
        for (k = 0; k < k2; k ++)
        {
            b[p].r = f[k].r;
            b[p].c = f[k].c;
            
            printf("(%d, %d) ", b[p].r, b[p].c);
            count ++;
            if (b[p].c == size - 1 && b[p].r % 2 == 1)
            {
                jane = false;
            }
            p++;
        }
        
        printf("\nCount = %d", count);
        
        printf("\n");
        
        temp = p;
        p = 0;
        k = 0;
        weight++;
        turns++;
        
	  printf("TURNS = %d\n", turns);
        for (r = 0; r < ((2*(size))-1); r ++)
        {
            for (c = 0; c < size; c ++)
            {
                if (river[r][c] == 100000)
                {
                    printf("x  ");
                }
                else if (river[r][c] == INT16_MAX)
                {
                    printf("|  ");
                }
                else if (river[r][c] > 9)
                {
                    printf("%d ", river[r][c]);
                }
                else
                {
                    printf("%d  ", river[r][c]);
                }
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
       
        
        
    }
    
    free(b);
    free(f);
}

void configureboard(Board * f, int * k, int bd, int ** river, int r, int c, int size, int weight)
{
    if (bd == 0)
    {
        return;
    }
    else if (bd == 2)
    {
        int x = r + 1;
        while (x < size && river[x][c] == INT16_MAX)
        {
            river[x][c] = weight;
            addtof(f, k, x, c);
            x += 2;
        }
    }
    else if (bd == 8)
    {
        int y = r - 1;
        
        while (y > 0 && river[y][c] == INT16_MAX)
        {
            river[y][c] = weight;
            addtof(f, k, y, c);
            y -= 2;
        }
    }
    else
    {
        int z = r + 1;
        while (z < size && river[z][c] == INT16_MAX)
        {
            river[z][c] = weight;
            addtof(f, k, z, c);
            z += 2;
        }
        
        int j = r - 1;
        while (j > 0 && river[j][c] == INT16_MAX)
        {
            river[j][c] = weight;
            addtof(f, k, j, c);
            j -= 2;
        }
    }
}

Board * addtof(Board * f, int * k, int r, int c)
{
    int i = 0;
    
    if ((*k) == 0)
    {
        f[i].r = r;
        f[i].c = c;
        (*k)++;
        return f;
    }
    
    for(i = 0 ; i < (*k); i++)
    {
        if((f[i].r == r) && (f[i].c == c))
        {
            return f;
        }
    }
    f[i].r = r;
    f[i].c = c;
    (*k) ++;
    
    return f;
}

int checkboard(int ** river, int r, int c, int size)
{
    int u = 8;
    int m = 5;
    int d = 2;
    int nb = 0;
    
    if (r == 0 && river[r+1][c] == INT16_MAX )
    {
        return d;
    }
    else if (r == 0 && river[r+1][c] != INT16_MAX)
    {
        return nb;
    }
    if (r == size && river[r -1][c] == INT16_MAX)
    {
        return u;
    }
    else if (r == size && river[r -1][c] != INT16_MAX)
    {
        return nb;
    }
    
    if(river[r-1][c] == INT16_MAX && river[r+1][c] != INT16_MAX)
    {
        return u;
    }
    else if (river[r+1][c] == INT16_MAX && river[r-1][c] != INT16_MAX)
    {
        return d;
    }
    else if (river[r+1][c] == INT16_MAX && river[r-1][c] == INT16_MAX)
    {
        return m;
    }
    
    return nb;
}

int min(int x, int y)
{
    return ((x < y) ? x : y);
}

int ** river_load(const char * filename, int * size)
{
    FILE * fh;
    int ** river = NULL;
    int board;
    int g = 0;
    
    fh = fopen(filename, "r");
    if (fh == NULL)
    {
        printf("ERROR\n");
        printf("INVALID INPUT FILE!\n");
        return NULL;
    }
    
    g = fscanf(fh, "%d", size);
    if (g < 0)
      {
	printf("FSCANF ERROR\n");
	fclose(fh);
	return NULL;
      }
    
    //MAKE RIVER
    int r = 0;
    int c = 0;
    
    river = malloc(sizeof(int *) * (2*(*size) - 1));
    for (r = 0; r < ((2*(*size))-1); r++)
    {
        river[r] = malloc(sizeof(int) * ((*size)));
    }
    
    for (r = 0; r < ((2*(*size))-1); r ++)
    {
        for (c = 0; c < (*size); c ++)
        {
            river[r][c] = 100000;
        }
    }
    
    //ADD BOARDS
    for (r = 1; (r < ((2*(*size))-1)) && !feof(fh); r += 2)
    {
        for (c = 0; (c < (*size)) && !feof(fh) ; c ++)
        {
            board = fgetc(fh);
            if (board == 10)
            {
                board = fgetc(fh);
            }
            board -= 48;
            if (board == 1)
            {
                river[r][c] = INT16_MAX;
            }
        }
    }
    
    fclose(fh);
    return river;
}
