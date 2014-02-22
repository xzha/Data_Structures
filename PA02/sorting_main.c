#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

int main (int argc, char ** argv)
{
  //VALIDATE INPUT
  if (argc != 3)
    {
      printf("ERROR\n");
      printf("FORMAT: ./proj2 <input> <output>\n");
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
  Node * head = NULL;
  Node * fulllist = NULL;
  fulllist = Load_File(argv[1]);
  if (fulllist == NULL)
    {
      printf("ERROR LOADING INTO LINKED LIST\n");
      return EXIT_FAILURE;
    }
  input_clock_end = clock();

  //DEFINE HEAD OF LIST
  head = fulllist -> next;

  //SORT
  sort_clock_begin = clock();
  fulllist = Shell_Sort(fulllist);
  sort_clock_end = clock();

  //SAVE FILE
  output_clock_begin = clock();
  int save_node = 0;
  save_node = Save_File(argv[2], head);
  if (save_node == 0)
    {
      printf("ERROR SAVING\n");
      //FREE
      return EXIT_FAILURE;
    }
  output_clock_end = clock();

  
  //CLOCK
  input_clock = (double)(input_clock_end - input_clock_begin)/ CLOCKS_PER_SEC;
  output_clock = (double)(output_clock_end - output_clock_begin)/ CLOCKS_PER_SEC;
  sort_clock = (double)(sort_clock_end - sort_clock_begin)/ CLOCKS_PER_SEC;

  //SCREEN DUMP
  printf("I/O time:  %le\n", (double)(input_clock + output_clock));
  printf("Sorting time:  %le\n", (double)sort_clock);

  Node_clear(fulllist);
  return EXIT_SUCCESS;
}
