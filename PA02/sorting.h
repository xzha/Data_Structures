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
#endif
