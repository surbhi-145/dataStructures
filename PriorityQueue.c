#include<stdio.h>
#include<stdlib.h>
#define MAX 10
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

typedef struct priorityQueue
{
    Queue *priority[MAX];
}priorityQueue;

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

void initializePQ(priorityQueue** pq)
{
    (*pq)=(priorityQueue*)malloc(sizeof(priorityQueue));
    for (int i = 0; i < MAX; i++)
    {
        initialize(&((*pq)->priority[i]));
    }
    
}

statuscode insertPQ(int priority, datatype data, priorityQueue* pq)
{
    statuscode sc=SUCCESS;

    sc=enqueue(&pq->priority[priority],data);

    return sc;

}

statuscode deletePQ(datatype* d,priorityQueue* pq)
{
    statuscode sc=FAILURE;
    datatype data;
    for (int i = 0; i < MAX; i++)
    {
        if (isEmpty(&(pq->priority[i]))==FAILURE)
        {
            sc=dequeue(&(pq->priority[i]),&data);
            *d=data;
        }
        
    }

    return sc;
    
}

void main()
{
    priorityQueue* object;
    datatype d;
    int priority;
    Node* ptr;

    initializePQ(&object);
    insertPQ(0,10,object);
    insertPQ(1,12,object);
    insertPQ(1,13,object);
    insertPQ(1,14,object);

    ptr=object->priority[0]->front;
    while (ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr=ptr->next;
    }
    printf("\n");

    ptr=object->priority[1]->front;
    while (ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr=ptr->next;
    }

    printf("\n");

    deletePQ(&d,object);

    printf("%d\n",d);
    

}
