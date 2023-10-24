#include<stdio.h>
#include<stdlib.h>
int main ()
{
    int two[3][2]= {{2,3}, {4,5}, {6,7}};
    int i;
    int j;
    for(i=0;i<3;i++){
        for(j=0;j<2;j++){
            printf("%d,",two[i][j]);
        }
        printf("\n");
    }
    return 0;
}