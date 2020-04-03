#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

int HEAP[SIZE];

int get_left_index(int i,int n)
{
    int j=(2*i)+1;
    if(j>=n)
    j=-1;

    return j;
}

int get_right_index(int i,int n)
{
    int j=(2*i)+2;
    if(j>=n)
    j=-1;

    return j;
}

void swap(int index1,int index2)
{
    int temp=HEAP[index1];
    HEAP[index1]=HEAP[index2];
    HEAP[index2]=temp;
}

void maximizeParent(int p, int c1, int c2)
{
    
    if(c1!=-1)
    {
        if(HEAP[c1]>HEAP[p])
       swap(p,c1);

       if(c2!=-1)
       {
           if(HEAP[c2]>HEAP[p])
           swap(p,c2);
       }
    }
    
}

void heapify(int i, int n)
{
    int left_index=get_left_index(i,n);
    int right_index=get_right_index(i,n);

    if(left_index!=-1)
    heapify(left_index,n);

    if(right_index!=-1)
    heapify(right_index,n);

    if(left_index!=-1 || right_index!=-1)
    maximizeParent(i,left_index,right_index);
}

void TakeInputs()
{
    for(int i=0; i<SIZE; i+=1)
    {
        printf("Enter :");
        scanf("%d",&(HEAP[i]));
    }
}

void printHeap()
{
    printf("---------------------\n");
    printf("%d\n",HEAP[0]);
    int i;
    int pow=2;
    int sum=pow;
    for(i=1; i<SIZE; i++)
    {   
        printf("%d ",HEAP[i]);
        if(i==sum && i!=SIZE-1)
        {
            printf("\n");
            pow=2*pow;
            sum+=pow;
        }
    }

   printf("\n---------------------\n");
}

void heapSort(int n)
{
    for(int i=n; i>0; i-=1)
    {
        heapify(0,i);
        swap(0,i-1);
    }
}

int main() {
    TakeInputs();
    heapSort(SIZE);
    printHeap();
    return 0;
}