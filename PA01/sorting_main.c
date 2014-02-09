#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

  //INITIALIZE CLOCK
  clock_t total_clock_begin;
  clock_t total_clock_end;
  clock_t total_clock;

  clock_t sort_clock_begin;
  clock_t sort_clock_end;
  clock_t sort_clock;

  //GET INPUT
  total_clock_begin = clock();
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
      sort_clock_begin = clock();
      Shell_Insertion_Sort(Array_toSort, Size, &N_Comp, &N_Move);
      sort_clock_end = clock();
    }
  else if (method[0] == 's')
    {
      sort_clock_begin = clock();
      Shell_Selection_Sort(Array_toSort, Size, &N_Comp, &N_Move);
      sort_clock_end = clock();
    }
  else
    {
      printf("INVALID SORING METHOD\n");
      free(Array_toSort);
      return EXIT_FAILURE;
    }

  //SAVE FILE
  int save_array = 0; 
  save_array = Save_File(argv[4], Array_toSort, Size);
  if (save_array == 0)
    {
      printf("ERROR SAVING\n");
      free(Array_toSort);
      return EXIT_FAILURE;
    }
  
  int save_seq = 0;
  save_seq = Print_Seq(argv[3], Size);
  if (save_seq == 0)
    {
      printf("ERROR SAVING\n");
      free(Array_toSort);
      return EXIT_FAILURE;
    }
  total_clock_end = clock();

  //CLOCK
  total_clock = (double)(total_clock_end - total_clock_begin)/ CLOCKS_PER_SEC;
  sort_clock = (double)(sort_clock_end - sort_clock_begin)/ CLOCKS_PER_SEC;

  //SCREEN DUMP
  printf("Number of comparisons:  %le\n", N_Comp);
  printf("Number of moves:  %le\n", N_Move);
  printf("I/O time:  %le\n", (double)total_clock);
  printf("Sorting time:  %le\n", (double)sort_clock);



  free(Array_toSort);
  return EXIT_SUCCESS;
}
