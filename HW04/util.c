#include <stdio.h>


void takeDishName(int dishNum){ // This is my code can read spesific dish if you enter the dish number but due to the arrays forbidden i cannot use.
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
      
        if (ch == '\n' && skip) {
            skip = 0;
        }

		if(ch == '\n')
			count++;

		// print until space after skip
		if(!skip  && count == dishNum)
			printf("%c",ch);
    }

    fclose(menu);
}