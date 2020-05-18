#include <stdlib.h>
#include <stdio.h>
typedef float ElementType;

typedef struct SNode
{
    int identifier;   //to identify the data type ，0 is int, 1 is char
    union
    {
        ElementType num;
        char ch;
    } Data;    
    struct SNode *Next;
} SNode;
typedef SNode *Stack;

/* creat a head node and return the pointer */
Stack CreatStack()
{
    Stack S = (Stack)malloc(sizeof(SNode));
    S -> Next = NULL;
    return S;
}
/* to konw if it`s an empty stack*/
int IsEmpty(Stack S)
{
    return (S -> Next == NULL);
}
/* push an integer into a stack */
void Push_num(ElementType item,Stack *S)
{
    Stack new = (Stack)malloc(sizeof(SNode));
    new->Next = *S;
    new->identifier = 0;
    new->Data.num = item;
    *S = new;
}
/* push an character into a stack */
void Push_char(char item,Stack *S)
{
    Stack new = (Stack)malloc(sizeof(SNode));
    new->Next = *S;
    new->identifier = 1;
    new->Data.ch = item;
    *S = new;
}
/* identify the data type */
int Identify_ele(Stack S){
    return S->identifier;
}
/* pop out a integer element */
ElementType Pop_num(Stack *S){
    ElementType num = (*S)->Data.num;
    Stack temp = *S;
    *S = (*S)->Next;
    free(temp);
    return num;
}
/* pop out a character */
char Pop_ch(Stack *S){
    char ch = (*S)->Data.ch;
    Stack temp = (*S);
    *S = (*S)->Next;
    free(temp);
    return ch;
}
/* look the character */
char Look(Stack S){
    return S->Data.ch;
}