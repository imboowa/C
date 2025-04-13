#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

// global variable for our board
char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
const char player = 'X';
const char computer = 'O';
//function prototypes to make compiler know what each function recieves at runtime
void makeBoard(void);
void putChoice(char *choice, char *choiceCom);
bool checkSpaces(int *indexX, int *indexY);
char checkWinner(void);
int freeSpace(void);
void playerMove(int *pRow, int *pCol);
void computerMove(int *pX, int *pY);
int main(void){
    int x, y, row, col;
    srand((int)time(0));
    char response;
    // do this as long as checkWinner function returns a space to show that there is room to win
    do {
        int *pX = &x, *pY = &y, *pRow = &row, *pCol = &col;
        playerMove(pRow,pCol);
        computerMove(pX,pY);
        makeBoard();
        // to see if x was returned so 'X' won, or o was returned so 'O' won
        if (checkWinner() == 'X'){
            printf("Player won\n");
            break;
        } else if (checkWinner() == 'O'){
            printf("Computer won\n");
            break;
        }
    } while(freeSpace() > 0);
    // if out of loop check if it was a winner or tie
    if (checkWinner() == ' '){
        printf("It is a tie\n\n........................\n");
    } else{
        printf("Thanks For Playing\n........................");
    }
    // print for beauty
    printf("\n");
    return 0;
}
void makeBoard(void){
    printf(" %c \033[1;34m|\033[0m %c \033[1;34m|\033[0m %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n\033[31m___\033[0m|\033[31m___\033[0m|\033[31m___\033[0m\n");
    printf(" %c \033[1;34m|\033[0m %c \033[1;34m|\033[0m %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n\033[31m___\033[0m|\033[31m___\033[0m|\033[31m___\033[0m\n");
    printf(" %c \033[1;34m|\033[0m %c \033[1;34m|\033[0m %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}
bool checkSpaces(int *indexX, int *indexY){
//loop through and check if given indexes are valid(true), if not return false
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(board[*indexX][*indexY] == ' '){
                return true;
            }
        }
    }
    return false;
}
char checkWinner(void){
    // check all rows
    // loop through all rows looking for a row that's alike
    for (int i = 0; i < 3; i++){
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }
    // check columns
    // loop through all columns looking for a column that's alike
    for (int i = 0; i < 3; i++){
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
        }
    }
    // chech diagonals
    // checking all diagonals to find a diagonal that's alike
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    } else if (board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }
    // if none of the above, then there ain't a winner then continue playing
    return ' ';
}
int freeSpace(void){
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (checkSpaces(&i,&j) == false){
                freeSpaces = freeSpaces - 1;
            }
        }
    }
    return freeSpaces;
}
void playerMove(int *pRow, int *pCol){
    // player's choice
    do{
        // ask for user input from player
        printf("Enter row (0,1,2): ");
        scanf(" %d", pRow);
        while(getchar() != '\n');// infinetly loop through and read character till \n
        pRow = pRow;
        printf("Enter column(0,1,2): ");
        scanf(" %d", pCol);
        while(getchar() != '\n');// infinetly loop through and read character till \n
        pCol = pCol;
    } while((*pRow > 2 || *pCol > 2) || (*pRow < 0 || *pCol < 0) || checkSpaces(pRow,pCol) == false);
    
    board[*pRow][*pCol] = player;
}
void computerMove(int *pX, int *pY){
    // computer's choice
    if (freeSpace() > 0){
        do{
            *pX = rand() % 3;
            *pY = rand() % 3;
        } while (checkSpaces(pX, pY) == false);
        
    }
    board[*pX][*pY] = computer;
}
