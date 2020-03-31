#include<stdio.h>
#include<stdlib.h>
typedef int datatype;
typedef enum{FAILURE,SUCCESS}statuscode;

typedef struct NodeTag
{
    datatype data;
    struct NodeTag* next;
}Node;


int main() {

    Node* one;
    one->data=1;
    Node* two;
    two->data=4;
    one->next=two;
    Node* three;
    three->data=0;
    two->next=three;
    three->next=NULL;

    return 0;
}