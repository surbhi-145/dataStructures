#include<stdio.h>
#include<stdlib.h>

typedef int datatype;
typedef enum{FAILURE,SUCCESS}statuscode;

//It is  a circular queue.
typedef struct 
{
    int start,end;
    int capacity;
    datatype* data;

}Queue;

void initialize(Queue** ptr, int size)
{
    *ptr=(Queue*)malloc(sizeof(Queue));
    (*ptr)->start=0;//the position of the last deleted element.
    (*ptr)->end=-1;//the position of the last inserteds element.
    (*ptr)->capacity=size;
    (*ptr)->data=(datatype*)malloc(size*sizeof(datatype));
}

statuscode isFull(Queue** ptr)
{
    statuscode sc=FAILURE;

    if((*ptr)->start==((*ptr)->end+1)%(*ptr)->capacity && (*ptr)->end!=-1) // Be careful
    sc= SUCCESS;

    return sc;
}
statuscode isEmpty(Queue** ptr)
{
    statuscode sc=FAILURE;

    if((*ptr)->start==((*ptr)->end+1)%(*ptr)->capacity && (*ptr)->end==-1)//Be careful
    sc=SUCCESS;

    return sc;
}

statuscode front(Queue** ptr, datatype* d)
{
    statuscode sc=SUCCESS;

    if(isEmpty(ptr)==1)
    sc=FAILURE;

    else
    {
        *d=*((*ptr)->data+((*ptr)->start%(*ptr)->capacity));
    }

    return sc;
    
}
statuscode end(Queue** ptr, datatype* d)
{
    statuscode sc=SUCCESS;

    if(isEmpty(ptr)==1)
    sc=FAILURE;

    else
    {
        *d=*((*ptr)->data+((*ptr)->end%(*ptr)->capacity));
    }

    return sc;   
}
statuscode enqueue(Queue** ptr, datatype d)
{
    statuscode sc=SUCCESS;

    if(isFull(ptr)==1)
    sc=FAILURE;

    else
    {
        (*ptr)->end+=1;
        (*ptr)->end%=(*ptr)->capacity;
        *((*ptr)->data+((*ptr)->end%(*ptr)->capacity))=d;
    }
    
    return sc;

}

statuscode dequeue(Queue** ptr, datatype* d)
{
    statuscode sc=SUCCESS;

    if(isEmpty(ptr)==1)
    sc=FAILURE;

    else
    {
        *d=*((*ptr)->data+((*ptr)->start%(*ptr)->capacity));
        (*ptr)->start+=1;
        (*ptr)->start%=(*ptr)->capacity;

        if(((*ptr)->start)==((*ptr)->end+1)%(*ptr)->capacity) // Important condition.
        {
            (*ptr)->start=0;
            (*ptr)->end=-1;
        }
    }
    
    return sc;
}

void main()
{
    Queue* queue;

    initialize(&queue,5);
    statuscode sc;
    datatype d;

    sc=isEmpty(&queue);

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
        printf("%d\n", *((queue)->data+((queue)->end%(queue)->capacity)));
    }
    else
    {
        printf("failed at Enqueue\n");
    }

    sc=enqueue(&queue,34);

    sc=isFull(&queue);
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

    sc=isFull(&queue);
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