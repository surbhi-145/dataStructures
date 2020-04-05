#include <stdio.h>
#include <stdlib.h>
typedef int datatype;
typedef enum
{
    Failure,
    Success
} statuscode;

typedef struct NodeTag
{
    datatype data;
    struct NodeTag *next;
} Node;

Node *SelectionSort(Node *start)
{
    Node *pos = start;

    while (pos->next != NULL)
    {
        Node *tmp = pos;
        int min = pos->data;
        Node *ptr = pos->next;

        while (ptr != NULL)
        {
            if (ptr->data < min)
            {
                min = ptr->data;
                tmp = ptr;
            }

            ptr = ptr->next;
        }

        if (tmp != pos)
        {
            int data = tmp->data;
            Node *p = pos;
            Node *q = start;

            while (p->next != tmp)
            {
                p = p->next;
            }

            while (q!=NULL && q->next!=pos)
            {
                q=q->next;
            }
            

            p->next = tmp->next;
            free(tmp);

            Node *new = (Node *)malloc(sizeof(Node));
            new->data = data;
            new->next = pos;
            if (q!=NULL)
            {
                q->next=new;
            }
            if (pos==start)
            {
                start=new;
            }
            pos = new;
        }

        pos = pos->next;
    }

    return start;
}

int main() {

    Node* one;
    one=(Node*)malloc(sizeof(Node));
    one->data=1;
    Node* two;
    two=(Node*)malloc(sizeof(Node));
    two->data=4;
    one->next=two;
    Node* three;
    three=(Node*)malloc(sizeof(Node));
    three->data=0;
    two->next=three;
    Node* four;
    four=(Node*)malloc(sizeof(Node));
    three->next=four;
    four->data=-1;
    four->next=NULL;

    one=SelectionSort(one);

    Node* ptr=one;

    while (ptr!=NULL)
    {
        printf("%d\n",ptr->data);
        ptr=ptr->next;
    }
    

    return 0;
}