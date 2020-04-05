#include <stdio.h>
#include <stdlib.h>
#include<string.h>
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

void initialize(Node **ptr, Node **end, datatype d)
{
    *ptr = (Node *)malloc(sizeof(Node));
    (*ptr)->next = NULL;
    (*ptr)->data = d;
    *end = *ptr;
}

statuscode insertAtStart(datatype d, Node **ptr)
{
    statuscode sc = Success;
    Node *nptr = (Node *)malloc(sizeof(Node));
    if (nptr == NULL)
        sc = Failure;
    else
    {
        if (*ptr == NULL)
        {
            *ptr = nptr;
            (*ptr)->data = d;
            (*ptr)->next = NULL;
        }

        else
        {
            nptr->next = *ptr;
            nptr->data = d;
            *ptr = nptr;
        }
    }

    return sc;
}

statuscode insertAtEnd(Node **ptr, datatype d)
{
    statuscode sc = Success;
    Node *nptr = (Node *)malloc(sizeof(Node));
    if (nptr == NULL)
        sc = Failure;
    else
    {
        if ((*ptr) == NULL)
        {
            *ptr = nptr;
            (*ptr)->data = d;
            (*ptr)->next = NULL;
        }

        else
        {
            nptr->data = d;
            (*ptr)->next = nptr;
            nptr->next = NULL;
            *ptr = nptr;
        }
    }

    return sc;
}

statuscode deleteAtStart(Node **ptr, datatype *d)
{
    statuscode sc = Success;
    if (*ptr == NULL)
        sc = Failure;
    else
    {
        *d = (*ptr)->data;
        if ((*ptr)->next == NULL)
        {
            (*ptr) == NULL;
        }

        else
        {
            Node *nptr = (*ptr);
            (*ptr) = (*ptr)->next;
            free(nptr);
        }
    }

    return sc;
}

statuscode deleteAtEnd(Node **start, Node **end, datatype *d)
{
    statuscode sc = Success;
    if ((*start) == NULL)
        sc = Failure;

    else
    {
        *d = (*end)->data;
        Node *temp = (*start);

        if ((*start)->next == NULL)
        {
            (*start) = (*end) = NULL;
        }

        else
        {
            while (temp->next != (*end))
            {
                temp = (temp->next);
            }

            temp->next = NULL;
            Node *here = *end;
            (*end) = temp;
            free(here);
        }
    }

    return sc;
}

void input(Node **start, Node **end)
{
    statuscode sc;
    char ans[500];
    printf("enter a  positive number\n");
    scanf("%s",ans);

    int i=0;
    while(i<strlen(ans))
    {
        int d=(int)ans[i];
        d-=48;
        sc=insertAtEnd(end,d);
        i+=1;
    }

    sc=deleteAtStart(start,&i);

}

Node* reverse(Node* current, Node* prev)
{
    Node* end;

    if(current->next==NULL)
    {
        current->next=prev;
        end=current;
    }

    else
    {
        end=reverse(current->next,current);
        current->next=prev;
    }
    
    return end;
    
}

Node* increment(Node *start)
{
    start=reverse(start,NULL);
    Node* ptr=start;
    datatype carry=1;

    while (ptr->next!=NULL)
    {

        int d=ptr->data;
        d+=carry;

        if(d>=10)
        {
            carry=d/10;
            d=d%10;

        }

        else
        {
            carry=0;
        }

        ptr->data=d;

        ptr=ptr->next;
    }

    int d=ptr->data;
        d+=carry;
        carry=d/10;
            d=d%10;
             ptr->data=d;
        
    start=reverse(start,NULL);

    if(carry>0)
        {
             statuscode sc=insertAtStart(carry,&start);
        }
    
    return start;
}

Node* decrement(Node* start)
{
    start=reverse(start,NULL);
    Node* ptr=start;
    datatype sub=1;

    while (ptr->next!=NULL)
    {

        int d=ptr->data;
        d-=sub;

        if(d<0)
        {
            d+=10;

        }

        else
        {
            sub=0;
        }

        ptr->data=d;

        ptr=ptr->next;
    }

    int d=ptr->data;
        d-=sub;
        if(d<0)
        {
            d+=10;

        }
         ptr->data=d;

         start=reverse(start,NULL);

    if(start->data==0)
    start=start->next;

    return start;
}

Node* addition(Node *start1, Node* start2)
{
    start1=reverse(start1,NULL);

    start2=reverse(start2,NULL);
    
    Node *ptr1=start1;
    Node *ptr2=start2;
    datatype carry=0;

    while (ptr1->next!=NULL && ptr2->next!=NULL)
    {
        datatype d=ptr1->data+ptr2->data+carry;

        if (d>=10)
        {
            carry=d/10;
            d%=10;
        }

        else
        {
            carry=0;
        }

        ptr1->data=d;
        ptr1=ptr1->next;
        ptr2=ptr2->next;
        
    }
   

}

void main()
{

    Node *start;
    Node *end;
    initialize(&start, &end, 0);
    statuscode sc;
    datatype d;
    input(&start,&end);
    start=increment(start);
    Node* ptr=start;

    printf("INCREMENT\n");
    while (ptr!=NULL)
    {
        printf("%d",ptr->data);
        ptr=ptr->next;
    }

    printf("\n");

    start=decrement(start);
    ptr=start;

    printf("DECREMENT\n");
    while (ptr!=NULL)
    {
        printf("%d",ptr->data);
        ptr=ptr->next;
    }

    printf("\n");


    Node *startx;
    Node *endx;
    initialize(&startx, &endx, 0);
    input(&startx,&endx);

    start=addition(start,startx);
    ptr=start;

    printf("ADDITION\n");
    while (ptr!=NULL)
    {
        printf("%d",ptr->data);
        ptr=ptr->next;
    }

    printf("\n");

}
