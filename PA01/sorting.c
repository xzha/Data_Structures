#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sorting.h"

long * Load_File(char * Filename, int * Size)
{
  FILE * fh; 
  long * Array_toSort;
  int i = 0;
  int g;
  
  //CHECK FILE STATUS
  fh = fopen(Filename, "r");
  if (fh == NULL)
    {
      printf("ERROR\n");
      printf("INVALID INPUT FILE");
      return NULL;
    }

  //READ FIRST LINE
  g = fscanf(fh, "%d", Size);
  if (g != 1)
    {
      printf("ERROR1\n");
      return NULL;
    }

  //STORE THE ARRAY
  Array_toSort = malloc(sizeof(long) * (*Size));
  while (!feof(fh))
    {
      g = fscanf(fh, "%ld", &Array_toSort[i]);
      i++;
    }
  if (g > 0)
    {
      printf("ERROR2\n");
      return NULL;
    }


  fclose(fh);
  return Array_toSort;
}

void Shell_Insertion_Sort(long * array, int size, double *N_comp, double *N_Move)
{
  int * sequence = Sequence_make(size);
  sequence[0] = 1;
  
}

int * Sequence_make(int size)
{
  int n = 0; 
  int array_size; // size of the sequence
  int * array; // the sequence
  int i;

  //DETERMINE SIZE OF SEQUENCE
  while (pow(3,n) < size)
    {
      n += 1;
    }
  n = n - 1;
  array_size = ((n+1)*(n+2))/2;
  printf("size = %d\n", array_size);
  //CREATE SEQUENCE
  array = malloc(sizeof(int) * array_size);

  int k = 3;
  int j = 1;
  array[0] = 1; //BASE VALUES
  array[1] = 2;
  array[2] = 3;

  //GENERATE THE REMAINING VALUES
  for (i = 0; i < array_size; i ++)
    {
      if (i > 1)
	{
	  if (array[i] == pow(3,j))
	    {
	      array[i + k] = array[i] * 3;
	      k += 1;
	      j++;
	    }
	  else
	    {
	      array[i] = array[i - k + 2] * 2;
	    }
	}
    }
  
  //PRINT OUT THE MOTHERFUCKING TRIANGLE
  j = 0;
  for (i = 0; i < array_size; i ++)
    {
      printf("%d ", array[i]);
      if (pow(3,j) == array[i])
	{
	  j++;
	  printf("\n");
	}
    }
  printf("\n");
  return array;
}

long power(long base, int power)
{
  int i;
  long sum = base;

  if (power == 0)
    {
      return 1;
    }
  if (power == 1)
    {
      return base;
    }

  for (i = 1; i < power; i ++)
    {
      sum = sum * base;
    }
  return sum;
}
