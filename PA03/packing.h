#ifndef PACKING_H
#define PACKING_H

typedef struct _node{
    int thisnode;
    int parnode;
    int lcnode;
    int rcnode;
    char cutline;
    double width;
    double height;
    double xcoord;
    double ycoord;
}Node;

//I/O
Node * tree_load(const char * filename, int * blocks, int * nodes); //change const
int tree_save(const char * filename, int blocks, Node * tree);

//PACKING
Node tree_root(Node * tree, int nodes);
void tree_pack_rectangle(Node * tree, Node * root);
void tree_pack_coordinate(Node * tree, Node * root);

//PRINT ORDER
void preorder_print(Node * tree, Node * root);
void inorder_print(Node * tree, Node * root);
void postorder_print(Node * tree, Node * root);
#endif
