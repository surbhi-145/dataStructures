#include<stdio.h>
#include<stdlib.h>
typedef int datatype;
typedef enum{Failure,Success}statuscode;

typedef struct NodeTag
{
    datatype data;
    struct NodeTag* next;
}Node;

void initialize(Node** ptr,Node** end, datatype d)
{
    *ptr=(Node*)malloc(sizeof(Node));
    (*ptr)->next=NULL;
    (*ptr)->data=d;
    *end=*ptr;
}

statuscode insertAtStart(datatype d, Node** ptr, Node** end)
{
    statuscode sc=Success;
    Node* nptr=(Node*)malloc(sizeof(Node));
    if(nptr==NULL)
    sc=Failure;
    else
    {
        if(*ptr==NULL)
        {
            *end=nptr;
            *ptr=nptr;
            (*ptr)->data=d;
            (*ptr)->next=NULL;
        }

        else
        {
            nptr->next=*ptr;
            nptr->data=d;
            *ptr=nptr;
        }
        
    }
    
    return sc;

}

statuscode insertAtEnd(Node** ptr, datatype d, Node** start)
{
    statuscode sc=Success;
    Node* nptr=(Node*)malloc(sizeof(Node));
    if(nptr==NULL)
    sc=Failure;
    else
    {
        if ((*ptr)==NULL)
        {
            *start=nptr;
            *ptr=nptr;
            (*ptr)->data=d;
            (*ptr)->next=NULL;
        }

        else
        {
            nptr->data=d;
            (*ptr)->next=nptr;
            nptr->next=NULL;
            *ptr=nptr;
        }
        
    }
    
    return sc;
}

statuscode deleteAtStart(Node** ptr, datatype* d, Node** end)
{
    statuscode sc= Success;
    if(*ptr==NULL)
    sc=Failure;
    else
    {
        *d=(*ptr)->data;
        if ((*ptr)->next==NULL)
        {
            Node* nptr=(*ptr);
            free(nptr);   
            (*ptr)==NULL;
            (*end)==NULL;
        }

        else
        {
            Node* nptr=(*ptr);
            (*ptr)=(*ptr)->next;
            free(nptr);
        }
        
        
    }

    return sc;
}

    statuscode deleteAtEnd(Node** start, Node** end, datatype* d)
    {
        statuscode sc=Success;
        if((*start)==NULL)
        sc=Failure;

        else
        {
            *d=(*end)->data;
            Node* temp=(*start);

            if((*start)->next==NULL)
            {
                (*start)=(*end)=NULL;
                free(temp);
                
            }

            else
            {
                while(temp->next != (*end))
                {
                    temp=(temp->next);

                }

                temp->next=NULL;
                Node* here=*end;
                (*end)=temp;
                free(here);
                
            }
        }
        
        return sc;

    }

    void main() {
        
        Node* start;
        Node* end;
        initialize(&start,&end,10);
        //*end=*start;
        statuscode sc;
        datatype d;

        sc=insertAtStart(5,&start);
        if(sc==1)
        {
            printf("%d\n",start->data);
        }

        else
        {
            printf("Failed\n");
        }
        

        sc=deleteAtEnd(&start,&end,&d);
        if(sc==1)
        {
            printf("%d\n",d);
        }

        else
        {
            printf("Failed\n");
        }


    }
    

