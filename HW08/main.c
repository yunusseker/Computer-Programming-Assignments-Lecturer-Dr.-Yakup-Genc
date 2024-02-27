#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 3
#define FILENAME "8_puzzle_board.txt"
#define HIGHSCORE_FILENAME "highscore.txt"

typedef struct {
    int board[SIZE][SIZE];
    int empty_row;
    int empty_col;
} Puzzle;

// Function to save the current board state to a text file
void saveBoardState(const Puzzle *puzzle) {
    FILE *file = fopen(FILENAME, "a");
    if (file != NULL) {
        int i, j;
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                fprintf(file, "%d ", puzzle->board[i][j]);
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
        fclose(file);
    } else {
        printf("Error: Unable to save the board state.\n");
    }
}

// Function to save the high score to a text file
void saveHighScore(int score) {
    FILE *file = fopen(HIGHSCORE_FILENAME, "w");
    if (file != NULL) {
        fprintf(file, "%d", score);
        fclose(file);
    } else {
        printf("Error: Unable to save the high score.\n");
    }
}

// Function to count the number of inversions in an array
int countInversions(const int *arr, int size) {
    int inversions = 0;
    int i, j

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] != 0 && arr[j] != 0 && arr[i] > arr[j]) {
                inversions++;
            }
        }
    }

    return inversions;
}

// Function to check if the puzzle is solvable
int isSolvable(const Puzzle *puzzle) {
    int i, j;
    int arr[SIZE * SIZE];
    int k = 0;

    // Convert the puzzle board to a 1D array
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            arr[k] = puzzle->board[i][j];
            k++;
        }
    }

    // Count the number of inversions and check if it is even
    int inversions = countInversions(arr, SIZE * SIZE);
    return inversions % 2 == 0;
}

// Function to initialize the puzzle with a sequential board state
void initializePuzzle(Puzzle *puzzle) {
    int i, j, count = 1;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            puzzle->board[i][j] = count;
            count++;
        }
    }
    puzzle->board[SIZE-1][SIZE-1] = 0;
    puzzle->empty_row = SIZE - 1;
    puzzle->empty_col = SIZE - 1;
}

// Function to shuffle the board by swapping random elements
void shuffleBoard(Puzzle *puzzle) {
    int i, j, k, l;
    int temp;

    // Initialize the board in sequential order
    initializePuzzle(puzzle);

    // Shuffle the board using random swaps
    srand(time(NULL));
    do {
        for (i = SIZE - 1; i >= 0; i--) {
            for (j = SIZE - 1; j >= 0; j--) {
                // Generate random indices for swapping
                k = rand() % (i + 1);
                l = rand() % (j + 1);

                // Swap the elements
                temp = puzzle->board[i][j];
                puzzle->board[i][j] = puzzle->board[k][l];
                puzzle->board[k][l] = temp;

                // Update the position of the empty cell
                if (puzzle->board[i][j] == 0) {
                    puzzle->empty_row = i;
                    puzzle->empty_col = j;
                }
                if (puzzle->board[k][l] == 0) {
                    puzzle->empty_row = k;
                    puzzle->empty_col = l;
                }
            }
        }
    } while (!isSolvable(puzzle)); // Shuffle until a solvable board is generated
}

// Function to print the current puzzle board
void printPuzzle(const Puzzle *puzzle) {
    int i, j;
    printf("-------------\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (puzzle->board[i][j] == 0) {
                printf("|    ");
            } else {
                printf("| %d ", puzzle->board[i][j]);
            }
        }
        printf("\n");
        printf("-------------\n");
    }
}

// Function to move a number in a specified direction
void move(Puzzle *puzzle, int value, const char *direction) {
    int row, col;
    int i, j;

    // Find the row and column of the specified value
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (puzzle->board[i][j] == value) {
                row = i;
                col = j;
                break;
            }
        }
    }

    // Check if the specified value can be moved to the empty cell
    bool validMove = false;
    if (strcmp(direction, "U") == 0 && row > 0 && puzzle->empty_row == row - 1 && col == puzzle->empty_col) {
        validMove = true;
    } else if (strcmp(direction, "D") == 0 && row < SIZE - 1 && puzzle->empty_row == row + 1 && col == puzzle->empty_col) {
        validMove = true;
    } else if (strcmp(direction, "L") == 0 && col > 0 && puzzle->empty_col == col - 1 && row == puzzle->empty_row) {
        validMove = true;
    } else if (strcmp(direction, "R") == 0 && col < SIZE - 1 && puzzle->empty_col == col + 1 && row == puzzle->empty_row) {
        validMove = true;
    }

    if (validMove) {
        // Perform the move by swapping the value with the empty cell
        puzzle->board[puzzle->empty_row][puzzle->empty_col] = puzzle->board[row][col];
        puzzle->board[row][col] = 0;
        puzzle->empty_row = row;
        puzzle->empty_col = col;
    } else {
        printf("Invalid move!\n");
    }
}

// Function to check if the puzzle is solved
bool isPuzzleSolved(const Puzzle *puzzle) {
    int i, j;
    int count = 1;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1) {
                // Last cell should be empty (0)
                if (puzzle->board[i][j] != 0) {
                    return false;
                }
            } else {
                // Each cell should contain the next number in sequential order
                if (puzzle->board[i][j] != count) {
                    return false;
                }
                count++;
            }
        }
    }
    return true;
}

// Function to calculate the score based on the number of moves
int calculateScore(int moves) {
    return 1000 - 10 * moves;
}

// Recursive function to finish the puzzle automatically
void autoFinish(Puzzle *puzzle, int *moves) {
  /*Try to do but get a lot of segmentation fault with recursive way.*/
}

// Function to display the best score
void showBestScore() {
    FILE *highscoreFile = fopen(HIGHSCORE_FILENAME, "r");
    if (highscoreFile != NULL) {
        int highscore;
        fscanf(highscoreFile, "%d", &highscore);
        fclose(highscoreFile);

        printf("Best score: %d\n", highscore);
    } else {
        printf("No high score recorded yet.\n");
    }
}

int main() {
    Puzzle puzzle;
    int moves = 0;
    int score = 0;
    int input;

    printf("Welcome to the 8-puzzle game!\n");

    int option;
    do {
        printf("\nMenu:\n");
        printf("1. Play game as a user\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\nStarting a new game as a user.\n");

                // Shuffle the board and save the initial state
                shuffleBoard(&puzzle);
                saveBoardState(&puzzle);

                do {
                    printf("\nCurrent board:\n");
                    printPuzzle(&puzzle);
                    printf("\n");

                    printf("Enter a number and direction to move (e.g., 2-R): ");
                    scanf("%d-", &input);

                    char direction[2];
                    scanf("%1s", direction);

                    // Move the specified number in the specified direction
                    move(&puzzle, input, direction);
                    moves++;
                    score = calculateScore(moves);

                    // Save the updated board state
                    saveBoardState(&puzzle);

                    if (isPuzzleSolved(&puzzle)) {
                        printf("\nCongratulations! You solved the puzzle!\n");
                        printf("Total number of moves: %d\n", moves);
                        printf("Your score: %d\n", score);
                        FILE *file = fopen(FILENAME, "w");
                        fclose(file);

                        // Check if it's a new high score and save it
                        FILE *highscoreFile = fopen(HIGHSCORE_FILENAME, "r");
                        if (highscoreFile != NULL) {
                            int highscore;
                            fscanf(highscoreFile, "%d", &highscore);
                            fclose(highscoreFile);

                            if (score > highscore) {
                                printf("New high score! Your score has been saved.\n");
                                saveHighScore(score);
                            }
                        } else {
                            printf("New high score! Your score has been saved.\n");
                            saveHighScore(score);
                        }

                        break;
                    }
                } while (true);

                break;

            case 2:
                printf("\nFinishing the game with PC.\n");

                // Load the board state from the file
                /* FILE *file = fopen(FILENAME, "r");
                if (file != NULL) {
                    int i, j;
                    for (i = 0; i < SIZE; i++) {
                        for (j = 0; j < SIZE; j++) {
                            fscanf(file, "%d", &puzzle.board[i][j]);
                            if (puzzle.board[i][j] == 0) {
                                puzzle.empty_row = i;
                                puzzle.empty_col = j;
                            }
                        }
                    }
                    fclose(file);
                } else {
                    printf("Error: Unable to load the board state.\n");
                    break;
                }

                // Solve the puzzle automatically and save the moves
                moves = 0;
                autoFinish(&puzzle, &moves);
                saveBoardState(&puzzle);

                printf("\nThe computer solved the puzzle!\n");
                printf("Total number of moves: %d\n", moves); 
                printf("Returning to the main menu.\n");*/

                break;

            case 3:
                printf("\nShowing the best score.\n");
                showBestScore();
                break;

            case 4:
                printf("\nExiting the game. Goodbye!\n");
                FILE *file = fopen(FILENAME, "w");
                fclose(file);
                return 0;

            default:
                printf("\nInvalid option. Please try again.\n");
        }
    } while (true);
}
