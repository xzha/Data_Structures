#ifndef SORTING_H
#define SORTING_H

typedef struct _node{
  long value;
  struct _node * next;
}Node;


/*typedef struct _Array_list{
  Node * node_array;
  struct _Array_list *next;
}Array_list;

Array_list *arr_list = NULL;
Node * unused_list = NULL;
int arr_size;*/

Node * Load_File(char * Filename);
int Save_File(char * Filename, Node * list);
Node * Shell_Sort(Node * list);
int * Sequence_make (int Size, int * Sequence_Size);
Node * Node_create(long value);
Node * Node_insert(Node * head, long value);
void Node_clear(Node * head);
long power(long base, int power);


//Node *Node_mymalloc();
#endif
