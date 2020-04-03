#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    RED,
    BLACK
} COLOUR;

typedef struct nodeTag
{
    int data;
    struct nodeTag *left, *right, *parent;
    COLOUR colour;
} TreeNode;

void inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("Node: %d ", root->data);
        if (root->colour == 0)
            printf("RED\n");
        else
            printf("BLACK\n");
        inorder(root->right);
    }
}

void printTree(TreeNode *root)
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

TreeNode* fixParents(TreeNode* root)
{
    if(root->left!=NULL)
    {
        root->left->parent=root;
        root->left=fixParents(root->left);
        
    }
    if(root->right!=NULL)
    {
        root->right->parent=root;
        root->right=fixParents(root->right);
    }
    
    return root;
}

void rotateLeft(TreeNode **s, TreeNode* node)
{
    TreeNode* parent=*s;
    TreeNode* p=NULL;
    if(parent->left==node)
    p=parent->left;
    else
    p=parent->right;
    TreeNode *q = p;
    if (p != NULL && p->right != NULL)
    {
        q = p->right;
        p->right = q->left;
        q->left = p;
        if(parent!=NULL)
        {
            if(parent->left==p)
            parent->left=q;
            else
            parent->right=q;
        }
    }
    
    *s=parent;
   *s=fixParents(*s);
    
}

void rotateRight(TreeNode **s, TreeNode* node)
{
    TreeNode* parent=*s;
    TreeNode* p=NULL;
    if(parent->left==node)
    p=parent->left;
    else
    p=parent->right;
    TreeNode *q = p;
    if (p != NULL && p->left != NULL)
    {
        q = p->left;
        p->left = q->right;
        q->right = p;
        if(parent!=NULL)
        {
            if(parent->left==p)
            parent->left=q;
            else
            parent->right=q;
        }
    }

    *s=parent;
    *s=fixParents(*s);
}

TreeNode *createNode(int key, TreeNode *parent, COLOUR colour)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->colour = colour;

    return node;
}

TreeNode *BSTInsert(TreeNode *root, int key, TreeNode **insertedNode)
{
    if (root == NULL)
    {
        root = createNode(key, root, RED);
        *insertedNode = root;
    }

    else
    {
        TreeNode *node;
        if (key < root->data)
        {
            root->left = BSTInsert(root->left, key, insertedNode);
            node = root->left;
        }
        else
        {
            root->right = BSTInsert(root->right, key, insertedNode);
            node = root->right;
        }

        if (node->left == NULL && node->right == NULL)
        {
            node->parent = root;
        }
    }

    return root;
}

void swapColours(TreeNode **node1, TreeNode **node2)
{
    COLOUR temp = (*node1)->colour;
    (*node1)->colour = (*node2)->colour;
    (*node2)->colour = temp;
}

TreeNode *searchValue(TreeNode *root, int key)
{
    TreeNode *node = NULL;
    if (root->data == key)
        node = root;
    else if (key < root->data)
        node = searchValue(root->left, key);
    else
        node = searchValue(root->right, key);

    return node;
}

void *fixViolation(TreeNode **root)
{
    TreeNode *ret_val;
    TreeNode *parent = (*root)->parent;
    if (parent == NULL)
    {
       (*root)->colour = BLACK;
    }

    else if (parent->colour == RED)
    {
        TreeNode *grandparent = parent->parent;//(*root)->parent->parent
        TreeNode *sibling = NULL;
        TreeNode* temp=grandparent->parent;//(*root)->parent->parent->parent
        if (grandparent->left == parent)
        {
            
            sibling = grandparent->right;//(*root)->parent->parent->right
            if (sibling == NULL || sibling->colour == BLACK)
            {
                if (parent->left == *root)
                {
                    swapColours(&((*root)->parent->parent), &((*root)->parent));
                    rotateRight(&((*root)->parent->parent->parent),(*root)->parent->parent);
                }

                else
                {
                    rotateLeft(&((*root)->parent->parent),((*root)->parent));
                    swapColours(&((*root)->parent->parent), &((*root)->parent));
                    rotateRight(&((*root)->parent->parent->parent),(*root)->parent->parent);
                }
            }

            else
            {
                (*root)->parent->parent->right->colour= BLACK;
                (*root)->parent->colour = BLACK;
                (*root)->parent->parent->colour = RED;
                if (grandparent->parent == NULL)
                    fixViolation(&(*root)->parent->parent);
                else 
                    fixViolation(root);
            }
        }

        else
        {
            sibling = grandparent->left;//(*root)->parent->parent->left

            if (sibling == NULL || sibling->colour == BLACK)
            {
                if (parent->right == *root)
                {
                    swapColours(&((*root)->parent->parent), &((*root)->parent));
                    rotateLeft(&((*root)->parent->parent->parent),(*root)->parent->parent);
                }

                else
                {
                    rotateRight(&((*root)->parent->parent),(*root)->parent);
                    swapColours(&((*root)->parent->parent), &((*root)->parent));
                    rotateLeft(&((*root)->parent->parent->parent),(*root)->parent->parent);
                }
            }

            else
            {
                (*root)->parent->parent->left->colour = BLACK;
                (*root)->parent->colour = BLACK;
                (*root)->parent->parent->colour = RED;
                if (grandparent->parent == NULL)
                    fixViolation(&(*root)->parent->parent);
                else 
                    fixViolation(root);
            }
        }
    }
}

void insert(TreeNode **root, int key)
{
    TreeNode *newNode = NULL;
    *root = BSTInsert(*root, key, &newNode);
    fixViolation(&newNode);
    *root=fixParents(*root);
}

TreeNode *newNode(TreeNode *node)
{
    TreeNode *child = NULL;

    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    return child;
}

TreeNode *getSibling(TreeNode *parent, TreeNode *node)
{
    TreeNode *sibling = NULL;
    if (parent != NULL)
    {
        if (parent->left == node)
            sibling = parent->right;

        else
            sibling = parent->left;
    }

    return sibling;
}

TreeNode *freeNode(TreeNode *parent, TreeNode *node, TreeNode *child)
{
    if (parent == NULL)
        parent = child;

    else
    {
        if (parent->left == node)
            parent->left = child;

        else
            parent->right = child;

        if (child != NULL)
            child->parent = parent;
    }

    free(node);
    return parent;
}

void fixDoubleBlack(TreeNode **root, TreeNode **p, TreeNode **s)
{
    TreeNode *node = *root;
    TreeNode *parent = *p;
    TreeNode *sibling = *s;
    if (sibling != NULL && sibling->colour == BLACK)
    {
        if (sibling->left != NULL && sibling->left->colour == RED)
            rotateRight(&parent,sibling);

        else if (sibling->right != NULL && sibling->right->colour == RED)
            rotateLeft(&parent,sibling);

        else
        {
            sibling->colour = RED;
            if (parent->colour == RED)
                parent->colour == BLACK;
            else
            {
                TreeNode *temp = getSibling(parent->parent, parent);
                fixDoubleBlack(&parent, &(parent->parent), &temp);
            }
        }

    }

    else if (sibling == NULL)
    {
        if (parent != NULL)
        {
            if (parent->colour == RED)
                parent->colour == BLACK;
            else
            {
                TreeNode *temp = getSibling(parent->parent, parent);
                fixDoubleBlack(&parent, &(parent->parent), &temp);
            }
        }
    }

    else
    {
        if (parent->left == sibling)
        {
            rotateRight(&(parent->parent),parent);
            parent->right->colour = BLACK;
        }

        else
        {
            rotateLeft(&(parent->parent),parent);
            parent->left->colour = BLACK;
        }

        TreeNode *temp = getSibling(parent, node);
        fixDoubleBlack(root, p, &temp);
    }

    *p = parent;
    *s = sibling;
    *root = node;

}

void swapValues(TreeNode **node1, TreeNode **node2)
{
    int val = (*node1)->data;
    (*node1)->data = (*node2)->data;
    (*node2)->data = val;
}

TreeNode *deleteNode(TreeNode **root)
{
    TreeNode *node = *root;
    TreeNode *parent = node->parent;
    TreeNode *child = newNode(node);
    TreeNode *sibling = getSibling(parent, node);
    TreeNode *node_other_child = getSibling(node, child);
    if (node_other_child == NULL)
    {
        int double_black = 0; //=1 when it is double black
        if ((child == NULL || child->colour == BLACK) && node->colour == BLACK)
        {
            if (child == NULL && parent == NULL)
                ;
            else
                double_black = 1;
        }

        parent = freeNode(parent, node, child);
        node = NULL;

        if (double_black == 0)
        {
            if (child != NULL)
                child->colour = BLACK;
        }

        else
        {
           /** printTree(child);
            printTree(parent);
            printTree(sibling);**/
            fixDoubleBlack(&child, &parent, &sibling);
        }
    }

    else
    {
        swapValues(&node, &child);
        node = deleteNode(&child);
        parent = node;
    }

    *root = node;
    return parent;
}

void delete (TreeNode **root, int key)
{
    TreeNode *node = searchValue(*root, key);
    //printTree(node->parent);
    if (node == *root)
        *root = deleteNode(&node);
    else
        node->parent = deleteNode(&node);
}

int main()
{
    TreeNode *root = NULL;
    insert(&root, 3);
    insert(&root, 1);
    insert(&root, 4);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 7);
    printTree(root);
    //printf("%d\n",root->data);
    //printf("%d %d\n",root->left->data,root->right->data);
    delete (&root, 4);
    /**TreeNode* temp=root->right;
    printf("%d\n",temp->data);**/
    printTree(root);
    return 0;
}