#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"


void controll_Leap_Year(int year){
    
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){  // controlling if year is divisble  
        
        printf("%d year is a leap year\n",year);       
    }  
    else{
        printf("%d year is not leap year\n",year);
    }
}

int factorial(int num) {
    if (num == 0) {       // taking factorial 
        return 1;
    } else {
        return num * factorial(num-1);
    }
}

void format_controller(char format){
    if (format =='S' || format=='s' || format== 'I' || format== 'i') // controlling the format is correct or not
    {  }   

    else{ printf(" Warning Invalit Format !!\n"); 
        exit(0);
    }
} 


void operator_control(char operator){ // controlling operator
    switch (operator)
    {
    case '+':
        break;
    case '-':
        break; 
    case '/':
        break;
    case '*':
        break;
    case '%':
        break;
    case '!':
        break;
    case '^':
        break;
    default:
        printf("Invalid Operator\n");
        exit(0);
        break;
    }
}

double operation(char operator,double operand1, double operand2){  // making operation in switch case
    double result=0;
    switch (operator)
         {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if(operand2 == 0)
            {
                printf("Error Divisior cannot be 0 \n");
                exit(0);
            }
            result = operand1 / operand2;
            break;
        case '!':
            result = factorial((int)operand1);
            break;
        case '^':
            result = pow(operand1, operand2);
            break;
        case '%':
            result = fmod(operand1, operand2);
            break;
        default:
            printf("Error: Invalid operator.\n");
            result = 0;
            break;
    }
    
    return result;
}



void scientificNotation_Integer(double result, int m, int n, char format){
    if(format== 's' || format=='S'){  // choosing format integer or scientific
        
        int counter=0;
        double tempResult=result;
        int digits=0;
        
        for (; fmod(result, 1) != 0; counter--){ // taking result mode by 1 to taking numbers before decimal
            result *= 10;}
        for(;fmod(result,10) ==0; counter++){ // deleting zeros
            result/=10;}
        for (; 1<tempResult; digits++){ // count digits except 0
            tempResult/=10;
        }
        
        if(digits>m){ // controlling digits
            printf("Error your values are not enough\n");
            exit(0);
        }
        
        for (int j=1; j<=n; j++) // write digits to right
        {   
            result/=10;
            counter++;    
        }
        
        m+=1;
        printf("Result = %0*.*lfe%d",m,n,result,digits); // printing result
    }

    else{
        printf("%d",(int)result); // printing result
    }

}


void grade_calculator(int ex1, int ex2, int ex3, int assign1, int assign2){
    int final_grade;
    
    final_grade =((ex1 + ex2 + ex3) / 3) * 0.6 + ((assign1 + assign2) / 2 )* 0.4;  // calculating final grade with given formula


    if(final_grade<60){
        printf(" Final Grade : %d failed \n",final_grade); // controlling final grade
    }

    else{
        printf(" Final Grade : %d passed \n",final_grade);
    }

}