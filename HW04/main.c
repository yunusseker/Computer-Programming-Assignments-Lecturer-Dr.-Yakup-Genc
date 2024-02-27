#include <stdio.h>
#include "time.h"
#include <stdlib.h>
#include "util.h"

int main(){

    char ch;
    int skip = 1;
	int count=1;
    FILE *menu = fopen("menu.txt", "r");

    if (menu == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    while (fscanf(menu, "%c", &ch) == 1) {
        if (ch == ' ') {
            while (ch != '\n' && fscanf(menu, "%c", &ch) == 1);
        }
        if (!skip) {
            printf("%c", ch);
        }
        if (ch == '\n' && skip) {
            skip = 0;
            printf("\nYemek Listesi\n\n");
        }
	
	    if(ch == '\n'){
			printf("%d.",count);
			count++;
		}
    }
    fclose(menu);


    
    int dishNumber;
    int servingsNumber;
    float totalPrice;
    char studentCheck;
    float vat;
    float studentDiscount;
    float salesTen;
    char dish;
    time_t t = time(NULL);

 



    FILE *receipt = fopen("receipt.txt", "w");
    fprintf(receipt, "210104004309       %s\n", ctime(&t));
    fprintf(receipt,"------------------------------------------\n");
    fprintf(receipt,"\nProduct\t\t\t\tPrice (TL)\n\n"); 
    fprintf(receipt,"------------------------------------------\n");

   do
   {
   
    printf("\n\nPlease Choose A Product (1-13): ");
    scanf("%d",&dishNumber);
    printf("\nHow Many Servings Do You Want?  ");
    scanf("%d",&servingsNumber); 

    switch (dishNumber)
    {
    case 1:
        if (servingsNumber>1){

            fprintf(receipt, "%d*Kebap\t\t\t\t%.2f\n",servingsNumber,75.99*servingsNumber);
            totalPrice=totalPrice+75.99*servingsNumber;
        }

        else if(servingsNumber==0){
            fprintf(receipt,"Kebap\t\t\t\t75.99\n");
            totalPrice=totalPrice+75.99;
        }
        
        break;
    case 2:
        if (servingsNumber>1){

            fprintf(receipt,"%d*Ciğer\t\t\t\t%.2f\n",servingsNumber,80.55*servingsNumber);
            totalPrice=totalPrice+80.55*servingsNumber;    
        }
        else if(servingsNumber==0){

            fprintf(receipt,"Ciğer\t\t\t\t80.55\n");
            totalPrice=totalPrice+80.55;
            
        }
        
        break;
    case 3:
        if (servingsNumber>1){

            fprintf(receipt,"%d*Levrek\t\t\t%.2f\n",servingsNumber,21.50*servingsNumber);
            totalPrice=totalPrice+21.50*servingsNumber;
        }
        else if(servingsNumber==0){
            fprintf(receipt,"Levrek\t\t\t21.50\n");
            totalPrice=totalPrice+21.50;
        }
            
        break;
    case 4:
        if (servingsNumber>1){
            fprintf(receipt,"%d*Pide\t\t\t\t%.2f\n",servingsNumber,40.70*servingsNumber);
            totalPrice=totalPrice+40.70*servingsNumber;
        }

        else if(servingsNumber==0){
            
            fprintf(receipt,"Pide\t\t\t\t40.00");
            totalPrice=totalPrice+40.70;
        }
        break;
    case 5:
        if (servingsNumber>1){
            fprintf(receipt,"%d*Büryan\t\t\t\t%.2f\n",servingsNumber,95.90*servingsNumber);
            totalPrice=totalPrice+95.90*servingsNumber;
        }
        else if(servingsNumber==0){
            fprintf(receipt,"Büryan\t\t\t\t95.90");servingsNumber=1;
            totalPrice=totalPrice+95.90;
        }

        break;
    case 6:
        if (servingsNumber>1){
            fprintf(receipt,"%d*Döner\t\t\t\t%.2f\n",servingsNumber,55.60*servingsNumber);
            totalPrice=totalPrice+55.60*servingsNumber;
        }

        else if(servingsNumber==0){

            fprintf(receipt,"Döner\t\t\t\t55.60\n");
            totalPrice=totalPrice+55.60;
        }
        
        break;
    case 7:
        if (servingsNumber>1){
            fprintf(receipt,"%d*Kola\t\t\t\t%.2f\n",servingsNumber,15.20*servingsNumber);
            totalPrice=totalPrice+15.00*servingsNumber;
        }
        else if(servingsNumber==0){
            fprintf(receipt,"Kola\t\t\t\t15.20");;
            totalPrice=totalPrice+15.20;
        }
        
        break;
    case 8:
        if (servingsNumber>1){
            
            fprintf(receipt,"%d*Su\t\t\t\t%.2f\n",servingsNumber,10.60*servingsNumber);
            totalPrice=totalPrice+10.60*servingsNumber;
        }
        else if(servingsNumber==0){
            fprintf(receipt,"Su\t\t\t\t10.60\n");
            totalPrice=totalPrice+10.60;
        }
        break;
    case 9:
        if (servingsNumber>1){

            fprintf(receipt,"%d*Gazoz\t\t\t\t%.2f\n",servingsNumber,15.50*servingsNumber);
            totalPrice=totalPrice+15.50*servingsNumber;
        }
        else if(servingsNumber==0){
            
            fprintf(receipt,"Gazoz\t\t\t\t15.50");
            totalPrice=totalPrice+15.50;
        }
            
        break;
    case 10:
        if (servingsNumber>1){

            fprintf(receipt,"%d*Limonata\t\t\t%.2fn",servingsNumber,17.50*servingsNumber);
            totalPrice=totalPrice+17.50*servingsNumber;
        }
        else if(servingsNumber==0){
            fprintf(receipt,"Limonata\t\t\t17.50");;
            totalPrice=totalPrice+17.50;
        }
        break;
    default:
        break;
    }
    
   } while (servingsNumber!=0);
    
    

    printf("\nAre you student? (Y/N): ");

    scanf(" %c",&studentCheck);
    
    studentDiscount=totalPrice*0.125;
    salesTen=totalPrice*0.10;
    

    fprintf(receipt, "\n\n\nTotal :\t\t\t\t%.2f\n",totalPrice);
    if(studentCheck=='y' || studentCheck=='Y' && totalPrice>150){
        totalPrice= totalPrice - (totalPrice*0.125+totalPrice*0.1);
        fprintf(receipt, "Student Discount:\t\t%.2f\n",studentDiscount);
        fprintf(receipt, "%%10 Discount:\t\t\t%.2f\n",salesTen);  
        
    }
    
    else if(studentCheck=='y' || studentCheck=='Y' && totalPrice<150){
        totalPrice=totalPrice-(totalPrice*0.125);
        fprintf(receipt, "Student Discount:\t\t%.2f\n",studentDiscount);
    }
    else if(studentCheck!='y' || studentCheck!='Y' && totalPrice>150){
        totalPrice=totalPrice-(totalPrice*0.1);
        fprintf(receipt, "%%10 Discount:\t\t\t%.2f\n",salesTen);  
    }

    fprintf(receipt,"\n------------------------------------------\n");

    fprintf(receipt,"Price:\t\t\t\t%.2f\n",totalPrice); 
    vat=totalPrice*0.18;
    fprintf(receipt,"Price + VAT:\t\t\t%.2f\n",(totalPrice+vat));;
   
    fclose(receipt);

    receipt = fopen("receipt.txt", "r");
    printf("\n\n");
    
    
    printf("\n\n");

    while(! feof(receipt) ){
        putchar(fgetc(receipt));
    }

    fclose(receipt);


    printf("\n\n~~~~~~~~~~~~~~~~Stone-Paper-Scissors~~~~~~~~~~~~~~~~\n\n");
    
    srand(time(0));
    char gamePlay;
    int userChoice;
    int computerChoice=rand() % 3 +1;
    int controlValue;
 

   do
    {   printf("\nPlease Make A Choice! \n\n");
        printf("1: Stone, 2: Paper, 3: Scissors\n\n");
        scanf("%d",&userChoice);
        if(userChoice==1 && computerChoice==1){
            printf("You chose Stone. I chose Stone. It's a tie!");
        }
        else if(userChoice==1 && computerChoice==2){
            printf("You chose Stone. I chose Paper. I won!");
        }
        else if(userChoice==1 && computerChoice==3){
            printf("You chose Stone. I chose Scissors. You won!");
        }
        else if(userChoice==2 && computerChoice==1){
            printf("You chose Paper. I chose Stone. I won!");
        }
        else if(userChoice==2 && computerChoice==2){
            printf("You chose Paper. I chose Paper. It's a tie!");
        }
        else if(userChoice==2 && computerChoice==3){
            printf("You chose Paper. I chose Scissors. I won!");
        }
        else if(userChoice==3 && computerChoice==1){
            printf("You chose Scissors. I chose Stone. I won!");
        }
        else if(userChoice==3 && computerChoice==2){
            printf("You chose Scissors. I chose Paper. you won!");
        }
        else if(userChoice==3 && computerChoice==3){
            printf("You chose Scissors. I chose Scissors. It's a tie!");
        }

        printf("\n\nDo you want to play again (Y/N): ");
        scanf(" %c",&gamePlay);
        if (gamePlay=='Y' || gamePlay=='y'|| gamePlay=='n' || gamePlay=='N')
        {   
        }
        
        else{
            printf("\n\nInvalid Input Try Again!!");
        }

    } while (gamePlay=='Y' || gamePlay=='y');
    
}
