#include<stdio.h>
#include<stdlib.h>
typedef int datatype;
typedef enum{FAILURE,SUCCESS}statuscode;

typedef struct NodeTag
{
    datatype data;
    struct NodeTag* next;
}Node;

typedef struct StackTag
{
    Node* top;
}Stack;


Node* MakeNode(datatype d)
{
    Node* nptr;
    nptr=(Node*)malloc(sizeof(Node));

    if(nptr!=NULL)
    {
        nptr->data=d;
        nptr->next=NULL;
    }

    else 
    {
        printf("Memory Full\n");
    }
    
    return nptr;
}

void initialize(Stack** ptr)
{
    *ptr=(Stack*)malloc(sizeof(Stack));
    (*ptr)->top=NULL;
}

statuscode push(Stack** sptr, datatype d)
{
    statuscode sc=SUCCESS;

    Node* nptr=MakeNode(d);
    if (nptr==NULL)
    {
        sc=FAILURE;
    }

    else
    {
        nptr->next=(*sptr)->top;
        (*sptr)->top=nptr;
    }
    
    return sc;
    
}

statuscode pop(Stack** sptr, datatype* d)
{
    Node* ptr;

    statuscode sc=SUCCESS;

    if ((*sptr)->top==NULL)
    {
        sc=FAILURE;
    }
    
    else
    {
        ptr=(*sptr)->top;
        *d=ptr->data;
        (*sptr)->top=ptr->next;
        free(ptr);
    }
    
    return sc;
}

int main() {

    Stack* stack;
    datatype d;
    initialize(&stack);
    statuscode sc;
    sc=push(&stack,12);
    if(sc==SUCCESS)
    {
        printf("%d\n",(stack->top->data));
    }
    else
    {
        printf("Failed.");
    }
    sc=push(&stack,10);
    sc=push(&stack,5);
    sc=pop(&stack,&d);
    if(sc==SUCCESS)
    {
        printf("%d\n",d);
    }
    else
    {
        printf("Failed Pop\n");
    }
    return 0;
}








