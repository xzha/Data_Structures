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
  clock_t input_clock_begin;
  clock_t input_clock_end;
  clock_t input_clock;
  
  clock_t output_clock_begin;
  clock_t output_clock_end;
  clock_t output_clock;

  clock_t sort_clock_begin;
  clock_t sort_clock_end;
  clock_t sort_clock;

  //GET INPUT
  input_clock_begin = clock();
  int Size;
  long * Array_toSort;

  Array_toSort = Load_File(argv[2], &Size); //FREE 
  if (Array_toSort == NULL)
    {
      return EXIT_FAILURE;
    }
  input_clock_end = clock();
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
  output_clock_begin = clock();
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
  output_clock_end = clock();

  //CLOCK
  input_clock = (double)(input_clock_end - input_clock_begin)/ CLOCKS_PER_SEC;
  output_clock = (double)(output_clock_end - output_clock_begin)/ CLOCKS_PER_SEC;
  sort_clock = (double)(sort_clock_end - sort_clock_begin)/ CLOCKS_PER_SEC;

  //SCREEN DUMP
  printf("Number of comparisons:  %le\n", N_Comp);
  printf("Number of moves:  %le\n", N_Move);
  printf("I/O time:  %le\n", (double)(input_clock + output_clock));
  printf("Sorting time:  %le\n", (double)sort_clock);



  free(Array_toSort);
  return EXIT_SUCCESS;
}
