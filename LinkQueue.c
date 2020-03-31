#include<stdio.h>
#include<stdlib.h>
typedef int datatype;
typedef enum{FAILURE,SUCCESS}statuscode;

typedef struct NodeTag
{
    datatype data;
    struct NodeTag* next;
}Node;


typedef struct queue
{
    Node* front;
    Node* end;
}Queue;

void initialize(Queue** ptr)
{
    *ptr=(Queue*)malloc(sizeof(Queue));
    (*ptr)->end=(*ptr)->front=NULL;
}

statuscode isEmpty(Queue** ptr)
{
    statuscode sc=FAILURE;

    if (((*ptr)->end==NULL) && ((*ptr)->front==NULL))
    {
        sc=SUCCESS;
    }
    
    return sc;
}

statuscode front(Queue** ptr, datatype* d)
{
    statuscode sc=SUCCESS;

    if(isEmpty(ptr)==1)
    sc=FAILURE;

    else
    {
        *d=(*ptr)->front->data;
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
        *d=(*ptr)->end->data;
    }

    return sc;   
}

statuscode enqueue(Queue** ptr, datatype d)
{
    statuscode sc=SUCCESS;

    Node* nptr;
        nptr=(Node*)malloc(sizeof(Node));
        if (nptr==NULL)
        {
            sc=FAILURE;
        }
        

    else
    {
        
        nptr->data=d;
        nptr->next=NULL;
        if ((*ptr)->end==(*ptr)->front && (*ptr)->end==NULL )
        {
            (*ptr)->end=(*ptr)->front=nptr;
        }

        else if ((*ptr)->end==(*ptr)->front)
        {
            (*ptr)->end=nptr;
            (*ptr)->front->next=(*ptr)->end;
        }
        else
        {
            (*ptr)->end->next=nptr;
            (*ptr)->end=nptr;
        }
        
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
        (*d)=(*ptr)->front->data;
        Node* nptr=(*ptr)->front;
        ((*ptr)->front)=((*ptr)->front->next);
        free(nptr);

        if((*ptr)->front==NULL) // Important condition.
        {
            (*ptr)->end=(*ptr)->front;
        }
    }
    
    return sc;
}

void main()
{
    Queue* queue;

    initialize(&queue);
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
        printf("%d\n", queue->end->data);
    }
    else
    {
        printf("failed at Enqueue\n");
    }

    sc=enqueue(&queue,34);
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
