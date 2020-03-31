//write a recursive function to traverse a binary tree level wise
#include <stdio.h>
#include <stdlib.h>
#define datatype int
typedef enum
{
    FAILURE,
    SUCCESS
} statuscode;
typedef struct TNode
{
    datatype data;
    struct TNode *left;
    struct TNode *right;
} TreeNode;

typedef struct Queue
{
    TreeNode *tree_node;
    struct Queue *next;
} Queue;

statuscode insert(datatype d, TreeNode **root)
{
    statuscode sc = SUCCESS;
    TreeNode *p = *root;
    TreeNode *prev = NULL;
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
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

    return sc;
}

void inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d\n", root->data);
        inorder(root->right);
    }
}

void preorder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d\n", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d\n", root->data);
    }
}

void enqueue(Queue **start, Queue **end, Queue *node)
{
    if ((*start) == NULL)
    {
        (*start) = (*end) = node;
    }

    else
    {
        node->next = (*start);
        (*start) = node;
    }
}

void dequeue(Queue **start, Queue **end)
{
    if ((*start) == (*end))
    {
        free(*start);
        (*start) = (*end) = NULL;
    }

    else
    {
        Queue *ptr = *start;
        while (ptr->next != (*end))
        {
            ptr = ptr->next;
        }
        ptr->next = NULL;
        free(*end);
        (*end) = ptr;
    }
}

void printElement(Queue *ptr)
{
    printf("%d\n", ptr->tree_node->data);
}

void LevelPrint(Queue *start, Queue *end)
{
    if (start != NULL && end != NULL)
    {
        printElement(end);
        if (end->tree_node->left != NULL)
        {
            Queue *node1 = (Queue *)malloc(sizeof(Queue));
            node1->tree_node = end->tree_node->left;
            node1->next = NULL;
            enqueue(&start, &end, node1);
        }

        if (end->tree_node->right != NULL)
        {
            Queue *node2 = (Queue *)malloc(sizeof(Queue));
            node2->tree_node = end->tree_node->right;
            node2->next = NULL;
            enqueue(&start, &end, node2);
        }
        dequeue(&start, &end);
        LevelPrint(start, end);
    }
}

int main()
{
    TreeNode *root = NULL;
    root = NULL;
    statuscode sc;
    sc = insert(10, &root);
    sc = insert(20, &root);
    sc = insert(5, &root);
    sc = insert(11, &root);
    sc = insert(21, &root);
    sc = insert(1, &root);
    sc = insert(7, &root);
    sc = insert(30, &root);
    //inorder(root);
    Queue *que = NULL;
    Queue *node = (Queue *)malloc(sizeof(Queue));
    node->tree_node = root;
    node->next = NULL;
    enqueue(&que, &que, node);
    LevelPrint(que, que);
    return 0;
}
