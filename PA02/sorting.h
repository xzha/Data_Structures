#ifndef SORTING_H
#define SORTING_H

typedef struct _node{
  long value;
  struct _node * next;
}Node;

typedef struct _list{
  Node * node;
  struct _list * next;
}List;

Node * Load_File(char * Filename);
int Save_File(char * Filename, Node * list);
Node * Shell_Sort(Node * list);
Node * Node_create(long value);
void Node_clear(Node * head);
List * List_create(int gap);
List * List_fill(Node * head, List * list, int * count);
Node * List_insertion_up(Node * head, Node * insert);
Node * List_insertion_down(Node * head, Node * insert);
Node * Node_reconstruct(Node * head, List * list);
Node * Node_reverse(Node * head);
void List_destroy(List * list);


//MYMALLOC
typedef struct _Array_list
{
  Node * node_array;
  struct _Array_list * next;
}Array_list;

typedef struct _List_list
{
  List * list_array;
  struct _List_list * next;
}List_list;

Node * Node_mymalloc();
void Node_myfree(Node * node);
void Node_list_destroy(Array_list * list);

List * List_mymalloc();
void List_myfree(List * list);
void List_list_destroy(List_list * list);
void destroyall();

#endif
