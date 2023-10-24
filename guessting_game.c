#include<stdio.h>
#include<stdlib.h>

int main ()
{
    int correct_number =7;
    int i;
    int guess_count = 0;
    int guess_limit=3;
    int outofguess=0;

    while(i!=correct_number && outofguess==0){
        if(guess_count<guess_limit){
            printf("enter the gueesing number ");
            scanf("%d",&i);
            guess_count++;

            }else{
           outofguess=1;
        }
    }
    if(outofguess==1){
            printf("out of guesses");
                 }
        else{
            printf("you win !");
            }
        
        
    
    return 0;
}
    