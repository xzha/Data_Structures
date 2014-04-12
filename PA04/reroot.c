#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "reroot.h"

int main(int argc, const char * argv[])
{
    //VALIDATE INPUT
    if (argc != 3)
    {
        printf("ERROR\n");
        printf("FORMAT: ./proj4 <input> <output>\n");
        return EXIT_FAILURE;
    }
    
    //GET INPUT
    Node * tree = NULL;
    int blocks = 0; //number of rectangles (leaf)
    int nodes = 0; //number of nodes (leaf + internal)
    tree = tree_load(argv[1], &blocks, &nodes);
    if (tree == NULL)
    {
        return EXIT_FAILURE;
    }

    //MAKE TREE
    tree = tree_build(tree, nodes); //generate tree from postorder print

    //MAKE ROOT
    Node root = tree[nodes]; //root is the last element in array
    root.parnode = -1;
   
    //INITIALIZE CLOCK
    clock_t reroot_clock_begin;
    clock_t reroot_clock_end;
    double reroot_clock;
    clock_t pack_clock_begin;
    clock_t pack_clock_end;
    double pack_clock;

    //PACK
    pack_clock_begin = clock();
    tree = tree_pack_rectangle(tree, nodes);
    
    //COORDINATES
    root.xcoord = 0; //start from big rectangle
    root.ycoord = 0;
    tree_pack_coordinate(tree, &root);
    
    pack_clock_end = clock();
    pack_clock = (double)(pack_clock_end - pack_clock_begin) / CLOCKS_PER_SEC;
    
    //AREA
    Size area = {0,0}; //smallest area
    Size rootsize = {0,0}; //size of the other root child

    //REROOT
    reroot_clock_begin = clock();

    area.width = tree[nodes].width; //assign minimum area
    area.height = tree[nodes].height;
    
    //LEFT-REROOT
    rootsize.height = tree[tree[nodes].rcnode].height; //assign size of the other child
    rootsize.width = tree[tree[nodes].rcnode].width;
    reroot(tree, tree[nodes].thisnode, tree[nodes].lcnode, rootsize, &area); //left of root
    
    //RIGHT-REROOT
    rootsize.height = tree[tree[nodes].lcnode].height; //assign size of the other child
    rootsize.width = tree[tree[nodes].lcnode].width;
    reroot(tree, tree[nodes].thisnode, tree[nodes].rcnode, rootsize, &area); //right of root
  
    reroot_clock_end = clock();
    reroot_clock = (double)(reroot_clock_end - reroot_clock_begin)/ CLOCKS_PER_SEC;
 
    //SCREEN DUMP
    printf("\nPreorder: ");
    preorder_print(tree, &root);
    printf("\n");
    printf("\nInorder: ");
    inorder_print(tree, &root);
    printf("\n");
    printf("\nPostorder: ");
    postorder_print(tree, &root);
    printf("\n");
    printf("\nWidth: %le\n", tree[nodes].width);
    printf("Height: %le\n", tree[nodes].height);
    printf("\nX-coordinate: %le\n",tree[1].xcoord); //first element is the first rectangle
    printf("Y-coordinate: %le\n",tree[1].ycoord);
    printf("\nElapsed Time: %le\n", pack_clock);
    printf("\nBest width: %le\nBest height: %le\n",area.width, area.height);
    printf("\nElapsed time for re-rooting: %le\n\n", reroot_clock);

    //SAVE FILE
    int save_file;
    save_file = tree_save(argv[2], &root, tree);
    if (save_file == 0)
    {
        printf("ERROR SAVING FILE\n");
        free(tree);
        return EXIT_FAILURE;
    }
    
    //FREE
    free(tree);
    return EXIT_SUCCESS;
}

//FIND MINIMUM AREA
void min_rectangle (Size * area, double width, double height)
{
    if ((width*height) < (area->width * area->height))
    {
        area->width = width;
        area->height = height;
    }
    else if ((width*height) == (area->width * area->height))
    {
        if (width < area->width)
        {
            area->width = width;
            area->height = height;
        }
    }
}

//SUM THE CHILD NODE WITH THE ADOPTED ONE BASED ON H/V
Size reroot_help(Size constant, char cutline, double width, double height)
{
    Size newconstant;
    
    //ADD HEIGHT, MAX WIDTH
    if(cutline == 'H')
    {
        newconstant.height = constant.height + height;

        if (constant.width < width)
        {
            newconstant.width = width;
        }
        else
        {
            newconstant.width = constant.width;
        }
    }

    //ADD WIDTH, MAX HEIGHT
    else if (cutline == 'V')
    {
        newconstant.width = constant.width + width;
        
        if (constant.height < height)
        {
            newconstant.height = height;
        }
        else
        {
            newconstant.height = constant.height;
        }
    }
    
    return newconstant;
}

//REROOT
//FIND MINAREA BETWEEN LEFT AND RIGHT EDGE, RECURSE THROUGH TREE
//PRE-ORDER REMOVED TAIL RECURSION
void reroot(Node * tree, int root, int rootchild, Size heightwidth, Size * area)
{
    if(tree[rootchild].cutline == '-')
    {
        return;
    }
   
    Size newrootl;
    Size newrootr;
    Size edge;
    
    while (tree[rootchild].cutline != '-')
    {
        //KEEP LEFT EDGE - PUT RIGHT EDGE UP FOR ADOPTION
        newrootl = reroot_help(heightwidth, tree[root].cutline,tree[tree[rootchild].rcnode].width,tree[tree[rootchild].rcnode].height);
        edge = reroot_help(newrootl, tree[rootchild].cutline, tree[tree[rootchild].lcnode].width, tree[tree[rootchild].lcnode].height);
        min_rectangle(area, edge.width, edge.height);

        //KEEP RIGHT EDGE _ PUT LEFT EDGE UP FOR ADOPTION
        newrootr = reroot_help(heightwidth, tree[root].cutline,tree[tree[rootchild].lcnode].width,tree[tree[rootchild].lcnode].height);
        edge = reroot_help(newrootr, tree[rootchild].cutline, tree[tree[rootchild].rcnode].width, tree[tree[rootchild].rcnode].height);
        min_rectangle(area, edge.width, edge.height);
	
        reroot(tree, tree[rootchild].thisnode, tree[rootchild].lcnode, newrootl, area);
        root = tree[rootchild].thisnode;
        rootchild = tree[rootchild].rcnode;
        heightwidth = newrootr;
    }
}

//OUTPUT
int tree_save(const char * filename, Node * root, Node * tree)
{
    FILE * fh;

    fh = fopen(filename, "w");
    if (fh == NULL)
    {
        printf("ERROR\n");
        printf("INVALID OUTPUT FILE\n");
        return 0;
    }

    postorder_save(tree, root, fh);

    fclose(fh);
    return 1;
}

//SAVE IN POSTORDER FASHION
void postorder_save(Node * tree, Node * root, FILE * fh)
{
  if(root->rcnode == -1 && root->lcnode == -1)
    {
      fprintf(fh, "%le %le %le %le\n", root->width, root ->height, root->xcoord, root->ycoord);
      return;
    }
  postorder_save(tree, &tree[root->lcnode], fh);
  postorder_save(tree, &tree[root->rcnode], fh);
  return;
}

//BUILD TREE USING AN ARRAY AS STACK
Node * tree_build(Node *  tree, int blocks)
{
    int i;
    int j = 1; //STACK EMPTY
    int * stack = malloc(sizeof(int)* (blocks));
    
    for (i = 1; i <= blocks; i ++)
    {
        if(tree[i].cutline == '-')
        {
            //PUSH
            stack[j] = i;
            j++;
        }
        else
        {
            //POP RC
            j--;
            tree[i].rcnode = stack[j];
            tree[stack[j]].parnode = i;
            //POP LC
            j--;
            tree[i].lcnode = stack[j];
            tree[stack[j]].parnode = i;
            
            //PUSH
            stack[j] = i;
            j++;
        }
    }
    
    free(stack);
    return tree;
}

//POSTORDER
void postorder_print(Node * tree, Node * root)
{
    if(root->rcnode == -1 && root->lcnode == -1)
    {
        printf("(%le,%le)", root->width,root->height);
        return;
    }
    postorder_print(tree, &tree[root->lcnode]);
    postorder_print(tree, &tree[root->rcnode]);
    printf("%c", root->cutline);
    return;
}

//INORDER - REMOVED TAIL RECURSION
void inorder_print(Node * tree, Node * root)
{
    while (root->rcnode != -1 && root->lcnode != -1)
    {
        inorder_print(tree, &tree[root->lcnode]);
        printf("%c", root->cutline);
        root = &tree[root->rcnode];
    }
    printf("(%le,%le)", root->width,root->height);
    return;
}

//PREORDER - REMOVED TAIL RECURSION
void preorder_print(Node * tree, Node * root)
{
    while (root->rcnode != -1 && root->lcnode != -1)
    {
        printf("%c", root->cutline);
        preorder_print(tree, &tree[root->lcnode]);
        root = &tree[root->rcnode];
    }
    printf("(%le,%le)", root->width,root->height);
    return;
}

//RECTANGLE COORDINATES: ASSUMING BIG RECTANGLE IS (0,0)
//THE SMALLER RECTANGLES ARE BASED ON THE BIG RECTANGLE
//PREORDER - REMOVED TAIL RECURSION
void tree_pack_coordinate(Node * tree, Node * root)
{
    while(root->rcnode != -1 && root->lcnode != -1)
    {
        if (root -> cutline == 'V')
        {
            //LC IS TO THE LEFT
            tree[root->lcnode].xcoord = root->xcoord;
            tree[root->lcnode].ycoord = root->ycoord;
            //RC IS TO THE RIGHT
            tree[root->rcnode].xcoord = root->xcoord + tree[root->lcnode].width; //ADD WIDTH OF LC
            tree[root->rcnode].ycoord = root->ycoord;
        }
        else if (root-> cutline == 'H')
        {
            //LC IS ABOVE
            tree[root->lcnode].xcoord = root->xcoord;
            tree[root->lcnode].ycoord = root->ycoord + tree[root->rcnode].height; //ADD HEIGHT OF RC
            //RC IS BELOW
            tree[root->rcnode].xcoord = root->xcoord;
            tree[root->rcnode].ycoord = root->ycoord;
        }
        tree_pack_coordinate(tree, &tree[root->lcnode]);
        root = &tree[root->rcnode];
    }
    return;
}

//CONSTRUCT RECTANGLE
//POSTORDER
Node * tree_pack_rectangle(Node * tree, int root)
{
    if(tree[root].rcnode == -1 && tree[root].lcnode == -1)
    {
        return tree;
    }
    tree_pack_rectangle(tree, tree[root].lcnode);
    tree_pack_rectangle(tree, tree[root].rcnode);
    
    //VERTICAL: ADD WIDTH AND FIND MAX HEIGHT
    if (tree[root].cutline == 'V')
    {
        tree[root].width = tree[tree[root].rcnode].width + tree[tree[root].lcnode].width;
        if (tree[tree[root].rcnode].height > tree[tree[root].lcnode].height)
        {
            tree[root].height = tree[tree[root].rcnode].height;
        }
        else
        {
            tree[root].height = tree[tree[root].lcnode].height;
        }
    }
    
    //HORIZONTAL: ADD HEIGHT AND FIND MAX WIDTH
    else if (tree[root].cutline == 'H')
    {
        tree[root].height = tree[tree[root].rcnode].height + tree[tree[root].lcnode].height;
        if (tree[tree[root].rcnode].width > tree[tree[root].lcnode].width)
        {
            tree[root].width = tree[tree[root].rcnode].width;
        }
        else
        {
            tree[root].width = tree[tree[root].lcnode].width;
        }
    }
    return tree;
}

//LOAD FILE
Node * tree_load(const char * filename, int * blocks, int * nodes)
{
    FILE * fh;
    Node * tree = NULL;
    int i = 0;
    double g;
    double j;
    char h;
    
    fh = fopen(filename, "r");
    if (fh == NULL)
    {
        printf("ERROR\n");
        printf("INVALID INPUT FILE!\n");
        return NULL;
    }
    
    //REMEMBER 1 BASED ARRAY
    //READ FIRST FOR SIZE
    while(!feof(fh))
    {
        if (fscanf(fh, "(%lf,%lf)", &g, &j))
        {
            i++;
        }
        else if (fscanf(fh, "%c", &h))
        {
            i++;
        }
    }
    
    *nodes = i - 1;
    i++;
    fseek (fh, 0, SEEK_SET);
    tree = malloc(sizeof(Node) * i);

    i = 1;
    
    //REREAD TO STORE INTO ARRAY
    while(!feof(fh))
    {
        if (fscanf(fh, "(%le,%le)", &tree[i].width, &tree[i].height))
        {
            tree[i].thisnode = i;
            tree[i].cutline = '-';
            tree[i].lcnode = -1;
            tree[i].rcnode = -1;
            i++;
            (*blocks)++;
        }
        else if (fscanf(fh, "%c", &tree[i].cutline))
        {
            tree[i].thisnode = i;
            tree[i].width = 0;
            tree[i].height = 0;
            i++;
        }
    }
    (*blocks)--;
    
    fclose(fh);
    return tree;
}
