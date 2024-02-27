#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define up 'w' 
#define down 's'
#define right 'd' 
#define left 'a' 



int startGame(){
    
    printf("\n");
    srand(time(NULL));  // for the take random number every time
    int y_axis,x_axis;
    int count=0;
    int move_count=0;
    int options;
    char operation;

    
    do
    {          
        printf("Enter y axis of game (you cannot specify a size smaller than 5 or greater than 10.) : ");
        scanf("%d",&y_axis);                                                                                // taking y axis
        printf("Enter x axis of game (you cannot specify a size smaller than 5 or greater than 10.) : ");   // taking x axis
        scanf("%d",&x_axis);                                                                                
        printf("\n");
        if(y_axis<5 || y_axis>10 || x_axis<5 || x_axis>10){ // controlling size of the room if size is not betwwen 5-10
            printf("\nInvalid input please enter again  \n\n");
            count++;
        }
        else{
            count=0;  // if not
        }

    } while (count>0);

    int game=1;
    int num1 = rand() % y_axis;
    int num2 = rand() % x_axis;
    int x=rand() % y_axis;
    int y=rand() % x_axis;
    

    do  // printing game room
    {   

        for (int i = 0; i <= x_axis; i++)
        {
            printf("- ");       // printing top of the game with the x
        }
        
        printf("\n");

        for (int i = 0; i < y_axis; i++)
        {
            for (int j = 0; j <=x_axis; j++)
            {
                printf("|");

                if(i==x && j==y ){
                    printf("C"); // printing cordinant of c first place is random
                
                }

                else if(i==num1 && j==num2){
                    printf("D"); //printing cordinant of D first place is random
                }
            
                else{
                    printf(" "); // printing whitspace 
                }
            

                if (x==num1 && y==num2) // if the cordinant of the door and chracter is same chracter exit and win
                {   
                    printf("You Reach The Door Congrulations Game Over...\n\n");
                    printf("You Made %d Move\n\n",move_count);
                    return 1;
                }

            }       
            printf("\n");
        
        }
        for (int i = 0; i <= x_axis; i++)
        {
            printf("- ");        // printing bottom of the game with the x
        }
         printf("\n");

  

        
        printf("\n\nEnter your move for up ""W"", for down ""S"", for right ""D"", for left ""A"" : ");
        scanf(" %c",&operation); // taking move from user
        while (getchar() != '\n');  // clear buffer for the avoid diagonal moves
        printf("\n");
        
        switch(operation) // with move changing corddinant of the chracter
            {
            case up:
                x-=1;
                if(x<0){
                    x+=1;
                    printf("\nWARNİNG!! YOU CANNOT MOVE THE THROUGH THE WALL\n\n");
                    move_count--; // I dont want to count the move when the user try to move the wall
                }
                move_count++;
                break;
        
            case down:
                x+=1;
                if(x>y_axis){
                    x-=1;
                    printf("\nWARNİNG!! YOU CANNOT MOVE THE THROUGH THE WALL\n\n");
                    move_count--; // I dont want to count the move when the user try to move the wall
                }
                move_count++;
                break;
            case right:
                y+=1;
                if(y>x_axis-1){
                    y-=1;
                    printf("\nWARNİNG!! YOU CANNOT MOVE THE THROUGH THE WALL\n\n");
                    move_count--; // I dont want to count the move when the user try to move the wall
                }
                move_count++;
                break;
         
            case left:
                y-=1;
                if(y<0){
                    y+=1;
                    printf("\nWARNİNG!! YOU CANNOT MOVE THE THROUGH THE WALL\n\n");
                    move_count--; // I dont want to count the move when the user try to move the wall
                }
                move_count++;
                break;
        
            default:
                printf("Invalid input please try again\n\n");
                break;
            }
        
       
    } while (game==1); 

}





void help(){        //printing game rules
                    
    printf("\t\t\t\tThe BOOK OF THE GAME");
    printf("\n\n1.The game board consists of a room with walls and a door.\n");
    printf("\n2.The player character is able to move one space in any of the four cardinal directions: up, down, left, and right. Diagonal moves are not allowed.\n");
    printf("\n3.The player inputs their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down\n");
    printf("\n4.The game will prompt the user for a new move after each move is made until the game is over.\n");
    printf("\n5.The current state of the room will be printed after each move, except when the character reaches the door.\n");
    printf("\n6.If the character attempts to move through a wall, a warning message will be displayed.\n");
    printf("\n7.The game ends when the character reaches the door.\n");
    printf("\n8.A message will be displayed to notify the user that the game is over and how many moves were made during the game.\n\n\n");

}



int exitGame(){ // exiting from game
    printf("\n\nYou Logged Out Of The Game See You Soon...\n");
    return 1;
}