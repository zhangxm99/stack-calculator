#include <stdio.h>
#include "stack.h"
#define e 0.0001  

int hierachy(char operator);
ElementType Calculate(ElementType First,ElementType Second,char operator);
ElementType Power(ElementType First,ElementType Second);

int main(void)
{
    while(1){
        fputs("INPUT: ",stdout);

        Stack Opertor = CreatStack();   //Initialize an operator stack
        Stack General = CreatStack();   //Initialize a general stack that stored both numbers and operators

        char touch;
        while((touch = getchar()) != '\n'){
            ElementType num;
            
            if(touch >= 48 && touch <= 57){
                ungetc(touch,stdin);
                scanf("%f",&num);
                Push_num(num,&General);
            }

            else{
                if(IsEmpty(Opertor)){
                    Push_char(touch,&Opertor);
                }
                else{
                    while(1){
                        if((hierachy(Look(Opertor)) < hierachy(touch)) || touch == '('){
                            if(Look(Opertor) == '('&&touch == ')'){
                                Pop_ch(&Opertor);
                                break;
                            }
                            Push_char(touch,&Opertor);
                            break;
                        }
                        else{
                            //Push_char(Pop_ch(&Opertor),&General);
                            char op = Pop_ch(&Opertor);
                            ElementType Second = Pop_num(&General);
                            ElementType First = Pop_num(&General);
                            Push_num(Calculate(First,Second,op),&General);

                        }
                    }
                }  
            }
        }
        while(!IsEmpty(Opertor)){
            //Push_char(Pop_ch(&Opertor),&General);
            char op = Pop_ch(&Opertor);
            ElementType Second = Pop_num(&General);
            ElementType First = Pop_num(&General);
            Push_num(Calculate(First,Second,op),&General);
        }
        printf("%f\n",Pop_num(&General));

    }
    return 0;
}

int hierachy(char operator){
    switch(operator){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
        case '@':
            return 3;
        case '(':
            return -2;
        case ')':
            return -1;
        default:
            return 0;
    }
}

ElementType Calculate(ElementType First,ElementType Second,char operator){
    ElementType i;
    switch(operator){
        case '+':
            return First + Second;
        case '-':
            return First - Second;
        case '*':
            return First * Second;
        case '/':
            return First / Second;
        case '^':
            return Power(First,Second);
        case '@':
            for(i = 0.0;Power(i,Second) < First;i += e);
            return i;
    }
}
ElementType Power(ElementType First,ElementType Second){
    if(Second == 0.0){
        return 1;
    }
    else{
        ElementType temp = First;
        for(int i = 0;i < Second - 1;i++){
            First = temp * First;
        }
        return First;
    }            
}
