#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

void fillLinkedList(struct Node** head);
void serializeLinkedList(struct Node* head);
void deserializeLinkedList(struct Node** head);
void printLinkedList(struct Node* head);

void fillLinkedList(struct Node** head) {
    srand(time(NULL));  // Seed the random number generator

    int assetCount = rand() % 11 + 10;  // Randomly determine the number of assets (between 10 and 20)

    for (int i = 0; i < assetCount; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;

        // Randomly select an asset type
        int assetType = rand() % 4;

        switch (assetType) {
            case 0: {
                Asset1* asset1 = (Asset1*)malloc(sizeof(Asset1));
                strcpy(asset1->type, "Asset1");
                asset1->ivals[0] = rand() % 100;
                asset1->svals[0] = (double)rand() / RAND_MAX;
                newNode->data = asset1;
                break;
            }
            case 1: {
                Asset2* asset2 = (Asset2*)malloc(sizeof(Asset2));
                strcpy(asset2->type, "Asset2");
                asset2->svals[0] = (double)rand() / RAND_MAX;
                asset2->svals[1] = (double)rand() / RAND_MAX;
                asset2->ivals[0] = rand() % 100;
                asset2->ivals[1] = rand() % 100;
                newNode->data = asset2;
                break;
            }
            case 2: {
                Asset3* asset3 = (Asset3*)malloc(sizeof(Asset3));
                strcpy(asset3->type, "Asset3");
                sprintf(asset3->string1, "String1_%d", i);
                sprintf(asset3->string2, "String2_%d", i);
                newNode->data = asset3;
                break;
            }
            case 3: {
                Asset4* asset4 = (Asset4*)malloc(sizeof(Asset4));
                strcpy(asset4->type, "Asset4");
                asset4->value1 = (double)rand() / RAND_MAX;
                asset4->value2 = (float)rand() / RAND_MAX;
                asset4->value3 = (double)rand() / RAND_MAX;
                newNode->data = asset4;
                break;
            }
        }

        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* curr = *head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    }
}

void serializeLinkedList(struct Node* head) {
    FILE* file = fopen("linkedlist.bin", "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    Node* curr = head;

    while (curr != NULL) {
        if (strcmp(((Asset1*)curr->data)->type, "Asset1") == 0) {
            fwrite(((Asset1*)curr->data)->type, sizeof(char), 20, file);
            fwrite(curr->data, sizeof(Asset1), 1, file);
        } else if (strcmp(((Asset2*)curr->data)->type, "Asset2") == 0) {
            fwrite(((Asset2*)curr->data)->type, sizeof(char), 20, file);
            fwrite(curr->data, sizeof(Asset2), 1, file);
        } else if (strcmp(((Asset3*)curr->data)->type, "Asset3") == 0) {
            fwrite(((Asset3*)curr->data)->type, sizeof(char), 20, file);
            fwrite(curr->data, sizeof(Asset3), 1, file);
        } else if (strcmp(((Asset4*)curr->data)->type, "Asset4") == 0) {
            fwrite(((Asset4*)curr->data)->type, sizeof(char), 20, file);
            fwrite(curr->data, sizeof(Asset4), 1, file);
        }

        curr = curr->next;
    }

    fclose(file);
}

void deserializeLinkedList(struct Node** head) {
    FILE* file = fopen("linkedlist.bin", "rb");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    *head = NULL;
    Node* curr = NULL;

    while (1) {
        char assetType[21];  // Increased buffer size by 1 for null-terminator
        size_t bytesRead = fread(assetType, sizeof(char), 20, file);
        if (bytesRead != 20) {
            break;  // Reached end of file
        }
        assetType[20] = '\0';  // Null-terminate the asset type string

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;

        if (strcmp(assetType, "Asset1") == 0) {
            Asset1* asset1 = (Asset1*)malloc(sizeof(Asset1));
            fread(asset1, sizeof(Asset1), 1, file);
            newNode->data = asset1;
        } else if (strcmp(assetType, "Asset2") == 0) {
            Asset2* asset2 = (Asset2*)malloc(sizeof(Asset2));
            fread(asset2, sizeof(Asset2), 1, file);
            newNode->data = asset2;
        } else if (strcmp(assetType, "Asset3") == 0) {
            Asset3* asset3 = (Asset3*)malloc(sizeof(Asset3));
            fread(asset3, sizeof(Asset3), 1, file);
            newNode->data = asset3;
        } else if (strcmp(assetType, "Asset4") == 0) {
            Asset4* asset4 = (Asset4*)malloc(sizeof(Asset4));
            fread(asset4, sizeof(Asset4), 1, file);
            newNode->data = asset4;
        }

        if (*head == NULL) {
            *head = newNode;
            curr = newNode;
        } else {
            curr->next = newNode;
            curr = curr->next;
        }
    }

    fclose(file);
}

void printLinkedList(struct Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        if (strcmp(((Asset1*)curr->data)->type, "Asset1") == 0) {
            Asset1* asset1 = (Asset1*)curr->data;
            printf("Asset1: ivals[0] = %d, svals[0] = %lf\n", asset1->ivals[0], asset1->svals[0]);
        } else if (strcmp(((Asset2*)curr->data)->type, "Asset2") == 0) {
            Asset2* asset2 = (Asset2*)curr->data;
            printf("Asset2: svals[0] = %lf, svals[1] = %lf, ivals[0] = %d, ivals[1] = %d\n",
             asset2->svals[0], asset2->svals[1], asset2->ivals[0], asset2->ivals[1]);
        } else if (strcmp(((Asset3*)curr->data)->type, "Asset3") == 0) {
            Asset3* asset3 = (Asset3*)curr->data;
            printf("Asset3: string1 = %s, string2 = %s\n", asset3->string1, asset3->string2);
        } else if (strcmp(((Asset4*)curr->data)->type, "Asset4") == 0) {
            Asset4* asset4 = (Asset4*)curr->data;
            printf("Asset4: value1 = %lf, value2 = %f, value3 = %lf\n",
             asset4->value1, asset4->value2, asset4->value3);
        }

        curr = curr->next;
    }
}

int main() {
    struct Node* head = NULL;

    fillLinkedList(&head);
    serializeLinkedList(head);
    printf("\nGenerated and Serilazed Linked List...\n");
    printLinkedList(head);
    deserializeLinkedList(&head);
    printf("\nReaded and Reconstructed Linked List..\n");
    printLinkedList(head);
    
    return 0;
}
