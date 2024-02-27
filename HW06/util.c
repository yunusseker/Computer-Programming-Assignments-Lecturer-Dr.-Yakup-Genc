#include <stdio.h>
#include <stdlib.h>

void mainMenu();
int mainOperation();
void fileOperationMenu();
int fileOperation();
int addNewProduct();
int updateProduct();
int deleteProduct();
int addFeautureToProduct();
int addStockEntry();
int deleteStockEntry();
int updateStockEntry();
int backToMenu();
int queryProduct();
void queryMenu();
int listAllProduct();
int listProductsByFeature();
int exportReport(double product[100][3]);
int brandStockControl();
int queryStockByBranchProduct();
int checkStockStatus();
int myStrcmp(const char* str1, const char* str2);
int listTheStockByBranch();
int listTheStockByBranch();
int listOutOfStockProductsByBranch();


void mainMenu(){
    printf("1- Fıle Operations\n");
    printf("2- Query Products\n");
    printf("3- Check Stock Status\n");
    printf("4- Stock Control By Brand\n");
    printf("5- Export Report\n\n");  
}

int mainOperation(){
    int operation;
    mainMenu(); 
    scanf("%d",&operation);

    do
    {   if(operation<0 || operation>6){
            printf("\nInvalid Input Please Try Again!!\n\n");
            mainMenu();
            scanf("%d",&operation);
        }

    } while (operation<0 || operation>6);

    switch (operation)
    {
    case 1:
        fileOperation();
        break;
    case 2:
        queryProduct();
        break;
    case 3:
        checkStockStatus();
        break;
    case 4:
        brandStockControl();
        break;
    case 5:
        
        break;
    case 6:
        break;

    default:
        break;
    }
    return 0;   
}

void fileOperationMenu(){

    printf("1- Add A New Product: \n");
    printf("2- Delete Product: \n");
    printf("3- Update Product: \n");
    printf("4- Add Feature To Products: \n");
    printf("5- Add A New Stock Entry: \n");
    printf("6- Delete A Stock Entry: \n");
    printf("7- Update A Stock Entry\n");
    printf("8- Back To Menu: \n");

}


int fileOperation(){

    int fileOperation;

    fileOperationMenu();

    scanf("%d",&fileOperation);

     do
    {   if(fileOperation<0 || fileOperation>9){
            printf("\nInvalid Input Please Try Again!!\n\n");
            fileOperationMenu();
            scanf("%d",&fileOperation);
        }

    } while (fileOperation<0 || fileOperation>9);


    switch (fileOperation)
    {
    case 1:
        addNewProduct();
        break;
    case 2:
        deleteProduct();
        break;
    case 3:
        updateProduct();
        break;
    case 4:
        addFeautureToProduct();
        break;
    case 5:
        addStockEntry();
        break;
    case 6:
        deleteStockEntry();
        break;
    case 7:
        updateStockEntry();
        break;
    case 8:
        backToMenu();
        break;
    default:
        break;
    }

    return 0;
}


int addNewProduct(){
    FILE *productFile;
    productFile = fopen("product.txt","r");
    char ch;
    int  pID=1;
    while (fscanf(productFile,"%c",&ch)==1)
    {
        if (ch=='\n')
        {
            pID+=1;
        }
    }
    
    fclose(productFile);
    char type;
    char name[9];
    char brand[6];
    double price;

    productFile = fopen("product.txt","a");
    printf("Enter The Type Of Product: ");
    scanf(" %c",&type);
    printf("Enter The Name of Product: ");
    scanf(" %s",&name);
    printf("Enter The brand of Product: ");
    scanf(" %s",&brand);
    printf("Enter The price of Product: ");
    scanf("%lf",&price);

    fprintf(productFile,"\n%d,%c,%s,%s,%.2lf",pID,type,name,brand,price);
    fclose(productFile);
    fileOperation();
    
    return 0;
}


int deleteProduct(){

    int pID;
    int pIDControl=0;
    char ch;
    int lineCounter=0;
    int control=1;

    FILE *original = fopen("product.txt","r");
    FILE *copy =fopen("temp.txt","w");

    
    while (fscanf(original,"%c",&ch)!=EOF)
    {
        if (ch=='\n')
        {
            pIDControl++;
        }  
    }
    do
    {   printf("\nEnter The Product ID That You Want To Delete : ");
        scanf("%d",&pID);

        if(pID>pIDControl){

            printf("\nThere Is Not Product with %d pID number Try Again \n",pID);

        }
       
    } while (pID>pIDControl);

    rewind(original);

    while (fscanf(original,"%c",&ch)!=EOF)
    {
        if (ch=='\n')
        {
            lineCounter++;
        }

        if (lineCounter==pID && control)
        {   
            fprintf(copy,"%c",ch);
            while (fscanf(original,"%c",&ch) != EOF && ch != '\n'){}          
            fscanf(original,"%c",&ch);
            control=0;
        }
        
       fprintf(copy,"%c",ch);
    }    
    
    remove("product.txt");
    rename("temp.txt","product.txt");

    fclose(original);
    fclose(copy);
    fileOperation();
    return 0;

}

int updateProduct(){
    char ch;
    int feautureNumber=0;
    int pID;
    char new_value[5];
    int commaControl=0;
    int columnNum;
    int skip=1;
    int lineControl=0;

    FILE *original = fopen("product.txt","r");
    FILE *copy=fopen("temp.txt","w");

    printf("Enter The pID Of Product That You Want To Update : ");
    scanf("%d",&pID);

    while (fscanf(original,"%c",&ch) != EOF && ch != '\n')
    {   
        if (ch == ',' )
        {             
            feautureNumber++;
            
            
        }
        
        printf("%c",ch);
        if (ch == ',' )
        {             
            printf("%d.",feautureNumber);    
        }
      
    }
    printf("\nEnter The Column Number That You Want To Change There is %d Column : (You cannot Change PID Number Starting From Type)",feautureNumber);
    scanf("%d",&columnNum);
    printf("\nEnter The New Value : ");
    scanf("%s",&new_value);
    rewind(original);
    while (fscanf(original,"%c",&ch) != EOF)
    {
        if (ch == '\n')
        {   
            lineControl++;
        }

        if (lineControl==pID)
        {   fprintf(copy,"%c",ch);
            while (fscanf(original,"%c",&ch) != EOF && ch != '\n'){

                if(ch==','){
                    commaControl++;
                }

                if(commaControl==columnNum && skip){
                    fprintf(copy,"%c",ch);
                    fprintf(copy,"%s",new_value);
                    skip=0;
                }

                else if(commaControl!=columnNum){
                    fprintf(copy,"%c",ch);
                }
            }
        }
        fprintf(copy,"%c",ch);
        
    }  
  
    fclose(original);
    fclose(copy);

    remove("product.txt");
    rename("temp.txt","product.txt");
    fileOperation();

    return 0;
}

int addFeautureToProduct(){

    char ch;
    int commaCounter=0;
    char newFeature[9];
    int commaControl=0;
    int fillFeatureCont=1;

    FILE *original =fopen("product.txt","r");
    FILE *copy=fopen("temp.txt","w");

    printf("Enter The New Feature Name To Column (warning feauture name maximum size can be 8 chrachter) : ");
    scanf("%s",&newFeature);

    while (fscanf(original,"%c",&ch) != EOF && ch != '\n')
    {   
        if (ch == ',' )
        {
            commaControl++;
        }
    }
    rewind(original);
    while (fscanf(original,"%c",&ch)!=EOF)
    {
        if(ch == ','){
            commaCounter+=1;
        }

        if(commaCounter==commaControl && fillFeatureCont){
            fprintf(copy,"%c",ch);
            fprintf(copy,"%s",newFeature);
            commaCounter=0;
            fillFeatureCont=0;
        }

        else if(commaCounter==commaControl && !fillFeatureCont){
            fprintf(copy,"%c",ch);
            fprintf(copy,"NONE");
            commaCounter=0;
        }

        fprintf(copy,"%c",ch);
    }

    fclose(original);
    fclose(copy);

    remove("product.txt");
    rename("temp.txt","product.txt");
    fileOperation();

    return 0;
}

int addStockEntry(){
    int sID=1;
    int pID;
    int pIDControl=1;
    char branch[16];
    int currentStock;
    char c1,c2;

    FILE *product =fopen("product.txt","r");
    FILE *stock =fopen("stock.txt","r");

    while (fscanf(product,"%c",&c1)!=EOF)
    {
        if(c1=='\n'){
            pIDControl++;
        }
    }

    while (fscanf(stock,"%c",&c2)!=EOF)
    {
        if(c2=='\n'){
            sID+=1;
        }
    }

    fclose(product);
    fclose(stock);
    stock =fopen("stock.txt","a");

    do
    {       
        printf("\nEnter The pID Of The Product That You Want To Stock Of It : ");
        scanf("%d",&pID);
            
        if (pID>pIDControl)
        {
            printf("\nThere Is Not Product with %d pID number Try Again \n",pID);
        }
            
     } while (pID>pIDControl);

    printf("\nEnter The Branch, Name Of The City Where The Branch Is Located : ");
    scanf("%s",&branch);
    printf("\nEnter The Current Stock Of The Product : ");
    scanf("%d",&currentStock);


    fprintf(stock,"\n%d,%d,%s,%d",sID,pID,branch,currentStock);
    fclose(stock);
    fileOperation();

    return 0;
}




int deleteStockEntry(){

    int sID;
    int sIDControl=0;
    char ch;
    int lineCounter=0;
    int control=1;

    FILE *original = fopen("stock.txt","r");
    FILE *copy =fopen("temp.txt","w");

    
    while (fscanf(original,"%c",&ch)!=EOF)
    {
        if (ch=='\n')
        {
            sIDControl++;
        }  
    }
    do
    {   printf("\nEnter The Stock ID That You Want To Delete : ");
        scanf("%d",&sID);

        if(sID>sIDControl){

            printf("\nThere Is Not Product with %d sID number Try Again \n",sID);

        }
       
    } while (sID>sIDControl);

    rewind(original);

    while (fscanf(original,"%c",&ch)!=EOF)
    {
        if (ch=='\n')
        {
            lineCounter++;
        }

        if (lineCounter==sID && control)
        {   
            fprintf(copy,"%c",ch);
            while (fscanf(original,"%c",&ch) != EOF && ch != '\n'){}          
            fscanf(original,"%c",&ch);
            control=0;
        }
        
       fprintf(copy,"%c",ch);
    }    
    
    remove("stock.txt");
    rename("temp.txt","stock.txt");

    fclose(original);
    fclose(copy);
    fileOperation();
    return 0;
}


int updateStockEntry(){ // counting the comma number and find the location the feature that user want to update
    

    char ch;        
    int feautureNumber=0;
    int pID;
    char new_value[5];
    int commaControl=0;
    int columnNum;
    int skip=1;
    int lineControl=0;

    FILE *original = fopen("stock.txt","r");
    FILE *copy=fopen("temp.txt","w");

    printf("Enter The sID Of The Stock That You Want To Update : ");
    scanf("%d",&pID);

    while (fscanf(original,"%c",&ch) != EOF && ch != '\n')
    {   
        if (ch == ',' )
        {
            feautureNumber++;
        }
        
        printf("%c",ch);
        
        if (ch == ',' )
        {             
            printf("%d.",feautureNumber);    
        }

    }

    printf("\nEnter The Column Number That You Want To Change There is %d Column : ",feautureNumber);
    scanf("%d",&columnNum);
    printf("\nEnter The New Value : ");
    scanf("%s",&new_value);
    
    rewind(original);
    
    while (fscanf(original,"%c",&ch) != EOF)
    {
        if (ch == '\n')
        {   
            lineControl++;
        }

        if (lineControl==pID)
        {   fprintf(copy,"%c",ch);
            while (fscanf(original,"%c",&ch) != EOF && ch != '\n'){

                if(ch==','){
                    commaControl++;
                }

                if(commaControl==columnNum && skip){
                    fprintf(copy,"%c",ch);
                    fprintf(copy,"%s",new_value);
                    skip=0;
                }

                else if(commaControl!=columnNum){
                    fprintf(copy,"%c",ch);
                }
            }
        }
        fprintf(copy,"%c",ch);
        
    }  

  
    fclose(original);
    fclose(copy);

    remove("stock.txt");
    rename("temp.txt","stock.txt");
    fileOperation();

    return 0;
}

int backToMenu(){
    
    mainOperation();

    return 0;
}

void queryMenu(){
    printf("1-List All Products\n");
    printf("2-Filter products by Feature\n");
    printf("3-Back To Main Menu\n");
}


int queryProduct(){

    int operation;
    queryMenu();
    scanf("%d",&operation); 
    do
    {   if(operation<0 || operation>4){
            printf("\nInvalid Input Please Try Again!!\n\n");
            queryMenu();
            scanf("%d",&operation);
        }

    } while (operation<0 || operation>4);


    switch (operation)
    {
    case 1:
        listAllProduct();
        break;
    case 2:
        listProductsByFeature();
        break;
    case 3:
        printf("\n");
        fileOperation();
        break;
    default:
        break;
    }
    return 0;
}


int listAllProduct(){
    printf("\n");
    char ch;
    FILE *product=fopen("product.txt","r");

    while (fscanf(product,"%c",&ch)==1)
    {
        printf("%c",ch);
    }
    queryProduct();
    return 0;
}


int listProductsByFeature(){

    int filterNum;
    int feautureNumber;
    char ch;
    double price;
    char name[9];
    char brand[6];
    char type;
    char feature[6];
    char userInput[100];
    

    printf("Enter The Feature Name And Feature (You Can Filter More Than One Feature..) : ");
    scanf("%s",userInput);
  
    FILE *original = fopen("product.txt","r");
    queryProduct();
    return 0;
}


void StockStatusMenu(){
    printf("\n1-Query The Stock Of Given Product In a Specified Branch By Using The Product ID And Branch Name");
    printf("\n2-List The Stock Of all Products In a Specified Branch");
    printf("\n3-List The Out Of Stock Product");
    printf("\n4-Back To The Main Menu");
}

int checkStockStatus(){
    int operation;
    StockStatusMenu();
    scanf("%d",&operation);

     do
    {   if(operation<0 || operation>5){
            printf("\nInvalid Input Please Try Again!!\n\n");
            StockStatusMenu();
            scanf("%d",&operation);
        }

    } while (operation<0 || operation>5);

    switch (operation)
    {
    case 1:
        queryStockByBranchProduct();
        break;
    case 2:
        listTheStockByBranch();
        break;
    case 3:
        listOutOfStockProductsByBranch();
        break;
    case 4:
        mainOperation();
        break;
    default:
        break;
    }
    return 0;
}

int queryStockByBranchProduct(){

    int pID;
    int userpID;
    char branch[15];
    char userBranch[15];
    char ch;
    int sID;
    int product[1][2];
    int currentStock;

    FILE *stock = fopen("stock.txt","r");

    printf("Enter The Product ID : ");
    scanf("%d",&userpID);
    printf("Enter The Branch Name : ");
    scanf("%s",userBranch);

    while (fscanf(stock,"%c",&ch) != EOF && ch != '\n');
    
    while (fscanf(stock,"%d,%d,%[^,],%d",&sID,&pID,branch,&currentStock)==4)
    {
        if(myStrcmp(userBranch,branch)==0 && pID==userpID){
            product[0][0]=sID;
            product[0][1]=currentStock;
        }

    }
    
    printf("\nStock ID : %d",product[0][0]);
    printf("\nCurrent Stock : %d",product[0][1]);
    fclose(stock);
    printf("\n");
    checkStockStatus();
    return 0;
}

int listTheStockByBranch(){

    int pID;
    char branch[15];
    char userBranch[15];
    char ch;
    int sID;
    int product[100][2];
    int currentStock;
    int i=0;

    FILE *stock = fopen("stock.txt","r");

    printf("Enter The Branch Name : ");
    scanf("%s",userBranch);

    while (fscanf(stock,"%c",&ch) == 1 && ch != '\n'); // skip first line
    while (fscanf(stock,"%d,%d,%[^,],%d",&sID,&pID,branch,&currentStock)==4)
    {
        if(myStrcmp(userBranch,branch)==0){  // controlling if branch is same with the user entered branch name
            
            product[i][0]=pID; // if its same taking pID values  and current stock values from text file
            product[i][1]=currentStock;
            i++;
        }

    }

    printf("Stocks For %s Branch \n ",userBranch);
    for (int j = 0; j < i; j++)
    {
        printf("\nStock ID : %d",product[j][0]); // printing the values
        printf("\nCurrent Stock : %d",product[j][1]);
        printf("\n");
    }
    fclose(stock);
    printf("\n");
    checkStockStatus();
    return 0;

}

int listOutOfStockProductsByBranch(){

    int pID;
    int userpID;
    char branch[15];
    char userBranch[15];
    char ch;
    int sID;
    int product[1000][3];
    int currentStock;
    int i=0;

    FILE *stock = fopen("stock.txt","r");

    printf("Enter The Branch Name : "); 
    scanf("%s",userBranch);

    while (fscanf(stock,"%c",&ch) != EOF && ch != '\n');
    
    while (fscanf(stock,"%d,%d,%[^,],%d",&sID,&pID,branch,&currentStock)==4)
    {
        if(currentStock==0 && myStrcmp(userBranch,branch)==0){ // if the user entered branch name is same with in the text file and currents stock is 0 so taking the value in array
            product[i][0]=sID;
            product[i][1]=pID;
            product[i][2]=currentStock;
            i++;
        }

    }


   if (i!=0)
   {
        printf("\nProducts That Out Of Stock In %s Branch  \n",userBranch);
        for (int j = 0; j < i; j++)
        {
            printf("\nStock ID : %d",product[j][0]);    // printing the that values
            printf("\nProduct ID : %d",product[j][1]);
            printf("\nCurrent Stock : %d",product[j][2]);
            printf("\n");
        }
   }

   else{

    printf("\nThere Are No Out Of Stock Product With %s Name \n",userBranch);

   }
   
    
    fclose(stock);
    printf("\n"); 
    checkStockStatus();
    return 0;
}

int brandStockControl(){
    
    double products[100][3];
    char brand[6];
    char ch;
    int pID;
    int feautureNumber=1;
    double price;
    char userBrand[6];
    char c;
    int currentStock;
    int stockFeatureCounter=1;
    int i = 0;
    int brandControl=0;
    int stockPıdCont;
    int cont;

    printf("Enter The Brand Name (you cannot use upper case!!) : ");
    scanf("%s",userBrand);
    FILE *product =fopen("product.txt","r");
    FILE *stock =fopen("stock.txt","r");
    while (fscanf(product,"%c",&ch) != EOF && ch != '\n')
    {   
        if (ch == ',' )     //counting the feature number
        {
            feautureNumber++;
        }
    }
    cont=feautureNumber;
    cont-=1;
    feautureNumber=1;
    fscanf(product,"%d",&pID);
    while (fscanf(product,"%c",&ch) != EOF)
    {
        if (ch==',')
        {
            feautureNumber++;
        }
        if(ch=='\n'){
            fscanf(product,"%d",&pID); // taking product ID
        }
        if (feautureNumber==cont)
        {
            
           
            fscanf(product,"%6[^,]",brand); // Taking brand name
            
        }
        if(feautureNumber==cont+1){ 
            fscanf(product,"%lf",&price); // taking price
            if (myStrcmp(brand,userBrand)==0)
            {   
                brandControl=1;
                while (fscanf(stock,"%c",&c) != EOF && c != '\n');
                while (fscanf(stock,"%c",&c) != EOF ){
                    if (c==',')
                    {
                        stockFeatureCounter++; // counting the commas
                    }

                    if (stockFeatureCounter==2)
                    {
                        fscanf(stock,"%d",&stockPıdCont);

                    }

                    if (stockFeatureCounter==4) // if int he stock column 
                    {
                        if (stockPıdCont==pID) // if the stock id same take the values
                        {
                            fscanf(stock,"%d",&currentStock);
                            products[i][0]=pID;
                            products[i][1]=price;
                            products[i][2]=currentStock;
                            i++;                   
                        }
                        stockFeatureCounter = 1;                     
                    }                                
                }
                rewind(stock);  
            }
            feautureNumber=1; 
        }
    } 
   
   if (!brandControl)
   {
        printf("There Is No Brand with %s Name",userBrand);
   }

   else
   {
        printf("PID-PRICE-STOCK\n");
        
        for (int j = 0; j<i; j++)
        {   
            printf("%0.lf  ",products[j][0]);
            printf("%.2lf  ",products[j][1]);
            printf("%0.lf",products[j][2]);
            printf("\n"); 
        }
    
   }
   
    fclose(stock);
    fclose(product);
    mainOperation();
    return 0;
}

int exportReport(double product[100][3]){


    return 0;
}

int myStrcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}












