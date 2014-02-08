#include <stdio.h>
#include <stdlib.h>
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
      printf("INVALID INPUT FILE!\n");
      return NULL;
    }

  //READ FIRST LINE
  g = fscanf(fh, "%d", Size);
  if (g != 1)
    {
      printf("ERROR1\n");
      fclose(fh);
      return NULL;
    }

  //STORE THE ARRAY
  Array_toSort = malloc(sizeof(long) * (*Size));
  if (Array_toSort == NULL)
    {
      printf("MALLOC FAILED\n");
      fclose(fh);
      return NULL;
    }

  while (!feof(fh))
    {
      g = fscanf(fh, "%ld", &Array_toSort[i]);
      i++;
    }
  if (g > 0)
    {
      printf("ERROR2\n");
      free(Array_toSort);
      fclose(fh);
      return NULL;
    }

  fclose(fh);
  return Array_toSort;
}

void Shell_Insertion_Sort(long * array, int size, double *N_comp, double *N_Move)
{
  int sequence_size;
  int * sequence = Sequence_make(size, &sequence_size);
  if (sequence == NULL)
    {
      return;
    }
  int i;
  int j;
  int k;
  int temp_value;
  
  for (i = sequence_size - 1; i >= 0 ; i --)
    {
      for (j = sequence[i]; j < size; j ++)
	{
	  temp_value = array[j];
	  k = j;
	  while (k >= sequence[i] && array[k-sequence[i]] > temp_value)
	    {
	      array[k] = array[k - sequence[i]];
	      k = k - sequence[i];
	      (*N_comp)++;
	    }
	  array[k] = temp_value;
	  (*N_Move)++;
	}
    }
  free(sequence);
}

void Shell_Selection_Sort(long * array, int size, double *N_comp, double *N_Move)
{
  int sequence_size;
  int * sequence = Sequence_make(size, &sequence_size);
  if (sequence == NULL)
    {
      return;
    }

  int i;
  int j;
  int k;
  int min;
  int temp;

  for (i = sequence_size - 1; i >= 0; i--)
    {
      for (j = 0; j < size; j++)
	{
	  min = j;
	  for (k = j + sequence[i]; k < size; k+= sequence[i])
	    {
	      if (array[k] < array[min])
		{
		  (*N_comp)++;
		  min = k;
		}
	    }
	  if (min != j)
	    {
	      (*N_Move)++;
	      temp = array[j];
	      array[j] = array[min];
	      array[min] = temp;
	    }
	}
    }
  free(sequence);
}

int * Sequence_make(int size, int * sequence_size)
{
  int n = 0; 
  int array_size; // size of the sequence
  int * array; // the sequence
  int i;

  //DETERMINE SIZE OF SEQUENCE
  while (power(3,n) < size)
    {
      n += 1;
    }
  n = n - 1;
  array_size = ((n+1)*(n+2))/2;
  *sequence_size = array_size;

  //CREATE SEQUENCE
  array = malloc(sizeof(int) * array_size);
  if (array == NULL)
    {
      printf("MALLOC FAILED\n");
      return NULL;
    }

  int k = 3;
  int j = 1;
  array[0] = 1; //BASE VALUES
  array[1] = 2;
  array[2] = 3;

  //GENERATE THE REMAINING VALUES

  //INITIALIZE ARRAY
  for (i = 3; i < array_size; i ++)
    {
      array[i] = 0;
    }

  //FILL IN ARRAY
  for (i = 2; i < array_size; i ++)
    {
      if (array[i] == power(3,j))
	{
	  if ((i+k) < array_size)
	    {
	      array[i + k] = array[i] * 3;
	    }
	  k += 1;
	  j++;
	}
      else
	{
	  array[i] = array[i - k + 2] * 2;
	}
    }

  return array;
}

long power(long base, int power)
{
  int i;
  long sum = base;

  //BASE CASES
  if (power == 0)
    {
      return 1;
    }
  if (power == 1)
    {
      return base;
    }

  //POWER
  for (i = 1; i < power; i ++)
    {
      sum = sum * base;
    }
  return sum;
}

int Save_File (char * filename, long * array, int size)
{
  FILE * fh;
  int i;
  
  //CHECK FILE STATUS
  fh = fopen(filename, "w");
  if (fh == NULL)
    {
      printf("ERROR\n");
      return 0;
    }
  
  //PRINT TO FILE
  fprintf(fh, "%d\n", size);
  for (i = 0; i < size; i ++)
    {
      fprintf(fh, "%ld\n", array[i]);
    }

  fclose(fh);
  return 1;
}

int Print_Seq (char * filename, int size)
{
  FILE * fh;
  int i;

  //CHECK FILE STATUS
  fh = fopen(filename, "w");
  if (fh == NULL)
    {
      printf("ERROR\n");
      return 0;
    }
  
  //GENERATE SEQUENCE
  int sequence_size;
  int * sequence = Sequence_make(size, &sequence_size);

  //PRINT TO FILE
  fprintf(fh, "%d\n", sequence_size);
  for (i = 0; i < sequence_size; i++)
    {
      fprintf(fh, "%d\n", sequence[i]);
    }

  free(sequence);
  fclose(fh);
  return 1;
}
