#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"


int main(){
    
    printf("\n~~~~~~~~~~~~~~~~~~~~~~Leap Year Problem~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
    int year;
    printf("Please enter year to find is it leap year or not : ");
    scanf("%d",&year);
    controll_Leap_Year(year);

    char format;
    int m,n;
    char operator;
    double result;
    double operand1, operand2;  

    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~Enhanced Calculator~~~~~~~~~~~~~~~~~~~~~~\n\n\n");

    printf("Enter the format of output (S or I) : ");
    
    scanf(" %c",&format);

    format_controller(format);

    if(format== 's' || format=='S'){ // if format scientific taking m and n values
        printf("\nEnter m and n values (“m” is number of total digits of result and “n” is number of digits after decimal n cannot be greater then m) : ");
        scanf("%d %d",&m,&n);
        
        if(n>m){
            printf("Erorr N cannot be greater then M"); // controlling n m values
            exit(0);
        }
    }

    printf("\nEnter The operation please  +, -, *, /,!,^, %% : "); 
    scanf(" %c",&operator);  // taking operator
    operator_control(operator);

    if (operator!='!') // controlling if operator factorial or not
    {
        printf("\nEnter the first operand : ");
        scanf("%lf",&operand1);

        printf("\nEnter the second operand : ");
        scanf("%lf",&operand2);
        
    }
    else
    {   
        printf("\nEnter the operand : ");
        scanf("%lf",&operand1);
    }

    result=operation(operator,operand1,operand2);
    scientificNotation_Integer(result,m,n,format);

    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~Grade Calculator~~~~~~~~~~~~~~~~~~~~~~\n\n\n");

    int first_grade, second_grade, third_grade,assignment1 , assingment2, final_grade;
    int control_grade=0;

    while (control_grade==0)        
    {
        printf("Enter 3 exam grades of students (out of 100) : ");  
        scanf("%d %d %d",&first_grade,&second_grade,&third_grade); // taking grades
        
        printf("Enter 2 assingment  of students (out of 100) : ");
        scanf("%d %d",&assignment1,&assingment2); // taking assignments

        if (first_grade>100 || first_grade<0 || second_grade>100 || second_grade<0  || third_grade>100 || third_grade<0 || assignment1>100 || assignment1<0 || assingment2>100 || assingment2<0)
        {
            printf("You enter invalit input please enter again..\n"); // controlling grades are greater than 100 or less than 0
        } 
        else{
            control_grade=1;
        }
    }

    grade_calculator(first_grade,second_grade,third_grade,assignment1,assingment2);
    

}




















