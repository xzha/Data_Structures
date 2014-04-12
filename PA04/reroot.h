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

typedef struct _size{
    double width;
    double height;
}Size;

//I/O
Node * tree_load(const char * filename, int * blocks, int * nodes); //change const*********
int tree_save(const char * filename, Node * root, Node * tree);

//PACKING
Node *  tree_pack_rectangle(Node * tree, int root);
void tree_pack_coordinate(Node * tree, Node * root);

//PRINT ORDER
void preorder_print(Node * tree, Node * root);
void inorder_print(Node * tree, Node * root);
void postorder_print(Node * tree, Node * root);

//TEMP
Node * tree_build(Node * tree, int blocks);
void tree_pack_rectangle_light(Node * tree, Node * root);
void reroot(Node * tree, int root, int rootchild, Size heightwidth, Size * area);
void min_rectangle(Size * area, double width, double height);
Size reroot_help(Size constant, char cutline, double width, double height);
void postorder_save(Node * tree, Node * root, FILE * fh);
#endif
