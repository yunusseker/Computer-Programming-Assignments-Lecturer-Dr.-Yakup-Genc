#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"


void gameArena(char gamePlay[3][3],int row,int col,int count);
int winCheck(char gameplay[3][3]);
void fillTheArea(char gamePlay[3][3]);

int main(){

    printf("\n\n~~~~~~~~~~~~~~~~~Letter-Frequency-Problem~~~~~~~~~~~~~~~~~~~~\n\n");

    char fileName[20];
    
    printf("Enter The file name: ");
    scanf(" %s",fileName);
    printf("\n");
    
    letterFrequencyProblem(fileName);


    printf("\n\n~~~~~~~~~~~~~~~~~Mixing-Color~~~~~~~~~~~~~~~~~~~~\n\n");

    char firstInputColor;
    char secondInputColor;
    Color color1;
    Color color2;
    printf("Enter Color 1 (r,g,b,y,o): ");
    
    scanf(" %c", &firstInputColor);

    printf("Enter Color 2 (r,g,b,y,o): ");
    
    scanf(" %c", &secondInputColor);

    switch (firstInputColor)
    {
    case 'r':
    case 'R':
        color1=RED;
        break;
    case 'g':
    case 'G':
        color1=GREEN;
        break;
    case 'b':
    case 'B':
        color1=BLUE;
        break;
    case 'y':
    case 'Y':
        color1=YELLOW;
        break;
    case 'o':
    case 'O':
        color1=ORANGE;
        break;
    default:
        printf("Invalid input!!");
        return 1;
        break;
    }

    switch (secondInputColor)
    {
    case 'r':
    case 'R':
        color2=RED;
        break;
    case 'g':
    case 'G':
        color2=GREEN;
        break;
    case 'b':
    case 'B':
        color2=BLUE;
        break;
    case 'y':
    case 'Y':
        color2=YELLOW;
        break;
    case 'o':
    case 'O':
        color2=ORANGE;
        break;
    default:
        printf("Invalid input!!");
        return 1;
        break;
    }
    
    colMix(color1, color2, mixerColors);
    

    printf("\n\n~~~~~~~~~~~~~~~~~Tic-Tac-Toe~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("Welcome To The Tic-Tac-Toe Game ...\n\n");

    int row;
    int col;
    char gamePlay[3][3];
    int gameCheck =1;
    int count=1;

    fillTheArea(gamePlay);
    do
    {
        printf("\n\nPlayer 1 (x), enter your move (row, col) : ");
        scanf(" %d %d",&row,&col);
        count =1;

        gameArena(gamePlay,row,col,count);
        gameCheck=winCheck(gamePlay);

        if(gameCheck){
            
            printf("\n\nPlayer 2 (0), enter your move (row, col) : ");
            scanf(" %d %d",&row,&col);
            count =0;
            gameArena(gamePlay,row,col,count);
            gameCheck=winCheck(gamePlay);

            if(!gameCheck){
                
                printf("If you want to play again press 1..");
                scanf("%d",&gameCheck);
                if (gameCheck==1)
                {
                    fillTheArea(gamePlay);
                }

                else{
                    printf("You logged out of game see you soon...");
                }
            }
        }
        else{
            
            printf("If you want to play again press 1..");
            scanf("%d",&gameCheck);
            if (gameCheck==1)
            {
               fillTheArea(gamePlay);
            }

            else{
                printf("You logged out of game see you soon...");
            }
        }
    } while (gameCheck==1);
    
    return 0;
}





