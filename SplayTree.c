//
// Created by Surbhi on 05-04-2020.
//top-down splaying
//
#include <stdio.h>
#include <stdlib.h>

typedef struct treeTag{
    int data;
    struct treeTag *left,*right;
}treeNode;

typedef enum {Success,Failure}statuscode;

treeNode *current=NULL,*child=NULL,*lastSmall=NULL,*firstLarge=NULL,*dummy=NULL;

void inorder(treeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("Node: %d\n", root->data);
        inorder(root->right);
    }
}

void printTree(treeNode *root)
{
    printf("-------------------------------\n");
    if (root != NULL)
    {
        inorder(root);
    }
    else
    {
        printf("Empty Tree\n");
    }
    printf("-------------------------------\n");
}

treeNode *createNode(int key)
{
    treeNode *node = (treeNode *)malloc(sizeof(treeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void initialize()
{
    current= child= lastSmall= firstLarge=dummy=NULL;
    firstLarge=lastSmall=dummy=createNode(0);
}

void  linkRight()
{
    if(current!=NULL)
    {
        firstLarge->left=current;
        firstLarge=current;
        current=current->left;
    }
}

void linkLeft()
{
    if(current!=NULL)
    {
        lastSmall->right=current;
        lastSmall=current;
        current=current->right;
    }
}

void rotateRight()
{
    treeNode *leftTree=current->left;
    current->left=leftTree->right;
    leftTree->right=current;
    current=leftTree;
}

void rotateLeft()
{
    treeNode* rightTree=current->right;
    current->right=rightTree->left;
    rightTree->left=current;
    current=rightTree;
}

statuscode splay(int key, treeNode** root)
{
    initialize();
    statuscode sc=Failure;
    current=*root;

    while(current!=NULL && current->data!=key)
    {
        if(key< current->data)
        {
            child=current->left;
            if(child==NULL || key==child->data){ //zig move
                linkRight();
            } else if(key<child->data){           //zig-zig move
                rotateRight();
                linkRight();
            } else{                             //zig-zag move
                linkRight();
                linkLeft();
            }
        } else{

            child=current->right;
            if(child==NULL || child->data==key){ //zag move
                linkLeft();
            } else if (key>child->data){        //zag-zag move
                rotateLeft();
                linkLeft();
            } else{                             //zag-zig move
                linkLeft();
                linkRight();
            }
        }
    }

    if (current==NULL){
            *root=createNode(key);
            lastSmall->right=firstLarge->left=NULL;
    } else{
        sc=Success;
        (*root)=current;
        lastSmall->right=current->left;
        firstLarge->left=current->right;
    }

    (*root)->left=dummy->right;
    (*root)->right=dummy->left;

    free(dummy);
    return sc;

}

void main(){

    treeNode *root=NULL;
    statuscode sc;
    sc=splay(5,&root);
    //printTree(root);
    sc=splay(10,&root);
    //printTree(root);
    sc=splay(1,&root);
    //printTree(root);
    sc=splay(11,&root);
    //printTree(root);
   sc=splay(2,&root);
    //printTree(root);
    sc=splay(3,&root);
    //printTree(root);
    sc=splay(5,&root);
    printTree(root);
    //printf("%d\n",root->left->data);
}




