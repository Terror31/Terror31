#include <stdio.h>
#include <stdlib.h>
int main(){
    double num1;
    double num2;
    char op;
    printf("enter the first number "); // taking input from the users
    scanf("%lf",&num1);
    printf("enter the operations  ");
    scanf( "%s",&op);
    printf("enter the second number ");
    scanf("%lf",&num2);

    if(op=='+'){                        // first operations with operators using if conditions 
        printf("%lf",num1+num2);}
        else if(op =='-'){
            printf("%lf",num1-num2);}
            else if(op =='/'){
                printf("%lf",num1/num2);}
                else if (op =='*'){
                    printf("%lf",num1*num2);
                }
                else{
                    printf("invalid operators ");
                }
                    return 0;
}