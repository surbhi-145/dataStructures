#include<stdio.h>
#define MAX_SIZE 100
typedef int itemtype;
typedef enum{FAILURE,SUCCESS} status_code;
typedef struct
{
    itemtype items[MAX_SIZE];
    int front;
    int rear;
}QUEUE;

void initialize(QUEUE *qptr)
{
    qptr->front=0;
    qptr->rear=-1;
}

int isQueueFull(QUEUE *qptr)
{
    int retval;
    if(qptr->front==((qptr->rear + 1)%MAX_SIZE) && (qptr->rear!=-1))
    {
        retval=1;
    }
    else
    {
        retval=0;
    }
    return retval;
}

status_code push(itemtype e,QUEUE *qptr)
{
    status_code retval=SUCCESS;
    if(isQueueFull(qptr))
    {
        retval=FAILURE;
    }
    else
    {
        qptr->rear=(qptr->rear+1)%MAX_SIZE;
        qptr->items[qptr->rear]=e;
    }
    return retval;
}

int isQueueEmpty(QUEUE *qptr)
{
    int retval;
    if(qptr->front==(qptr->rear+1)%MAX_SIZE && qptr->rear==-1)
    {
        retval=1;
    }
    else
    {
        retval=0;
    }
    return retval;
}

status_code pop(itemtype *e,QUEUE *qptr)
{
    status_code retval=SUCCESS;
    if(isQueueEmpty(qptr))
    {
        retval=FAILURE;
    }
    else
    {
        *e=qptr->items[qptr->front];
        qptr->front=(qptr->front+1)%MAX_SIZE;
        if(qptr->front==(qptr->rear+1)%MAX_SIZE)
        initialize(qptr);
    }
    return retval;
}

int main()
{
    status_code sc;
    QUEUE q;
    itemtype e1,e2,e3;
    initialize(&q);
    sc=push(10,&q);
    sc=push(15,&q);
    sc=push(17,&q);
    sc=pop(&e1,&q);
    sc=pop(&e2,&q);
    sc=pop(&e3,&q);
    printf("%d\n%d\n%d\n",e1,e2,e3);
    sc=pop(&e1,&q);
    if(sc==FAILURE)
    {
        printf("queue was empty\n");
    }
    return 0;
}