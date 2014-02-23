#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <unistd.h>

Node * Node_create(long value)
{
  Node * head = malloc(sizeof(Node));
  head -> value = value;
  head -> next = NULL;
 
  return head;
}

void Node_clear(Node * head)
{
  Node * temp = head;

  while(head != NULL)
    {
      temp = head -> next;
      free(head);
      head = temp;
    }
}

Node * Load_File(char * Filename)
{
  FILE * fh;
  Node * head = NULL;
  Node * current = NULL;
  long value;
  int i = 0;
  int g = 0;

  fh = fopen(Filename, "r");
  if (fh == NULL)
    {
      printf("ERROR\n");
      printf("INVALID INPUT FILE!\n");
      return NULL;
    }
  while (!feof(fh))
    {
      g = fscanf(fh,"%ld\n", &value);
      if (head == NULL)
	{
	  head = Node_create(value);
	  current = head;
	}
      else
	{
	  current -> next = Node_create(value);
	  current = current -> next;
	}
      i++;
    }

  Node * dummy = malloc(sizeof(Node));
  dummy -> value = i;
  dummy -> next = head; 

  if (g < 0)
    {
      printf("FSCANF ERROR\n");
      fclose(fh);
      return NULL;
    }

  fclose(fh);
  return dummy;
}

Node * Shell_Sort(Node * fulllist)
{
  //GENERATE SEQUENCE
  int size = fulllist -> value;
  int sequence_size;
  int * sequence = Sequence_make(size, &sequence_size);
  if (sequence == NULL)
    {
      return NULL;
    }

  //MANAGE HEAD
  Node * head = fulllist->next;
  free(fulllist);
  
  //SORT
  Node * front = head -> next;
  Node * back = head;
  Node * current = head;
  Node * backcurrent = head;
  int i;
  int k;

  for (i = sequence_size; i >= 0; i--)
    {
      while(front != NULL)
	{
	  backcurrent = head;
	  current = head;
	  k = 0;
	  
	  while (current->value < front->value && k < sequence[i])
	    {
	      backcurrent = current;
	      current = current->next;
	      k++;
	    }
	  if(current != front)
	    {
	      back->next = front->next;
	      if(current==head)
		{
		  front->next = head;
		  head = front;
		}
	      else
		{
		  backcurrent->next =front;
		  front->next = current;
		}
	      front=back->next;
	    }
	  else
	    {
	      back = back->next;
	      front=front->next;
	    }
	}
    }
  free(sequence);
  return head;
}

int * Sequence_make(int size, int * sequence_size)
{
  int n = 0; 
  int array_size; // size of the sequence
  int * array; // the sequence

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

  //FILL IN SEQUENCE
  int i; //position
  int p = 0; //2
  int q = 0; //3
  int pp; //increment
  int qq; //decrement
  
  for (i = 0; i < array_size; i ++)
    {
      pp = p;
      qq = 0;
      while (pp >= 0 && qq <= q)
	{
	  array[i] = power(2,pp) * power(3,qq);
	  i++;
	  pp--;
	  qq++;
	}
      i--;
      p++;
      q++;
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


int Save_File(char * Filename, Node * head)
{
  FILE * fh;
  Node * temp = NULL;
  int i = 0;

  fh = fopen(Filename, "w");
  if(fh == NULL)
    {
      printf("ERROR\n");
      return 0;
    }

  temp = head;

  while (temp != NULL)
    {
      fprintf(fh, "%ld\n", temp->value);
      temp = temp->next;
      i++;
    }
  fclose(fh);
  return i;
} 
