#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
// allocate an n x n board (contiguous block for rows)
char **make_board(int n){
    if (n <= 0) return NULL;

    char **board = malloc(n * sizeof(char *));
    if (!board) return NULL;

    char *data = malloc(n * n * sizeof(char));
    if (!data){
        free(board);
        return NULL;
    }

    for (int i = 0; i < n; ++i){
        board[i] = data + i * n;
        for (int j = 0; j < n; ++j)
            board[i][j] = ' '; // initialize with blank space
    }
    return board;

}
// free the board allocated by make_board
int free_board(char **board){
    if (!board) return 0;
    if (board[0]) free(board[0]); /* free contiguous data block */
    free(board);
    return 1;
}
// initialize guide board with printable labels (1..9 then A..)
void initialize_guide_board(char **board, int n){
    if (!board || n <= 0) return;
    int count = 1;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (count <= 9)
                board[i][j] = '0' + count; /* '1'..'9' */
            else
                board[i][j] = 'A' + (count - 10); /* 'A', 'B', ... */
            count++;
        }
    }
}
// print the board directly to stdout (no fixed-size buffer)
void print_board(char **a,char **b, int n){
    if (!a || !b || n <= 0) return;
    printf("\n");
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            printf(" %2c ", a[i][j]);
            if (j + 1 < n) printf("|");
        }
        printf("    ");
        for (int j = 0; j < n; ++j){
            printf(" %2c ", b[i][j]);
            if (j + 1 < n) printf("|");
        }
        printf("\n");
        if (i + 1 < n){
            for (int k = 0; k < n; ++k){
                printf("----");
                if (k + 1 < n) printf("+");
            }
            printf("    ");
            for (int k = 0; k < n; ++k){
                printf("----");
                if (k + 1 < n) printf("+");
            }
            printf("\n");
        }
    }
    if(n>3){printf("\n'A'=10,'B'=11,'C'=12,'D'=13,'E'=14,'F'=15,'G'=16");}
    if(n>4){printf(",'H'=17,'I'=18,'J'=19,'K'=20,'L'=21,'M'=22,'N'=23,'O'=24,'P'=25");}
    printf("\n");

}
int checkWin(char **board2,int n) 
{
    int i, j;
    /* Check rows */
    for (i = 0; i < n; i++) {
        char first = board2[i][0];
        if (first != 'X' && first != 'O') continue;
        for (j = 1; j < n; j++) {
            if (board2[i][j] != first) break;
        }
        if (j == n) return 1;
    }
    /* Check columns */
    for (i = 0; i < n; i++) {
        char first = board2[0][i];
        if (first != 'X' && first != 'O') continue;
        for (j = 1; j < n; j++) {
            if (board2[j][i] != first) break;
        }
        if (j == n) return 1;
    }
    /* Check primary diagonal */
    char first = board2[0][0];
    if (first == 'X' || first == 'O') {
        for (j = 1; j < n; j++) {
            if (board2[j][j] != first) break;
        }
        if (j == n) return 1;
    }
    /* Check anti-diagonal */
    first = board2[0][n-1];
    if (first == 'X' || first == 'O') {
        for (j = 1; j < n; j++) {
            if (board2[j][n-1-j] != first) break;
        }
        if (j == n) return 1;
    }

    return 0;  // No winner
}
int isDraw(char **board2,int n) 
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board2[i][j] != 'X' && board2[i][j] != 'O') {
                return 0;  // Still empty cell
            }
        }
    }
    return 1;  // No empty cells, draw
}
void play(char **board1,char **board2,int n){
    int player = 1;       // Player 1 starts
    char mark2;            // 'X' or 'O'
    int choice2,row2, col2,gameOver2 = 0;
    while (!gameOver2)
    {
        print_board(board1,board2,n);
        printf("Player %d, enter a number (1-%d): ", player,n*n);
        scanf("%d", &choice2);
        if (choice2 < 1 || choice2 > n*n) {
            printf("Invalid move! Try again.\n");
            continue;
        }
        // Convert choice 1-n*n to row and col (0-4)
        choice2--;              // make it 0-24
        row2 = choice2 / n;
        col2 = choice2 % n;
        if (board2[row2][col2] == 'X' || board2[row2][col2] == 'O') {
            printf("Cell already taken! Try again.\n");
            continue;
        }
        if (player == 1) 
        {
            mark2 = 'X';
        } 
        else 
        {
            mark2 = 'O';
        }
        board2[row2][col2] = mark2;
        if (checkWin(board2,n))
        {
            print_board(board1,board2,n);
            printf("Player %d wins!\n", player);
            gameOver2 = 1;
        } 
        else if (isDraw(board2,n)) 
        {
            print_board(board1,board2,n);
            printf("Game is a draw!\n");
            gameOver2 = 1;
        } 
        else 
        {
            // Switch player
            if (player == 1) 
            {
                player = 2;
            } 
            else 
            {
                player = 1;
            }
        }
    }
}
int main(){
    int flag = 1, n = 0;
    printf("%40s","WELCOME TO THE GAME OF TIC-TAC-TOE!!\n");
    //The fancy printing part is to be done here
    char ch;
    char **b = NULL, **bforp = NULL;
    do {
        printf("Choose the difficulty \nE for Easy(3x3) \nM for Medium(4x4)\nH for Hard(5x5)\nZ to Exit\n");
        printf("Enter Your choice ");
        if (scanf(" %c", &ch) != 1) break;
        ch = (char)toupper((unsigned char)ch);
        /* consume rest of line so subsequent fgets() works as expected */
        int __ch;
        while ((__ch = getchar()) != '\n' && __ch != EOF) ;

        if (toupper(ch) == 'Z') break;

        switch (ch) {
            case 'E':
                n = 3;
                b = make_board(n);
                bforp = make_board(n);
                break;
            case 'M':
                n = 4;
                b = make_board(n);
                bforp = make_board(n);
                break;
            case 'H':
                n = 5;
                b = make_board(n);
                bforp = make_board(n);
                break;
            default: flag = 0; break;
        }
        if (!flag) break;
        if (!b || !bforp) {
            if (b) { free_board(b); b = NULL; }
            if (bforp) { free_board(bforp); bforp = NULL; }
            continue; /* failed to make a board, try again */
        }

        initialize_guide_board(bforp,n);
        play(bforp,b,n);
        /* free the board after use */
        free_board(b);
        free_board(bforp);
        b = NULL;
        bforp=NULL;

    } while (flag);
    return 0;
}