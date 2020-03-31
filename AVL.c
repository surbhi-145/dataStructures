#include <stdio.h>
#include <stdlib.h>

typedef struct TNode
{
    int data;
    struct TNode *left;
    struct TNode *right;
    int height;

} TreeNode;

void inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d\n", root->data);
        inorder(root->right);
    }
}

int maxH(int h1, int h2)
{
    int m = h1 > h2 ? h1 : h2;
    return m;
}

int height(TreeNode *node)
{
    int h = 0;
    if (node != NULL)
        h = node->height;

    return h;
}

TreeNode *rotateLeft(TreeNode *p)
{
    TreeNode *q = p;
    if (p != NULL && p->right != NULL)
    {
        q = p->right;
        p->right = q->left;
        q->left = p;

        TreeNode *t = q->left;
        t->height = maxH(height(t->left), height(t->right)) + 1;
        q->height = maxH(height(q->left), height(q->right)) + 1;
    }

    return q;
}

TreeNode *rotateRight(TreeNode *p)
{
    TreeNode *q = p;
    if (p != NULL && p->left != NULL)
    {
        q = p->left;
        p->left = q->right;
        q->right = p;

        TreeNode *t = q->right;

        t->height = maxH(height(t->left), height(t->right)) + 1;
        q->height = maxH(height(q->left), height(q->right)) + 1;
    }

    return q;
}

TreeNode *createNode(int key)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int getBalance(TreeNode *node)
{
    int ret_val = 0;
    if (node != NULL)
    {

        ret_val = height(node->left) - height(node->right);
    }

    return ret_val;
}

TreeNode *insert(TreeNode *root, int key)
{

    if (root == NULL)
        root = createNode(key);

    else if (key != root->data)
    {
        if (key < (root->data))
            root->left = insert(root->left, key);
        else
            root->right = insert(root->right, key);

        root->height = maxH(height(root->left), height(root->right)) + 1;

        int balance = getBalance(root);

        if (balance > 1 && key < root->left->data)
            root = rotateRight(root);
        if (balance < -1 && key > root->right->data)
            root = rotateLeft(root);
        if (balance > 1 && key > root->left->data)
        {
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
        if (balance < -1 && key < root->right->data)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

TreeNode *minValueNode(TreeNode *node)
{
    TreeNode *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

TreeNode *delete (TreeNode *root, int key)
{
    if (root != NULL)
    {
        if (key < root->data)
            root->left = delete (root->left, key);

        else if (key > root->data)
            root->right = delete (root->right, key);

        else
        {
            if (root->left == NULL || root->right == NULL)
            {
                TreeNode *tmp = root->left ? root->left : root->right;

                if (tmp == NULL)
                {
                    tmp = root;
                    root = NULL;
                }

                else
                {
                    *root = *tmp;
                }

                free(tmp);
            }

            else
            {
                TreeNode *tmp = minValueNode(root->right);

                root->data = tmp->data;

                root->right = delete (root->right, tmp->data);
            }

            if (root != NULL)
            {
                root->height = 1 + maxH(height(root->left), height(root->right));
                int balance = getBalance(root);

                if (balance > 1 && key < root->left->data)
                    root = rotateRight(root);
                if (balance < -1 && key > root->right->data)
                    root = rotateLeft(root);
                if (balance > 1 && key > root->left->data)
                {
                    root->left = rotateLeft(root->left);
                    root = rotateRight(root);
                }
                if (balance < -1 && key < root->right->data)
                {
                    root->right = rotateRight(root->right);
                    return rotateLeft(root);
                }
            }
        }
    }

    return root;
}

int main()
{

    TreeNode *root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 12);
    root = insert(root, 18);
    root = insert(root, 11);
    root=delete(root,10);
    inorder(root);
    return 0;
}
