#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"


int main(){

    int options;

    printf("\n\nWelcome To The 2D Puzzle Game\n");
    


    do
    {   

        printf("1. New Game\n");
        printf("2. Help\n");
        printf("3. Exit\n\n");
        scanf("%d",&options); // taking menu options

        switch (options)
        {
        case 1:
            startGame(); // calling game func
            break;
        case 2:
            help(); // calling game rules
            break;
        case 3:
            exitGame(); // exit game
            break;
        default:
            printf("Invalid Input");
            break; 
        } 
        
    } while (options<=2  && options>0); // if the option is not in the this range it will exit

    return 0;
}







