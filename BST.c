#include <stdio.h>
#include <stdlib.h>

typedef struct TNode
{
    int data;
    struct TNode *left;
    struct TNode *right;

} treeNode;

void insert(int d, treeNode **root)
{
    treeNode *p = *root;
    treeNode *prev = NULL;
    treeNode *node = (treeNode *)malloc(sizeof(treeNode));
    node->data = d;
    node->left = NULL;
    node->right = NULL;

    if (*root == NULL)
        *root = node;

    else
    {
        while (p != NULL)
        {
            prev = p;
            if (p->data > d)
                p = p->left;
            else if (p->data < d)
                p = p->right;
        }

        if (d < prev->data)
            prev->left = node;
        else
            prev->right = node;
    }
}

void search(treeNode *root, int key)
{

    int flag = 0;

    while (flag == 0 && root != NULL)
    {
        if (root->data == key)
        {
            flag = 1;
        }

        else if (root->data < key)
        {
            root = root->right;
        }

        else
        {
            root = root->left;
        }
    }

    if (flag == 1)
    {
        printf("The required element exists in the Tree\n");
    }

    else
    {
        printf("The required element does not exist in the Tree.\n");
    }
}

void deleteNode(treeNode **p)
{
    treeNode *ptr = (*p);
    treeNode *del=(*p);
    if (ptr->left == NULL)
    {
        *p = ptr->right;
    }

    else
    {
        treeNode *tmp = ptr->right;
        *p=ptr = ptr->left;
        while (ptr->right != NULL)
        {
            ptr = ptr->right;
        }

        ptr->right = tmp;
    }

    free(del);
    
}

void delete (treeNode **root, int key)
{
    int done = 0;
    treeNode *p = *root, *prev = NULL;
    if ((*root)->data == key)
    {
        done = 1;
    }

    else
    {
        while (done==0)
        {
            if (p->data > key)
            {
                prev = p;
                p = p->left;
            }
            else if (p->data < key)
            {
                prev = p;
                p = p->right;
            }
            else
            {
                done = 1;
            }
        }
    }

    if (prev==NULL)
    {
         deleteNode(root);
    }
    

    else if (prev->left->data==key)
    {
       deleteNode(&(prev->left));
    }

    else
    {
        deleteNode(&(prev->right));
    }
    
}

void inorder(treeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d\n", root->data);
        inorder(root->right);
    }
}

int main() {

    treeNode *root=NULL;
    insert(10, &root);
    insert(20, &root);
    insert(5, &root);
    //inorder(root);
    //search(root,5);
    delete(&root,10);
    inorder(root);
    return 0;
}