#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sorting.h"



int main(int argc, char ** argv)
{
  //VALIDATE INPUT
  if (argc != 5)
    {
      printf("ERROR\n");
      printf("FORMAT: ./proj1 <method> <input> <seq> <output>\n");
      return EXIT_FAILURE;
    }

  //GET INPUT
  int Size;
  long * Array_toSort;

  Array_toSort = Load_File(argv[2], &Size); //FREE 
  if (Array_toSort == NULL)
    {
      return EXIT_FAILURE;
    }

  //CHECK METHOD
  char * method = argv[1];
  double N_Comp = 0;
  double N_Move = 0;

  if (method[0] == 'i')
    {
      printf("INSERTION SORT\n");
      Shell_Insertion_Sort(Array_toSort, Size, &N_Comp, &N_Move);
    }
  else if (method[0] == 's')
    {
      printf("SELECTION SORT\n");
    }
  else
    {
      printf("INVALID SORING METHOD\n");
      return EXIT_FAILURE;
    }


  return EXIT_SUCCESS;
}
