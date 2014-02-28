#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

Node * Node_create(long value)
{
  Node * head = malloc(sizeof(Node));
  head -> value = value;
  head -> next = NULL;
 
  return head;
}

List * List_create(int gap)
{
  List * list = malloc(sizeof(List));
  list -> node = NULL;
  list -> next = NULL;
  
  List * current = list;

  while (gap > 1)
    {
      current -> next = malloc(sizeof(List));
      current -> node = NULL;
      current = current -> next; 
      gap--;
    }

  current -> node = NULL;
  current -> next = NULL;
  return list;
}

void List_destroy(List * list)
{
  List * temp = list;
  
  while (list != NULL)
    {
      temp = list -> next;
      free(list);
      list = temp;
    }
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
  //GATHER SIZE
  int size = fulllist -> value;

  //MANAGE HEAD
  Node * head = fulllist->next;
  free(fulllist);

  //SEQUENCE
  int k = 1;
  int p = 0;
  int gap;
  int count;
  
  //SHELL SORT VARIABLES
  Node * node = head;
  List * lhead = NULL;
  int choice = 0;

  //INITIALIZE GAP
  while (k < size)
    {
      k *= 3;
      p += 1;
    }

  k /= 3;
  p -= 1;

  while (p >= 0)
    {
      gap = k;
      count = p;

      do
	{
	  //SHELL SORT
	  lhead  = List_create(gap);
	  if (gap == 729) //manual reset: end in ascending order
	    {
	      choice = 1;
	    }
	  lhead  = List_fill(node,lhead, &choice); //dummy list
	  node   = Node_reconstruct(node, lhead); 
	  List_destroy(lhead);
      	  gap = (gap / 3) * 2;
	  count--;
	}while(count >= 0);
      k /= 3;
      p -= 1;
    }
  
  //MEASURE FOR SIZE < 729
  if (node -> value > node -> next -> value)
    {
      node = Node_reverse(node);
    }

  return node;
}

Node * Node_reconstruct(Node * head, List * list)
{
  List * lhead = list;
  head = lhead -> node;
  Node * current = head;

  lhead -> node = lhead -> node -> next;
  lhead = lhead -> next;

  if (lhead == NULL)
    {
      lhead = list;
    }

  while (lhead -> node != NULL)
    {
      current -> next  = lhead -> node;
      lhead -> node = lhead -> node -> next;
      current = current -> next;
      lhead = lhead -> next;
      if (lhead == NULL)
	{
	  lhead = list;
	}
    }
  current -> next = NULL;
  
  return head; 

}

Node * Node_reverse(Node * head)
{
  Node * back = NULL;
  Node * current = head;
  Node * front;
  
  while (current != NULL)
    {
      front = current -> next;
      current -> next = back;
      back = current;
      current = front;
    }
  head = back;
  return head;
}


List * List_fill(Node * node, List * list, int * count)
{
  List * lhead = list; 
  Node * head = node;
  Node * insert = NULL;

  while (head != NULL)
    {
      insert = head;
      head = head-> next;

      if ((*count) % 2 == 0)
	{
	  lhead -> node = List_insertion_up(lhead->node, insert);
	}
      else
	{
	  lhead -> node = List_insertion_down(lhead->node, insert);
	}

      lhead = lhead -> next; 
      if (lhead == NULL)
	{
	  lhead = list;
	}
    }

  (*count)++;
  return list;
}

Node * List_insertion_up(Node * head, Node * insert)
{
  Node * front = head;
  Node * back = head;

  if (head == NULL)
    {
      insert -> next = NULL;
      return insert;
    }
  while (front != NULL && insert->value > front -> value)
    {
      back = front;
      front = front -> next;
    }
  if(front == head)
    {
      insert -> next = head;
      return insert;
    }
  else if (front == NULL)
    {
      back -> next = insert;
      insert -> next = NULL;
    }
  else
    {
      back->next = insert;
      insert -> next = front;
    }

  return head; 
}

Node * List_insertion_down(Node * head, Node * insert)
{
  Node * front = head;
  Node * back = head;

  if (head == NULL)
    {
      insert -> next = NULL;
      return insert;
    }
  while (front != NULL && insert->value < front -> value)
    {
      back = front;
      front = front -> next;
    }
  if(front == head)
    {
      insert -> next = head;
      return insert;
    }
  else if (front == NULL)
    {
      back -> next = insert;
      insert -> next = NULL;
    }
  else
    {
      back->next = insert;
      insert -> next = front;
    }

  return head; 
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
