#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <math.h>

int letterFrequencyProblem(char fileName[20]){

    FILE *file =fopen(fileName,"r"); 
    char ch;
    
    int alphabet[26];


    for (int i = 0; i < 26; i++)
    {   
        alphabet[i]=0;
        
    }
    
    while (!feof(file)) 
    {
        fscanf(file,"%c",&ch);

        if(ch>=97 && ch<=122){ // controlling ascii code of the chrahcters if its same decreasing  array
            
            alphabet[ch-97]++;
        }

        else if(ch>=65 && ch<=90){
            
            alphabet[ch-65]++;
        }
    
    }

    fclose(file);

    for(int i=65;i<91;i++){
        printf("%c : %d\n",i,alphabet[i-65]);
    }

}

// A function named "distance" is defined, which calculates the Euclidean distance between two points in three-dimensional space.
double MeasureDistance(double x1, double y1, double z1, double x2, double y2, double z2){
    
    double distance = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2) + pow((z2 - z1),2));
    return distance;
}

//The "colorMixer" function is defined to take two colors and a function pointer as arguments and return the result of the function pointer applied to the two colors.
int colMix(Color color1, Color color2, int (*mixer)(Color, Color)){
    return mixer(color1, color2);  
}

int mixerColors(Color color1, Color color2){
    
    double firstColorVectors[3]; 
    double secondColorVectors[3]; 
    double mixedColor[3];
    
    for (int i = 0; i < 3; i++)
    {   
        firstColorVectors[i]=0;
        secondColorVectors[i]=0;
    }
    
    switch (color1) // filling the arrays which given values
    {
    case RED:
        firstColorVectors[0]=1;
        break;
    case GREEN:
        firstColorVectors[1]=1;
        break;
    case BLUE:
        firstColorVectors[2]=1;
        break;
    case YELLOW:
        firstColorVectors[0]=0.5;
        firstColorVectors[1]=0.5;
        break;
    case ORANGE:
        firstColorVectors[0]=0.5;
        firstColorVectors[1]=0.4;
        firstColorVectors[2]=0.2;
        break;
    default:
        break;
    }

switch (color2) // filling the arrays which given values
    {
    case RED:
        firstColorVectors[0]=1;
        break;
    case GREEN:
        firstColorVectors[1]=1;
        break;
    case BLUE:
        firstColorVectors[2]=1;
        break;
    case YELLOW:
        firstColorVectors[0]=0.5;
        firstColorVectors[1]=0.5;
        break;
    case ORANGE:
        firstColorVectors[0]=0.5;
        firstColorVectors[1]=0.4;
        firstColorVectors[2]=0.2;
        break;
    default:
        break;
    }
    
    for (int i = 0; i < 3; i++)
    {   
     mixedColor[i]=((firstColorVectors[i]+secondColorVectors[i])/2);
    }

    //sending value func to calculate distance
    double distanceBetweenRed = MeasureDistance(mixedColor[0], mixedColor[1], mixedColor[2], 1, 0, 0);
    double distanceBetweenGreen = MeasureDistance(mixedColor[0], mixedColor[1], mixedColor[2], 0, 1, 0);
    double distanceBetweenBlue = MeasureDistance(mixedColor[0], mixedColor[1], mixedColor[2], 0, 0, 1);
    double distanceBetweenYellow = MeasureDistance(mixedColor[0], mixedColor[1], mixedColor[2], 0.5, 0.5, 0);
    double ddistanceBetweenOrange = MeasureDistance(mixedColor[0], mixedColor[1], mixedColor[2], 0.5, 0.4, 0.2);

    
    //controlling distance
    double min_dist = distanceBetweenRed;
    Color mixed_color = RED;
    if(distanceBetweenGreen < min_dist){
        min_dist = distanceBetweenGreen;
        mixed_color = GREEN;
    }
    
    if(distanceBetweenBlue< min_dist){
    min_dist = distanceBetweenBlue;
    mixed_color = BLUE;
    }
    if(distanceBetweenYellow< min_dist){
        min_dist = distanceBetweenYellow;
        mixed_color = YELLOW;
    }
    if(ddistanceBetweenOrange < min_dist){
        min_dist = ddistanceBetweenOrange;
        mixed_color = ORANGE;
    }

    printf("Mixed Color: ");
    switch(mixed_color){
        case RED:
            printf("RED ");
            break;
        case GREEN:
            printf("GREEN ");
            break;
        case BLUE:
            printf("BLUE ");
            break;
        case YELLOW:
            printf("YELLOW ");
            break;
        case ORANGE:
            printf("ORANGE ");
            break;
    }
    printf("[%0.1f, %0.1f, %0.1f]\n", mixedColor[0], mixedColor[1], mixedColor[2]);
    
    return mixed_color;

}

void gameArena(char gamePlay[3][3],int row,int col,int count){
    int check=1;

    if(gamePlay[row][col]=='X' || gamePlay[row][col]=='O'){
        printf("\nInvalid move this place is full!!\n");
        check=0; // if the place is full with the x or o warning user that this place is full
    }

    for (int i = 0; i < 3; i++)
        {  
            for (int j = 0; j < 3; j++)
            {   
                if(i==row && j==col){
                    if(!check){
                    }

                    else if(count){
                        gamePlay[i][j]='X'; // filling cordinant with user input
                        
                    }
                    else if(!count){
                        gamePlay[i][j]='O';
                        
                    }
                }
                printf(" %c",gamePlay[i][j]); //printing line
                         
            }
            printf("\n");
        }
}


void fillTheArea(char gamePlay[3][3]){
    for (int i = 0; i < 3; i++) //creating the game area
    {
        for (int j = 0; j < 3; j++){   

            gamePlay[i][j]='_'; // filling game area
            
        }   
       
    }
    
}


int winCheck(char gameplay[3][3]){

    if(gameplay[0][0]=='X' && gameplay[1][0]=='X' && gameplay[2][0]=='X' || gameplay[0][1]=='X' && gameplay[1][1]=='X' && gameplay[2][1]=='X' || gameplay[0][2]=='X' && gameplay[1][2]=='X' && gameplay[2][2]=='X' || gameplay[0][0]=='X' && gameplay[0][1]=='X' && gameplay[0][2]=='X' || gameplay[1][0]=='X' && gameplay[1][1]=='X' && gameplay[1][2]=='X' || gameplay[2][0]=='X' && gameplay[2][1]=='X' && gameplay[2][2]=='X'){
        printf("\nPlayer one (x) wins..\n\n");
        return 0;
        // controlling every probbality coordinates that user can win after each move 
    }

    else if(gameplay[0][0]=='O' && gameplay[1][0]=='O' && gameplay[2][0]=='O' || gameplay[0][1]=='O' && gameplay[1][1]=='O' && gameplay[2][1]=='O' || gameplay[0][2]=='O' && gameplay[1][2]=='O' && gameplay[2][2]=='O' || gameplay[0][0]=='O' && gameplay[0][1]=='O' && gameplay[0][2]=='O' || gameplay[1][0]=='O' && gameplay[1][1]=='O' && gameplay[1][2]=='O' || gameplay[2][0]=='O' && gameplay[2][1]=='O' && gameplay[2][2]=='O'){
        printf("\nPlayer two (O) wins..\n\n");
        return 0;
        // controlling every probbality coordinates that user can win after each move 
    }
    

    else if((gameplay[0][0]=='O' || gameplay[0][0]=='X') && (gameplay[1][0]=='O' || gameplay[1][0]=='X') && (gameplay[2][0]=='O' || gameplay[2][0]=='X')&& (gameplay[0][1]=='O' || gameplay[0][1]=='X') && (gameplay[1][1]=='O' || gameplay[1][1]=='X') && (gameplay[2][1]=='O' || gameplay[2][1]=='X') && (gameplay[0][2]=='O' || gameplay[0][2]=='X') && (gameplay[1][2]=='O' || gameplay[1][2]=='X') && (gameplay[2][2]=='O' || gameplay[2][2]=='X')){
        printf("\nGAME IS  OVER EVERY CORDINANT IS FULL...\n\n");
        return 0;
        // controlling every  coordinates if its full 
    }
    
    else{
        return 1;
    }
}
