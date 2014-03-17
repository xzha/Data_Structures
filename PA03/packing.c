#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "packing.h"

int main(int argc, const char * argv[])
{
    //VALIDATE INPUT
    if (argc != 3)
    {
        printf("ERROR\n");
        printf("FORMAT: ./proj3 <input> <output>\n");
        return EXIT_FAILURE;
    }
    
    //GET INPUT
    Node * tree = NULL;
    int blocks = 0;
    int nodes = 0;
    tree = tree_load(argv[1], &blocks, &nodes);
    if (tree == NULL)
      {
	return EXIT_FAILURE;
      }

    //GET ROOT
    Node root;
    root = tree_root(tree, nodes);
    
    //INITIALIZE CLOCK
    clock_t pack_clock_begin;
    clock_t pack_clock_end;
    double pack_clock;

    //PACK
    pack_clock_begin = clock();
    tree_pack_rectangle(tree, &root);
    
    //COORDINATES
    root.xcoord = 0; //Start from big rectangle
    root.ycoord = 0;
    tree_pack_coordinate(tree, &root);
    
    pack_clock_end = clock();
    pack_clock = (double)(pack_clock_end - pack_clock_begin)/ CLOCKS_PER_SEC;
    
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
    printf("\nWidth: %le\n", root.width);
    printf("Height: %le\n", root.height);
    printf("\nX-coordinate: %le\n",tree[blocks].xcoord);
    printf("Y-coordinate: %le\n",tree[blocks].ycoord);
    printf("\nElapsed Time: %le\n", pack_clock);
    
    //SAVE FILE
    int save_file;
    save_file = tree_save(argv[2], blocks, tree);
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

//OUTPUT
int tree_save(const char * filename, int blocks, Node * tree)
{
    FILE * fh;
    
    int i = 1;
    
    fh = fopen(filename, "w");
    if (fh == NULL)
    {
        printf("ERROR\n");
        printf("INVALID OUTPUT FILE\n");
        return 0;
    }
    
    fprintf(fh, "%d\n",blocks);
    for (i = 1; i <= blocks; i++)
    {
        fprintf(fh,"%d %le %le %le %le\n", 
		i, tree[i].width, tree[i].height, 
		tree[i].xcoord, tree[i].ycoord);
    }
    
    fclose(fh);
    return i;
}

//POSTORDER
void postorder_print(Node * tree, Node * root)
{
    if(root->rcnode == -1 && root->lcnode == -1)
    {
        printf("%d ", root->thisnode);
        return;
    }
    postorder_print(tree, &tree[root->lcnode]);
    postorder_print(tree, &tree[root->rcnode]);
    printf("%d ", root->thisnode);
    return;
}

//INORDER
//REMOVED TAIL RECURSION
void inorder_print(Node * tree, Node * root)
{
  while (root->rcnode != -1 && root->lcnode != -1)
    {
      inorder_print(tree, &tree[root->lcnode]);
      printf("%d ", root->thisnode);
      root = &tree[root->rcnode];
    }
  printf("%d ", root->thisnode);
  return;
}

//PREORDER
//REMOVED TAIL RECURSION
void preorder_print(Node * tree, Node * root)
{
  while (root->rcnode != -1 && root->lcnode != -1)
    {
      printf("%d ", root->thisnode);
      preorder_print(tree, &tree[root->lcnode]);
      root = &tree[root->rcnode];
    }
  printf("%d ", root->thisnode);
  return;
}

//RECTANGLE COORDINATES: ASSUMING BIG RECTANGLE IS (0,0)
//THE SMALLER RECTANGLES ARE BASED ON THE BIG RECTANGLE
//PREORDER
//REMOVED TAIL RECURSION
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
void tree_pack_rectangle(Node * tree, Node * root)
{
    if(root->rcnode == -1 && root->lcnode == -1)
    {
        return;
    }
    tree_pack_rectangle(tree, &tree[root->lcnode]);
    tree_pack_rectangle(tree, &tree[root->rcnode]);
    
    //VERTICAL: ADD WIDTH AND FIND MAX HEIGHT
    if (root->cutline == 'V')
    {
        root->width = tree[root->rcnode].width + tree[root->lcnode].width;
        if (tree[root->rcnode].height > tree[root->lcnode].height)
        {
            root->height = tree[root->rcnode].height;
        }
        else
        {
            root->height = tree[root->lcnode].height;
        }
    }
    
    //HORIZONTAL: ADD HEIGHT AND FIND MAX WIDTH
    else if (root->cutline == 'H')
    {
        root->height = tree[root->rcnode].height + tree[root->lcnode].height;
        if (tree[root->rcnode].width > tree[root->lcnode].width)
        {
            root->width = tree[root->rcnode].width;
        }
        else
        {
            root->width = tree[root->lcnode].width;
        }
    }
    return;
}

//FIND ROOT
Node tree_root(Node * tree, int nodes)
{
    int i = nodes;
    Node root;
    
    for (i = nodes; i > 0; i --)
    {
        if(tree[i].parnode == -1)
        {
            root = tree[i];
            break;
        }
    }
    return root;
}

//LOAD FILE
Node * tree_load(const char * filename, int * blocks, int * nodes)
{
    FILE * fh;
    Node * tree = NULL;
    int i = 1;
    int g = 0;
    
    fh = fopen(filename, "r");
    if (fh == NULL)
    {
        printf("ERROR\n");
        printf("INVALID INPUT FILE!\n");
        return NULL;
    }
    
    g = fscanf(fh, "%d", blocks);
    if (g < 0)
      {
	printf("FSCANF ERROR\n");
	fclose(fh);
	return NULL;
      }
    g = fscanf(fh, "%d", nodes);
    if (g < 0)
      {
	printf("FSCANF ERROR\n");
	fclose(fh);
	return NULL;
      }

    tree = malloc(sizeof(Node) * ((*nodes) + 1)); 

    if (tree == NULL)
    {
        printf("MALLOC FAILED\n");
        fclose(fh);
        return NULL;
    }
    
    //IMPORTANT: ONE BASED ARRAY OF NODES
    while (!feof(fh) && i < (*blocks) + 1)
    {
        g = fscanf(fh,"%d %d %d %d %c %lf %lf", 
		   &tree[i].thisnode, &tree[i].parnode, &tree[i].lcnode, 
		   &tree[i].rcnode, &tree[i].cutline, &tree[i].width, 
		   &tree[i].height);
        i++;
    }

    if (g < 0)
      {
	printf("FSCANF ERROR\n");
	free(tree);
	fclose(fh);
	return NULL;
      }

    while (!feof(fh) && i < (*nodes) + 1)
    {
        g = fscanf(fh,"%d %d %d %d %c %*c %*c", 
		   &tree[i].thisnode, &tree[i].parnode, &tree[i].lcnode, 
		   &tree[i].rcnode, &tree[i].cutline);
        tree[i].width = 0;
        tree[i].height = 0;
        i++;
    }

    if (g < 0)
      {
	printf("FSCANF ERROR\n");
	free(tree);
	fclose(fh);
	return NULL;
      }

    fclose(fh);
    return tree;
}
