#include <stdio.h>
#include <stdlib.h>
#define ARRSIZE 101

typedef enum 
{
    Failure,
    Success
}statuscode;

typedef struct value
{
    int data;
    int flag;
} value;

typedef struct Node
{
    int data;
    struct Node *next;  
}Node;

value arr[ARRSIZE];
Node *bucket[ARRSIZE];

void initialize()
{
    for (int i = 0; i < ARRSIZE; i++)
    {
        arr[i].flag = 0;
    }
}

statuscode insert_linear(int d)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    while (index < ARRSIZE && arr[index].flag == 1)
    {
        index += 1;
    }

    if (index < ARRSIZE)
    {
        arr[index].data = d;
        arr[index].flag = 1;
    }

    else
    {
        sc = Failure;
    }

    return sc;
}

statuscode delete_linear(int d)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    int flag=1;

    while (index<ARRSIZE && flag==1)
    {
        if (arr[index].data==d && arr[index].flag==1)
        {
            arr[index].flag=0;
            flag=0;
        }

        else if (arr[index].data%ARRSIZE!=d%ARRSIZE)
        {
            flag=-1;
        }
        
        else
        {
            index+=1;
        }
        
    }

    if (flag!=0)
    {
        sc=Failure;
    }
    
    return sc;
}
statuscode search_linear(int d, int *i)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    int flag=1;

    while (index<ARRSIZE && flag==1)
    {
        if (arr[index].data==d && arr[index].flag==1)
        {
            *i=index;
            flag=0;
        }

        else if (arr[index].data%ARRSIZE!=d%ARRSIZE)
        {
            flag=-1;
        }
        
        else
        {
            index+=1;
        }
        
    }

    if (flag!=0)
    {
        sc=Failure;
    }
    
    return sc;
}

void linear()
{
    initialize();
    statuscode sc;
    printf("----LINEAR----\n");
    sc=insert_linear(10);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    
    sc=insert_linear(20);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    sc=insert_linear(111);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    sc=delete_linear(111);
    if (sc==1)
    {
        printf("Deleted Successfully\n");
    }
    int index;
    sc=search_linear(111,&index);
    if (sc==1)
    {
         printf("Found Successfully at %d\n",index);
    }
    else
    {
        printf("Not Found\n");
    }

}


statuscode insert_quadratic(int d)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    int k=1;
    while (index < ARRSIZE && arr[index].flag == 1)
    {
        index = index + k;
        k+=2;
    }

    if (index < ARRSIZE)
    {
        arr[index].data = d;
        arr[index].flag = 1;
    }

    else
    {
        sc = Failure;
    }

    return sc;
}

statuscode delete_quadratic(int d)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    int flag=1;
    int k=1;

    while (index<ARRSIZE && flag==1)
    {
        if (arr[index].data==d && arr[index].flag==1)
        {
            arr[index].flag=0;
            flag=0;
        }

        else if (arr[index].data%ARRSIZE!=d%ARRSIZE)
        {
            flag=-1;
        }
        
        else
        {
            index=index+k;
            k+=2;
        }
        
    }

    if (flag!=0)
    {
        sc=Failure;
    }
    
    return sc;
}

statuscode search_quadratic(int d, int *i)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    int flag=1;
    int k=1;

    while (index<ARRSIZE && flag==1)
    {
        if (arr[index].data==d && arr[index].flag==1)
        {
            *i=index;
            flag=0;
        }

        else if (arr[index].data%ARRSIZE!=d%ARRSIZE)
        {
            flag=-1;
        }
        
        else
        {
            index+=k;
            k+=2;
        }
        
    }

    if (flag!=0)
    {
        sc=Failure;
    }
    
    return sc;
}

void quadratic()
{
    initialize();
    statuscode sc;
    printf("----QUADRATIC----\n");
    sc=insert_quadratic(10);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    
    sc=insert_quadratic(20);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    sc=insert_quadratic(111);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    sc=insert_quadratic(212);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    int index;
    sc=search_quadratic(111,&index);
    if (sc==1)
    {
         printf("Found Successfully at %d\n",index);
    }
    else
    {
        printf("Not Found\n");
    }
    sc=search_quadratic(212,&index);
    if (sc==1)
    {
         printf("Found Successfully at %d\n",index);
    }
    else
    {
        printf("Not Found\n");
    }
    sc=delete_quadratic(111);
    if (sc==1)
    {
        printf("Deleted Successfully\n");
    }
}

void initialize_bucket()
{
    for (int i = 0; i < ARRSIZE; i++)
    {
        bucket[i]=NULL;
    }
    
}

statuscode insert_bucket(int d)
{
    statuscode sc=Success;
    int index=d%ARRSIZE;
    Node* new=(Node*)malloc(sizeof(Node));
    if (new==NULL)
    {
        sc=Failure;
    }
    
    else 
    {
        new->data=d;
    new->next=bucket[index];
    bucket[index]=new;
    }

    return sc;
    
}

statuscode delete_bucket(int d)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    int flag=0;

    Node* prev=NULL;
    Node* ptr=bucket[index];

    while (ptr!=NULL && flag==0)
    {
        if (ptr->data==d)
        {
            flag=1;
            if (prev==NULL)
            {
                Node* temp=ptr;
                ptr=NULL;
                free(temp);
                
            }

            else
            {
                prev->next=ptr->next;
                free(ptr);

            }
            
        }

        else
        {
            prev=ptr;
            ptr=ptr->next;
        }
        
    }

    if (flag!=1)
    {
        sc=Failure;
    }
    
    return sc;

}

statuscode search_bucket(int d)
{
    statuscode sc = Success;
    int index = d % ARRSIZE;
    int flag=0;

    Node* prev=NULL;
    Node* ptr=bucket[index];

    while (ptr!=NULL && flag==0)
    {
        if (ptr->data==d)
        {
            flag=1;
            
        }

        else
        {
            prev=ptr;
            ptr=ptr->next;
        }
        
    }

    if (flag!=1)
    {
        sc=Failure;
    }
    
    return sc;

}

void bucketing()
{
    initialize_bucket();
    statuscode sc;
    printf("----BUCKET----\n");
    sc=insert_bucket(10);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    
    sc=insert_bucket(20);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    sc=insert_bucket(111);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    sc=insert_bucket(212);
    if (sc==1)
    {
        printf("Inserted Successfully\n");
    }
    int index;
    sc=search_bucket(111);
    if (sc==1)
    {
         printf("Found Successfully\n");
    }
    else
    {
        printf("Not Found\n");
    }
    sc=search_bucket(212);
    if (sc==1)
    {
         printf("Found Successfully\n");
    }
    else
    {
        printf("Not Found\n");
    }
    sc=delete_bucket(111);
    if (sc==1)
    {
        printf("Deleted Successfully\n");
    }
}

void main()
{
    linear();
    quadratic();
    bucketing();
}