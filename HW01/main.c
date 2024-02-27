#include <stdio.h>
#include "util.h"
int main(){

    int gcdnum1,gcdnum2;

    printf("Enter the dividend number for the find greatest common divisor\n");
    scanf("%d",&gcdnum1); // taking an number from user 
    printf("Enter the divisor for the find  greatest common divisor\n");
    scanf("%d",&gcdnum2); // taking an number from user 
    greatest_common_divisor(gcdnum1,gcdnum2); // sending these number to my function which in the util.c
    printf("Greatest Common Divisor = %d\n",greatest_common_divisor(gcdnum1,gcdnum2));


    int addnum1,addnum2;

    printf("Enter the first number you want to sum\n");
    scanf("%d",&addnum1);     // taking an number from user 
    printf("Enter the second number you want to sum\n");
    scanf("%d",&addnum2);    // taking an number from user 
    addition(addnum1,addnum2);   // sending these numbers to my function which in the util.c

    int multinum1, multinum2;

    printf("Enter the first number you want to multiply\n");
    scanf("%d",&multinum1); // taking an number from user 
    printf("Enter the second number you want to multiply\n");
    scanf("%d",&multinum2);// taking an number from user 
    multiplations(multinum1,multinum2); // sending these numbers to my function which in the util.c

    int rangenum;

    printf("Enter the numberbetween 1 and 10 (inclusive) to find range of number \n");
    scanf("%d",&rangenum);// taking an number from user 
    controlling_number_range(rangenum); // sending this number to my function which in the util.c


}