#include <stdio.h>



int greatest_common_divisor(int dividend, int divisor) {
  int remainder;
  // Use a while loop to continue the Euclidean algorithm until the divisor is 0.
  while (divisor != 0) {
    // Assign the value of the divisor to the remainder.
    remainder = divisor;
    // Calculate the remainder of the dividend divided by the divisor and assign the result to the divisor.
    divisor = dividend % divisor;
    // Assign the value of the remainder to the dividend.
    dividend = remainder;
  }

  // When the loop exits, return the value of the dividend, which is the greatest common divisor of the original values of dividend and divisor.
  return dividend;
}


void addition(int num1, int num2){ // addition function
    printf("%7d\n", num1);  // with the %4d format speciefer numbers are in the same line
    printf("%7d\n", num2);
    printf("+\n");
    printf("-------\n");
    printf("%7d\n\n\n",num1+num2); // numbers are add upp, using %5d format speciefer because output can be 5 digits
}


void multiplations(int num1, int num2){//multtiplations 

    int ones = num2 % 10;// taking ones digits of second number
    int tens = (num2 / 10) % 10;// taking tens digits of second number
    int hundreds = num2 / 100; // taking hundreds digits of second number

    printf("%7d\n",num1); //with the format speciefer numbers are in the same line multtiplations 
    printf("%7d\n",num2);
    printf("*\n");
    printf("-------\n");
    printf("%7d\n",ones*num1);  

    if (tens!=0)// controlling if there is a tens digits or not
    {
       printf("%6d\n",tens*num1); // if there is a tens digits take it and multpily by first number
    }
    
     
    if(hundreds!=0){    // controlling if there is a hundred digits or not
        printf("%5d\n",hundreds*num1); //if there is a hundreds digits take it and multpily by first number
    }
    
    printf("+\n");
    printf("-------\n");
    printf("%7d\n",num1*num2);
}


void controlling_number_range(int num){
    if(num>1 && num<10){  //controlling number if number range is between 1 and 10 
        if (num>5){   // controlling if number greater than 5
            printf("The integer you entered is greater than 5\n");
        }
        else if(num<=5){ // controlling if number equal or less than 5
            printf("The integer you entered is less than or equal to 5\n");
        }     
    }
    else{
        printf("Invalid input\n"); //if number range is not between 1 and 10 
    }
}

