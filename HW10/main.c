#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TITLE_SIZE 35
#define MAX_AUTHOR_SIZE 20
#define MAX_ISBN 14
#define BOOK_FILE "book.txt"
#define STUDENT_FILE "student.txt"

typedef struct book {
    char *isbn;
    char *title;
    char *author;
    int publication_year;
    bool reserved_status;
    struct book *next; 
} book_t;


typedef struct student{

    char *student_name;
    int student_id;
    struct book *borrowedBooks;
    struct student *next;
   
}student_t;

void readDataFFile();
void print();
void menu();
void WriteLLToFile();
void addBook(char* isbn, char* title, char* author, int publicationYear, int method);
int deleteBook(char* isbn);
void updateBook(char* isbn, char* feature, char* value);
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice);
void reverseBookList();
void searchBooks(int searchChoice, char * searchValue);
/* void borrowBook(char* isbn,int tudent_id);
void returnBook(char* isbn,int student_id); */
void countNodes();
book_t *newNode(char *isbn, char *title, char *author, int publication_year, bool reserved_status);
void swap(book_t *a, book_t *b);

book_t *head = NULL;
book_t *tail = NULL;

student_t *s_head=NULL;
student_t *s_tail=NULL;



 
void menu();

int main() {

    int operation,publicationYear,method,filterChoice,sortChoice,searchChoice,studentID;
    char *isbn,*title,*author,*value,*filter,*feature,*searchValue;
    
    printf("\nWelcome To The Library Book Management System\n");

    readDataFFile(); 
  
    do {
        menu();
        scanf("%d", &operation);
        if (operation < 0 || operation > 9) {
            printf("\nInvalid Input. Please Try Again!\n\n");
            menu();
            scanf("%d", &operation);
        } 
        else {
            if (operation==1){

                printf("\nWelcome To Add Book System\n");
                printf("Please Enter The ISBN Number Of The Book To Be Added\n");
                isbn=(char*)malloc(sizeof(char)*MAX_ISBN);
                scanf(" %s",isbn);
                printf("Please Enter The Title Of The Book To Be Added\n");
                title=(char*)malloc(sizeof(char)*MAX_TITLE_SIZE);
                scanf(" %[^\n]%*c",title);
                printf("Please Enter The Author Of The Book To Be Added\n");
                author=(char*)malloc(sizeof(char)*MAX_AUTHOR_SIZE);
                scanf(" %[^\n]%*c",author);

                printf("Please Enter The Publication Year Of The Book To Be Added\n");
                scanf("%d",&publicationYear);
                
                do
                {
                    printf("Please Choose The Book Management Method 0 for FIFO, 1 for LIFO\n");
                    scanf("%d",&method);
                    if(method!=1 && method!=0){
                        printf("Invalid Ouput Try Again ! ");
                    }      
                } while (method!=1 && method!=0);
                
                addBook(isbn,title,author,publicationYear,method);

            }

            else if(operation==2){
                printf("Welcome To Delete Book System\n");
                printf("Please Enter The ISBN Number Of The Book To Be Deleted\n");
                isbn=(char*)malloc(sizeof(char)*15);
                scanf("%s",isbn);
                deleteBook(isbn);
                WriteLLToFile();
            }

            else if(operation==3){

                printf("Welcome To Update Book System\n");

                printf("Please Enter The ISBN Number Of The Book To Be Updated\n");
                isbn=(char*)malloc(sizeof(char)*15);
                scanf("%s",isbn);

                printf("Please Enter The Feature Of The Book To Be Updated (title, author, or publication year) USE LOWER CASE!!\n");
                feature=(char*)malloc(sizeof(char)*16);
                scanf(" %[^\n]%*c",feature);

                printf("Please Enter The New Value For The Specified Feature\n");
                value=(char*)malloc(sizeof(char)*20);
                scanf(" %[^\n]%*c",value);
                
                updateBook(isbn,feature,value);
                WriteLLToFile();

            }

            else if(operation==4){

                printf("Welcome To Filter And Sort Book System\n");

                printf("Please Choose Your Choise For Filtering The Books,  0 For Filtering By Author, 1 For Filtering By Publication Year\n");
                scanf("%d",&filterChoice);

                printf("Please Enter The Filter Criteria\n");
                filter=(char*)malloc(sizeof(char)*15);
                scanf(" %[^\n]%*c",filter);

                printf("Please Choose Your Choise For Filtering The Books,  0 Sorting By Title, 1 For Sorting By Author ,2 For Sorting By Publication Year\n");
                scanf("%d",&sortChoice);

                filterAndSortBooks(filterChoice,filter,sortChoice);
            }


            else if(operation==5){
                
                printf("\nWelcome To The Reverse Book List Operation...\n ");
                reverseBookList();
                WriteLLToFile();
            }

            else if(operation==6){


                printf("Welcome To Search Book System\n");

                do
                {
                    printf("Please Choose Your Choise  for searching the books. 0 for searching by ISBN number, 1 for searching by author, 2 for searching by title. \n");
                    scanf("%d",&searchChoice);

                    if(searchChoice<0 && searchChoice>3){
                        printf("Invalid Ouput Try Again ! ");
                    }
                  
                } while (searchChoice<0 && searchChoice>3);

                printf("Please Enter The Filter Criteria\n");
                searchValue=(char*)malloc(sizeof(char)*15);
                scanf(" %[^\n]%*c",searchValue);

                searchBooks(searchChoice,searchValue);


            }

            else if(operation==7){
               /*  printf("\nWelcome To Borrow Books System\n");
                
                printf("\nPlease Enter The ISBN Of Book\n");
                isbn=(char*)malloc(sizeof(char)*15);
                scanf(" %[^\n]%*c",isbn);

                printf("\nPlease Enter Your Student ID\n");
                scanf("%d",&studentID);

                borrowBook(isbn,studentID); */
                
            }

            else if(operation==8){}
            
            
            
            else {
                printf("You Logged Out Of System, Have A Nice Day...");
                exit(0);
            }


        }
    } while (1);

    return 0;
}

void menu() {
    printf("\nPlease Select An Operation...\n");
    printf("1-Add Book\n");
    printf("2-Delete Book\n");
    printf("3-Update Book\n");
    printf("4-Filter and Sort Book\n");
    printf("5-Reverse Book List\n");
    printf("6-Search Books\n");
    printf("7-Borrow Books\n");
    printf("8-Return Books\n");
    printf("0-Exit\n");
    printf("Enter the operation number: ");
}



void addBook(char* isbn, char* title, char* author, int publicationYear, int method){
    
        book_t *new=(book_t *)malloc(sizeof(book_t)); 

        new->isbn = malloc(sizeof(char) * (MAX_ISBN + 1));
        new->title = malloc(sizeof(char) * (MAX_TITLE_SIZE + 1));
        new->author = malloc(sizeof(char) * (MAX_AUTHOR_SIZE + 1));


        if (head==NULL)
        {   
            
            strcpy(new->isbn,isbn);
            strcpy(new->title,title);
            strcpy(new->author,author);
            new->publication_year=publicationYear;
            new->reserved_status=0;
            new->next=NULL;

            head = tail = new;
          
            printf("\nBook is added sucssesfully..\n\n"); 
            print();
           
        }
        
        else{

            
            strcpy(new->isbn,isbn);
            strcpy(new->title,title);
            strcpy(new->author,author);
            new->publication_year=publicationYear;
            new->reserved_status=0;

            if (method==0){

                new->next=NULL;
                tail->next = new;
                tail=new;
                
            }
            else{

                 new->next=head;
                head=new;  
            }

            printf("\nBook is added sucssesfully..\n\n");
            print();

        }

        countNodes();
        WriteLLToFile();        
}

int deleteBook(char* isbn){
    
    book_t *prev = NULL;
    book_t *index = head;


    // linked list is empty

    if(head==NULL){
        printf("There Is Not Book In Library");
        return 1;
    }


    if (!(strcmp(head->isbn,isbn))){
        
        book_t *temp=head;   
        head = head->next;
        free(temp);
        printf("\nThe Book Deleted Succesfully...\n");
        return 1;
    }


    while (index!=NULL && strcmp(index->isbn,isbn))
    {
        prev = index;
        index = index->next;

    }

    if (index==NULL)
    {
        printf("\nThere Is Not Book With ""%s"" ISBN Number\n",isbn);
        return 1;
    }
    

    prev->next = index->next;

    if (!(strcmp(tail->isbn,isbn)))
    {
        tail = prev;
    }

    printf("\nThe Book Deleted Succesfully...\n");
    free(index);

}

void updateBook(char* isbn, char* feature, char* value){

    book_t *new = head;

    while (new!=NULL)
    {
        
        if (!(strcmp(feature,"title"))){   
            
            if (!(strcmp(new->isbn,isbn)))
            {
                strcpy(new->title,value);
                printf("\n%s,%s,%s,%d\n", new->isbn, new->title, new->author, new->publication_year);
                printf("\nThe Book Updated Succesfully...\n");
            }
            
        }

        else if(!(strcmp(feature,"author"))){
            if (!(strcmp(new->isbn,isbn))){
                strcpy(new->author,value);
                printf("\n%s,%s,%s,%d\n", new->isbn, new->title, new->author, new->publication_year);
                printf("\nThe Book Updated Succesfully...\n");
            }
        }

        else if (!(strcmp(feature,"publication year"))){
            if (!(strcmp(new->isbn,isbn))){
                int num = atoi(value); 
                new->publication_year=num;
                printf("\n%s,%s,%s,%d\n", new->isbn, new->title, new->author, new->publication_year);
                printf("\nThe Book Updated Succesfully...\n");
            }
        }

        else{

            printf("You Feature Name Is Not Correct...");
            
        }

        new = new->next;
    
    }
}

void filterAndSortBooks(int filterChoice, char* filter, int sortChoice) {
    book_t *filteredHead = NULL;
    book_t *filteredTail = NULL;
    book_t *temp = head;

    while (temp != NULL) {
        if ((filterChoice == 0 && strcmp(temp->author, filter) == 0) || (filterChoice == 1 && temp->publication_year == atoi(filter))) {
            if (filteredHead == NULL) {
                filteredHead = newNode(temp->isbn, temp->title, temp->author, temp->publication_year, temp->reserved_status);
                filteredTail = filteredHead;
            } else {
                filteredTail->next = newNode(temp->isbn, temp->title, temp->author, temp->publication_year, temp->reserved_status);
                filteredTail = filteredTail->next;
            }
        }
        temp = temp->next;
    }

    int swapped;
    book_t *ptr1;
    book_t *lptr = NULL;

    if (filteredHead != NULL) {
        do {
            swapped = 0;
            ptr1 = filteredHead;

            while (ptr1->next != lptr) {
                if (sortChoice == 0 && strcmp(ptr1->title, ptr1->next->title) > 0) { 
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                } else if (sortChoice == 1 && strcmp(ptr1->author, ptr1->next->author) > 0) {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                } else if (sortChoice == 2 && ptr1->publication_year > ptr1->next->publication_year) {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    printf("\nFiltered and sorted linked list\n");
    
    printf("\nISBN-------TITLE-------AUTHOR-------PUBLICATION_YEAR-------\n");
    while (filteredHead != NULL)
    {   
        
        printf("%s,%s,%s,%d\n", filteredHead->isbn, filteredHead->title, filteredHead->author, filteredHead->publication_year);
        filteredHead = filteredHead->next;

    }

}


book_t *newNode(char *isbn, char *title, char *author, int publication_year, bool reserved_status) {
    book_t *new_node = (book_t*)malloc(sizeof(book_t));
    new_node->isbn = isbn;
    new_node->title = title;
    new_node->author = author;
    new_node->publication_year = publication_year;
    new_node->reserved_status = reserved_status;
    new_node->next = NULL;
    return new_node;
}

void swap(book_t *a, book_t *b) {
    char *temp_isbn = a->isbn;
    char *temp_title = a->title;
    char *temp_author = a->author;
    int temp_publication_year = a->publication_year;
    bool temp_reserved_status = a->reserved_status;

    a->isbn = b->isbn;
    a->title = b->title;
    a->author = b->author;
    a->publication_year = b->publication_year;
    a->reserved_status = b->reserved_status;

    b->isbn = temp_isbn;
    b->title = temp_title;
    b->author = temp_author;
    b->publication_year = temp_publication_year;
    b->reserved_status = temp_reserved_status;
}


void reverseBookList() {
    book_t *prev = NULL;
    book_t *current = head;
    book_t *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    head = prev;
    
    print();
}


void searchBooks(int searchChoice, char* searchValue){

    book_t *index = head;
    bool bookFound = false;

    while (index!=NULL)
    {   

        switch (searchChoice)
        {
        case 0:
            
            if (!strcmp(index->isbn,searchValue)){
                printf("\n%s,%s,%s,%d\n", index->isbn, index->title, index->author, index->publication_year);
                bookFound = true;   
            }

            break;
        case 1:

            if (!strcmp(index->author,searchValue)){
                
                printf("\n%s,%s,%s,%d\n", index->isbn, index->title, index->author, index->publication_year); 
                bookFound = true;  
            }

            break;
        case 2:
            
            if (!strcmp(index->title,searchValue)){
                printf("\n%s,%s,%s,%d\n", index->isbn, index->title, index->author, index->publication_year); 
                bookFound = true;  
            }

            break;
        default:
            break;
        }
   
        index = index->next;

    }
    
    if (!bookFound) {
        printf("\nThe book was not found.\n");
    }

}





void WriteLLToFile() {
    
    book_t *books = head;
    
    FILE *fp = fopen("book.txt", "w");
    if (fp == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    while (books != NULL) {
        fprintf(fp,"%s,%s,%s,%d\n",books->isbn,books->title,books->author,books->publication_year);
        books = books->next;
    }
    
    fclose(fp);

}


void readDataFFile() {
    FILE *fp = fopen("book.txt", "r");
    if (fp == NULL) {
        printf("Failed to open the file for reading.\n");
        return;
    }

    char isbn[MAX_ISBN + 1];
    char title[MAX_TITLE_SIZE + 1];
    char author[MAX_AUTHOR_SIZE + 1];
    int publicationYear;

    while (fscanf(fp, "%[^,],%[^,],%[^,],%d\n", isbn, title, author, &publicationYear) == 4) {
        addBook(isbn, title, author, publicationYear, 0); // Assuming FIFO method (0)
    }

    fclose(fp);

}




void print(){

    book_t *index = head;
    
    printf("\nISBN-------TITLE-------AUTHOR-------PUBLICATION_YEAR-------\n");
    while (index!=NULL)
    {   
        
        printf("%s,%s,%s,%d\n", index->isbn, index->title, index->author, index->publication_year);
        index = index->next;

    }

}


void countNodes(){

    book_t *index = head;
    int count=0;

    while (index!=NULL)
    {
        count++;
        index=index->next;
    }
    
    printf("\n\nThere are %d book\n\n",count);

}