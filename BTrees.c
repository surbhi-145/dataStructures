#include <stdio.h>
#include<math.h>
#include <stdlib.h>

#define KArr 4
#define D 3//KArr-1
#define MIN 2 // ceil(KArr/2)

typedef struct BTreeNodeTag
{
    int data[D + 1];//An extra data node to make splitting easier
    struct BTreeNodeTag *ptr[KArr + 1];//an extra pointer node to make splitting easier
    int last_data_index;

} BTreeNode;

void printNode(BTreeNode* root)
{
    for(int i=0; i<=root->last_data_index; i+=1)
    {
        printf("%d ",root->data[i]);
    }

    printf("\n");
}

void printTree(BTreeNode* root)
{
    printNode(root);
    for (int i = 0; root->ptr[i]!=NULL && i<= root->last_data_index+1; i++)
    {
        printTree(root->ptr[i]);
    }
    
}

int isLeaf(BTreeNode *node) // returns 0 for not leaf and 1 for leaf
{
    int ans = 1;
    for (int i = 0; i < KArr; i += 1)
    {
        if (*(node->ptr + i) != NULL)
        {
            ans = 0;
        }
    }

    return ans;
}

BTreeNode *createNode(int key)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    *(node->data) = key;
    for (int i = 0; i < KArr; i++)
    {
        *(node->ptr + i) = NULL;
    }
    node->last_data_index = 0;
}

BTreeNode *insertElement(BTreeNode *root, int key)
{
    root->last_data_index += 1;
    int tmp = key, tmp2 = key;
    int i = 0;
    while (i <= root->last_data_index - 1)
    {
        if (key < root->data[i])
        {
            tmp = root->data[i];
            root->data[i] = tmp2;
            tmp2 = tmp;
        }

        i += 1;
    }

    root->data[i] = tmp2;

    return root;
}

BTreeNode *setPointers(BTreeNode *ptr, int index)
{
    while (index < KArr + 1)
    {
        ptr->ptr[index] = NULL;
        index += 1;
    }

    return ptr;
}

BTreeNode *split(BTreeNode *root, int median, BTreeNode *parent, int index)
{
    int data = root->data[median];
    BTreeNode *tmp = createNode(root->data[median + 1]);
    int i = median + 2, j = 1;
    while (i <= root->last_data_index)
    {
        tmp->data[j] = root->data[i];
        j+=1;
        i+=1;
    }

    if(isLeaf(root)==0)
    {
        i=median+1, j=0;
        while(i<=root->last_data_index+1)
        {
            tmp->ptr[j]=root->ptr[i];
            i+=1;
            j+=1;
        }

        root = setPointers(root, median+1);
    }

    float x=root->last_data_index;
    root->last_data_index=floor(x/2)-1;
    tmp->last_data_index=ceil(x/2)-1;

    if (parent != NULL)
    {
        parent = insertElement(parent, data);
        int ptr_length = parent->last_data_index + 1;
        while (index <= ptr_length)
        {
            BTreeNode *tmp2 = parent->ptr[index];
            parent->ptr[index]= tmp;
            tmp = tmp2;
            index+=1;
        }
    }

    else
    {
        parent=createNode(data);
        parent->ptr[0]=root;
        parent->ptr[1]=tmp;

    }

    return parent;
}

BTreeNode *insert(BTreeNode *root, int key)
{
    if (root == NULL)
    {
        root = createNode(key);
    }

    else
    {
        if (isLeaf(root) == 1)
        {
            root = insertElement(root, key);
        }

        else
        {
            int i = 0;
            while (i <= root->last_data_index && key > *(root->data + i))
            {
                i += 1;
            }

            *(root->ptr + i) = insert(*(root->ptr + i), key);

            BTreeNode *tmp = *(root->ptr + i);

            if (tmp->last_data_index == D)
            {
                int median = D / 2;
                root = split(tmp, median, root, i + 1);
            }
        }
    }

    return root;
}

BTreeNode *insertInTheTree(BTreeNode *root, int key)
{
    root=insert(root,key);
    if(root->last_data_index==D)
    {
        //printf("%d\n",root->last_data_index);
        int median=D/2;
        root=split(root,median,NULL,-1);
    }

    return root;
}

BTreeNode* deleteKey(BTreeNode* node,int key)
{
    int delete=1;
    int index=-1;
    node->last_data_index-=1;
    for(int i=0; i<=node->last_data_index; i++)
    {
        if(key==node->data[i] || delete==0)
        {
            index=i;
            delete=0;
            node->data[i]=node->data[i+1];
        }
    }

    return node;
}

BTreeNode* delete(BTreeNode* root, int key, BTreeNode* parent, int child_no)
{
    if(isLeaf(root)==1)
    {
        int child_count=root->last_data_index+1;
        root=deleteKey(root,key);

        if(child_count==MIN)
        {
            int sibling1=child_no-1;
            int sibling2=child_no+1;
            if(sibling1>=0 && root->ptr[sibling1]->last_data_index+1>MIN)
            {
                int index=child_no-1;
                BTreeNode* node=root->ptr[sibling1];
                int data=node->data[root->last_data_index];
                root->last_data_index-=1;
                root=insertElement(root,parent->data[index]);
                parent->data[index]=data;
            }

            else if (sibling1<KArr && root->ptr[sibling2]->last_data_index+1>MIN)
            {
                int index=child_no+1;
                BTreeNode* node=root->ptr[sibling2];
                int data=node->data[0];
                node=deleteKey(node,data);
                root=insertElement(data);
                parent->data[index]=data;
            }

            else
            {
                
                
            }
            
        }
        
    }
}

BTreeNode* deleteinTheTree(BTreeNode* root, int key)
{

}

int main()
{
    BTreeNode* root=NULL;
    root=insertInTheTree(root,1);
    root=insertInTheTree(root,2);
    root=insertInTheTree(root,3);
    root=insertInTheTree(root,4);
    root=insertInTheTree(root,5);
    root=insertInTheTree(root,6);
    root=insertInTheTree(root,7);
    root=insertInTheTree(root,8);
    root=insertInTheTree(root,9);
    root=insertInTheTree(root,10);
    printTree(root);
    return 0;
}