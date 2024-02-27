#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    char type;
    int value;
} Block;

typedef struct {
    Point* body;
    int length;
} Snake;

void init_board(Block*** board, int* obstacle_row, int* obstacle_col, int* bait_row, int* bait_col) {
    *board = (Block**)malloc(BOARD_SIZE * sizeof(Block*));
    for (int i = 0; i < BOARD_SIZE; i++) {
        (*board)[i] = (Block*)malloc(BOARD_SIZE * sizeof(Block));
        for (int j = 0; j < BOARD_SIZE; j++) {
            (*board)[i][j].type = 'e';
            (*board)[i][j].value = 0;
        }
    }

    // Generate random obstacle and bait positions
    srand(time(NULL));
    int obstacleNum= (rand() % (3) + 1);
    for (int i = 0; i < obstacleNum; i++)
    {   
        
        *obstacle_row = rand() % BOARD_SIZE;
        *obstacle_col = rand() % BOARD_SIZE;
        int obst= (rand() % (BOARD_SIZE-1) + 1);

        (*board)[*obstacle_row][*obstacle_col].type = 'o';
        (*board)[*obstacle_row][*obstacle_col].value = obst;
    }
    

    do {
        *bait_row = rand() % BOARD_SIZE;
        *bait_col = rand() % BOARD_SIZE;
    } while (*bait_row == 0 && *bait_col == 0);

    (*board)[*bait_row][*bait_col].type = 'b';
    (*board)[*bait_row][*bait_col].value = 0;
}


void draw_board(Block** board, Snake* snake) {
    printf(" ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("--");
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("|");
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == snake->body[0].row && j == snake->body[0].col) {
                printf("O ");
            } else if (i == 0 && j == 0) {
                printf("  ");
            } else if (i == snake->body[0].row && j == snake->body[0].col) {
                printf("O ");
            } else if (i == snake->body[0].row && j == snake->body[0].col) {
                printf("X ");
            } else if (board[i][j].type == 'b') {
                printf(". ");
            } else if (board[i][j].type == 'o') {
                printf("%d ", board[i][j].value);
            } else {
                printf("  ");
            }
        }
        printf("|\n");
    }

    printf(" ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("--");
    }
    printf("\n");
}



int is_snake_body(Snake* snake, int row, int col) {
    for (int i = 0; i < snake->length; i++) {
        if (snake->body[i].row == row && snake->body[i].col == col) {
            return 1;
        }
    }
    return 0;
}

void move(Snake* snake, char direction) {
    int row_delta = 0, col_delta = 0;
    switch (direction) {
        case 'w':
            row_delta = -1;
            break;
        case 'a':
            col_delta = -1;
            break;
        case 's':
            row_delta = 1;
            break;
        case 'd':
            col_delta = 1;
            break;
        default:
            return;
    }

    // Move the head of the snake
    snake->body[0].row += row_delta;
    snake->body[0].col += col_delta;

    // Shift the rest of the body
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
}

int check_status(Block** board, Snake* snake) {
    // Check if the snake hits its own body
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[i].row == snake->body[0].row && snake->body[i].col == snake->body[0].col) {
            return 1;
        }
    }

    // Check if the snake collides with the wall
    if (snake->body[0].row < 0 || snake->body[0].row >= BOARD_SIZE ||
        snake->body[0].col < 0 || snake->body[0].col >= BOARD_SIZE) {
        return 1;
    }

    // Check if the snake encounters an obstacle longer than itself
    int obstacle_row = -1, obstacle_col = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].type == 'o' && board[i][j].value > snake->length) {
                obstacle_row = i;
                obstacle_col = j;
                break;
            }
        }
        if (obstacle_row != -1 && obstacle_col != -1) {
            break;
        }
    }

    if (obstacle_row != -1 && obstacle_col != -1) {
        int obstacle_height = board[obstacle_row][obstacle_col].value;
        for (int i = 1; i < snake->length; i++) {
            if (snake->body[i].row == obstacle_row && snake->body[i].col == obstacle_col &&
                obstacle_height < snake->length) {
                return 1;
            }
        }
    }

    return 0;
}

void update(Block*** board, Snake* snake, int* bait_row, int* bait_col, int* obstacle_row, int* obstacle_col) {
    // Update the snake's body
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    // Check if the snake ate the bait
    if (snake->body[0].row == *bait_row && snake->body[0].col == *bait_col) {
        // Increase the length of the snake

        snake->length++;

        // Generate a new bait position
        do {
            *bait_row = rand() % BOARD_SIZE;
            *bait_col = rand() % BOARD_SIZE;
        } while (*bait_row == 0 && *bait_col == 0);

        (*board)[*bait_row][*bait_col].type = 'b';
        (*board)[*bait_row][*bait_col].value = 0;
    }

    // Update the obstacles every 5 moves
    if (snake->length % 5 == 0) {
        int obstacle_height = 1;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if ((*board)[i][j].type == 'o') {
                    (*board)[i][j].value++;
                    obstacle_height = (*board)[i][j].value;
                }
            }
        }

        if (obstacle_height <= 3) {
            // Generate a new obstacle position
            do {
                *obstacle_row = rand() % BOARD_SIZE;
                *obstacle_col = rand() % BOARD_SIZE;
            } while ((*obstacle_row == 0 && *obstacle_col == 0) ||
                     (*obstacle_row == *bait_row && *obstacle_col == *bait_col) ||
                     is_snake_body(snake, *obstacle_row, *obstacle_col));

            (*board)[*obstacle_row][*obstacle_col].type = 'o';
            (*board)[*obstacle_row][*obstacle_col].value = 1;
        }
    }
}

void play() {
    Block** board;
    Snake snake;
    int obstacle_row, obstacle_col;
    int bait_row, bait_col;
    char direction;
    int game_over = 0;

    init_board(&board, &obstacle_row, &obstacle_col, &bait_row, &bait_col);

    // Initialize the snake
    snake.length = 1;
    snake.body = (Point*)malloc(snake.length * sizeof(Point));
    snake.body[0].row = 0;
    snake.body[0].col = 0;

    while (!game_over) {
        draw_board(board, &snake);
        printf("Enter your move (w/a/s/d): ");
        scanf(" %c", &direction);

        move(&snake, direction);
        game_over = check_status(board, &snake);
        update(&board, &snake, &bait_row, &bait_col, &obstacle_row, &obstacle_col);
    }

    draw_board(board, &snake);
    printf("Game over!\n");

    // Free memory
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(board[i]);
    }
    free(board);
    free(snake.body);
}

int main() {
    play();

    return 0;
}
