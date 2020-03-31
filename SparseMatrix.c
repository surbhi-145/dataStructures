#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef int datatype;
typedef enum{FAILURE,SUCCESS}statuscode;
//Implement priority Queue with assign,access,addition,multiplication

typedef struct Node 
{ 
    int value; 
    int row_position; 
    int column_postion; 
    struct Node *next_row;
    struct Node *next_col; 
}Node;

statuscode createNode(Node** start, int row, int col, int value)
{
    Node *ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr->column_postion=col;
    ptr->row_position=row;
    ptr->next_col=NULL;
    ptr->next_row=NULL;
    ptr->value=value;

    Node *list=*start;

    while (list->next_col!=NULL)
    {
        list=list->next_col;
    }

    list->next_col=ptr;

    list=*start;
    while (list->next_row!=NULL)
    {
        list=list->next_row;
    }

    list->next_row=ptr;

}

int main() {
    return 0;
}

