#include <stdio.h>
#include <stdlib.h>
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

Node *reverse(Node *current, Node *prev)
{
    Node *end;

    if (current->next == NULL)
    {
        current->next = prev;
        end = current;
    }

    else
    {
        end = reverse(current->next, current);
        current->next = prev;
    }

    return end;
}

Node *loopReverse(Node *start)
{
    Node *prev = NULL;
    Node *current = start;

    if (current != NULL)
    {
        Node *ahead = start->next;
        while (ahead != NULL)
        {
            current->next=prev;
            prev=current;
            current=ahead;
            ahead=ahead->next;
        }

        current->next=prev;

    }

    return current;
}

void main()
{
    Node *start;
    Node *end;
    initialize(&start, &end, 10);
    statuscode sc;
    datatype d;

    sc = insertAtEnd(&end, 20);
    sc = insertAtEnd(&end, 30);
    sc = insertAtEnd(&end, 40);

    Node *ptr = start;

    while (ptr != NULL)
    {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }

     printf("-------------------------\n");

    start = reverse(start, NULL);

    ptr = start;

    while (ptr != NULL)
    {
        if (ptr->next == NULL)
        {
            end = ptr;
        }

        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }

    printf("-------------------------\n");

    start = loopReverse(start);

    ptr = start;

    while (ptr != NULL)
    {
        if (ptr->next == NULL)
        {
            end = ptr;
        }

        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }

}