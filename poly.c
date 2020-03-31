#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<limits.h>
typedef int datatype;
typedef enum
{
    FAILURE,
    SUCCESS
} statuscode;

typedef struct poly
{
    float coeff;
    int exp;
    struct poly *next;
} Poly;

Poly* makeNode(float c , int e)
{
    Poly* new=(Poly*)malloc(sizeof(Poly));
    new->coeff=c;
    new->exp=e;
    new->next=NULL;

    return new;
}

Poly* insertTerm(float c, int e, Poly* tail)
{
    Poly* ptr=makeNode(c,e);
    tail->next=ptr;
    return ptr;
}

Poly* readPoly()
{
    float c; 
    int exp,done=0;
    int explast=INT_MAX;
    Poly *result, *tail;
    printf("Enter coeffecients and exponents in decreasing order of exponents.\n");
    result=tail=makeNode(0,0);

    while (!done)
    {   
        printf("Enter exponent-\n");
        scanf("%d",&exp);
        printf("Enter coefficient-\n");
        scanf("%f",&c);

        if (c==0 || (exp>=explast) || (exp<0))
        {
            done=1;
        }

        else
        {
            tail=insertTerm(c,exp,tail);
            explast=exp;

            if (exp==0)
            {
                done=1;
            }
            
        }
    }

    Poly* ptr=result;
    result=result->next;
    free(ptr);
    
    return result;
}

Poly *addPoly(Poly *ptr1, Poly *ptr2)
{
    int sum=0;

    Poly *result,*tail,*ptr;
    tail=result=makeNode(0,0);

    while (ptr1!=NULL && ptr2!=NULL)
    {
        if (ptr1->exp==ptr2->exp)
        {
            sum=(ptr1->coeff)+(ptr2->coeff);

            if (sum!=0)
            {
                tail=insertTerm(sum,ptr1->exp,tail);
            }

            ptr1=ptr1->next;
            ptr2=ptr2->next;
    
        }

        else if(ptr1->exp>ptr2->exp)
        {
            tail=insertTerm(ptr1->coeff,ptr1->exp,tail);
            ptr1=ptr1->next;
        }
        
        else
        {
            tail=insertTerm(ptr2->coeff,ptr2->exp,tail);
            ptr2=ptr2->next;
        }
        
    }

    while (ptr1!=NULL)
    {
        tail=insertTerm(ptr1->coeff,ptr1->exp,tail);
            ptr1=ptr1->next;
    }

    while (ptr2!=NULL)
    {
         tail=insertTerm(ptr2->coeff,ptr2->exp,tail);
            ptr2=ptr2->next;
    }
    
    ptr=result;
    result=result->next;
    free(ptr);

    return result;
}

Poly* removeDuplicate(Poly* start)
{
    Poly *ptr1,*ptr2,*dup;

    ptr1=start;

    while (ptr1->next!=NULL)
    {
        ptr2=ptr1->next;
        dup=ptr1;

        while (ptr2!=NULL)
        {
            if (ptr1->exp==ptr2->exp)
            {
                ptr1->coeff=ptr2->coeff+ptr1->coeff;    
                dup->next=ptr2->next;
                free(ptr2);
                ptr2=dup->next;
            }
            
            else
            {
                dup=dup->next;
                ptr2=ptr2->next;
            }
            
        }

        ptr1=ptr1->next;
        
    }

    return start;
    
}

Poly* multiplyPoly(Poly *ptr1, Poly *ptr2)
{
    Poly *result,*tail,*ptr;
    tail=result=makeNode(0,0);
    Poly *poly1=ptr1;
    Poly* poly2=ptr2;

    while (ptr1!=NULL)
    {
        while(ptr2!=NULL)
        {
            float coeff;
            int exp;

            exp=ptr2->exp+ptr1->exp;
            coeff=(ptr1->coeff)*(ptr2->coeff);

            tail=insertTerm(coeff,exp,tail);

            ptr2=ptr2->next;
        }

        ptr2=poly2;
        ptr1=ptr1->next;
    }

    ptr=result;
    result=result->next;
    free(ptr);

    result=removeDuplicate(result);

    return result;
    
}

int main() {

    Poly* start;
    start=readPoly();

    Poly* new;
    new=readPoly();

    Poly* result;
    result=multiplyPoly(start,new);

    Poly* ptr;
    ptr=result;

    while (ptr!=NULL)
    {
        printf("%d %f\n", ptr->exp,ptr->coeff);
        ptr=ptr->next;
    }
    
    return 0;
}
