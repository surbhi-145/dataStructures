#include<stdio.h>
#include<stdlib.h>

typedef int datatype;

typedef struct 
{
    datatype* data;
    int capacity;
    int top;//stores index of last value inserted.
}Stack;

typedef enum{FAILURE, SUCCESS}statuscode;

void initialize(Stack** sptr, int size)
{
    (*sptr)=(Stack*)malloc(sizeof(Stack));
    (*sptr)->capacity=size;
    (*sptr)->top=-1;
    (*sptr)->data=(datatype*)malloc(size*sizeof(datatype));
}

statuscode isFull(Stack* ptr)
{
    statuscode sc= FAILURE;

    if(ptr->top==ptr->capacity-1)
    {
        sc=SUCCESS;
    }

    return sc;
}

statuscode isEmpty(Stack* ptr)
{
    statuscode sc=FAILURE;

    if(ptr->top==-1)
    {
        sc=SUCCESS;
    }

    return sc;
}

statuscode push(Stack** sptr, datatype d)
{
    statuscode sc= SUCCESS;

    if(isFull(*sptr)==SUCCESS)
    sc=FAILURE;

    else
    {
        (*sptr)->top+=1;
        *((*sptr)->data+(*sptr)->top)=d;
    }
    
    return sc;
}

statuscode pop(Stack** sptr, datatype* d)
{
    statuscode sc= SUCCESS;

    if(isEmpty(*sptr)==SUCCESS)
    sc=FAILURE;

    else
    {
        *d=*((*sptr)->data+(*sptr)->top);
        (*sptr)->top-=1;
    }

    return sc;
    
}

void main()
{
    Stack* stack;
    datatype d;
    initialize(&stack, 10);
    statuscode sc;
    sc=isFull(stack);
    if(sc==SUCCESS)
    {
        printf("Stack Full.\n");
    }
    else
    {
        printf("Stack not full.\n");
    }
    sc=isEmpty(stack);
    if(sc==SUCCESS)
    {
        printf("Stack Empty.\n");
    }
    else
    {
        printf("Stack not Empty.\n");
    }
    sc=push(&stack,12);
    if(sc==SUCCESS)
    {
        printf("%d\n",*((stack)->data+(stack)->top));
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
}



