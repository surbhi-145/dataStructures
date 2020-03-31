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

/**void initialize(Stack** sptr, int size)
{
    (*sptr)=(Stack*)malloc(sizeof(Stack));
    (*sptr)->capacity=size;
    (*sptr)->top=-1;
    (*sptr)->data=(datatype*)malloc(size*sizeof(datatype));
}**/

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

typedef struct 
{
    Stack* s1;
    Stack* s2;
}Queue;

statuscode enqueue(Queue** ptr, datatype d)
{
    statuscode sc=SUCCESS;
    if(isFull((*ptr)->s1)==1)
    sc=FAILURE;

    else
    {
        sc=push(&((*ptr)->s1),d);
    }

    return sc;
    
}

statuscode dequeue(Queue** ptr, datatype* d)
{
    statuscode sc=SUCCESS;
    if(isEmpty((*ptr)->s1)==1)
    sc=FAILURE;

    else
    {
        while ((*ptr)->s1->top>=0)
        {
            sc=pop(&(*ptr)->s1,d);
            sc=push(&(*ptr)->s2,*d);
        }

        datatype* temp;

        while ((*ptr)->s2->top>=0)
        {
            sc=pop(&(*ptr)->s2,temp);
            sc=push(&(*ptr)->s1,*temp);
        }

        (*ptr)->s1->top-=1;
        
    }

    return sc;
    
}

statuscode front(Queue** ptr, datatype* d)
{
     statuscode sc=SUCCESS;
    if(isEmpty((*ptr)->s1)==1)
    sc=FAILURE;

    else
    {
        while ((*ptr)->s1->top>=0)
        {
            sc=pop(&(*ptr)->s1,d);
            sc=push(&(*ptr)->s2,*d);
        }

        datatype* temp;

        while ((*ptr)->s2->top>=0)
        {
            sc=pop(&(*ptr)->s2,temp);
            sc=push(&(*ptr)->s1,*temp);
        }

    }

    return sc;
}

statuscode end(Queue** ptr, datatype* d)
{
    statuscode sc=SUCCESS;
    if(isEmpty((*ptr)->s1)==1)
    sc=FAILURE;

    else
    {
        *d=*((*ptr)->s1->data+(*ptr)->s1->top);
    }

    return sc;
    
}

void initialize(Queue** ptr, int size)
{
    *ptr=(Queue*)malloc(sizeof(Queue));

    (*ptr)->s1=(Stack*)malloc(sizeof(Stack));
    (*ptr)->s1->capacity=size;
    (*ptr)->s1->top=-1;
    (*ptr)->s1->data=(datatype*)malloc(size*sizeof(datatype));

    (*ptr)->s2=(Stack*)malloc(sizeof(Stack));
    (*ptr)->s2->capacity=size;
    (*ptr)->s2->top=-1;
    (*ptr)->s2->data=(datatype*)malloc(size*sizeof(datatype));
}

statuscode isQueueEmpty(Queue** ptr)
{
    return isEmpty((*ptr)->s1);

}

statuscode isQueueFull(Queue** ptr)
{
    return isFull((*ptr)->s1);

}

void main()
{
    Queue* queue;

    initialize(&queue,5);
    statuscode sc;
    datatype d;

    sc=isQueueEmpty(&queue);

    if(sc==1)
    {
        printf("Empty queue\n");
    }
    else
    {
        printf("Non empty queue.\n");
    }

    sc=enqueue(&queue,10);
    sc=enqueue(&queue,8);
    sc=enqueue(&queue,1);
    if(sc==1)
    {
        printf("%d\n", *((queue)->s1->top+(queue)->s1->data));
    }
    else
    {
        printf("failed at Enqueue\n");
    }

    sc=enqueue(&queue,34);

    sc=isQueueFull(&queue);
     if(sc==1)
    {
        printf("Queue is full.\n");
    }
    else
    {
        printf("Queue is not full yet.\n");
    }
    
    sc=dequeue(&queue,&d);
    if(sc==1)
    {
        printf("%d\n",d);
    }
    else
    {
        printf("Nothing left to dequeue.\n");
    }

    sc=enqueue(&queue,10);
    sc=enqueue(&queue,100);

    sc=isQueueFull(&queue);
     if(sc==1)
    {
        printf("Queue is full.\n");
    }
    else
    {
        printf("Queue is not full yet.\n");
    }

    sc=front(&queue,&d);
    if(sc==1)
    {
        printf("%d\n",d);
    }
    else
    {
        printf("Front() not working.\n");
    }

    sc=end(&queue,&d);
    if(sc==1)
    {
        printf("%d\n",d);
    }
    else
    {
        printf("end() not working.\n");
    }
}



