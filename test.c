#include <stdio.h>

char board[3][3];  // easy level
char board1[4][4];  // medium level
char board2[5][5];  // hard level

void Easy_Board1() 
{
    int i, j;
    char c = '1';
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = c;   // Fill with '1'..'9'
            c++;
        }
    }
}

void Medium_Board1() 
{
    int i, j;
    char c = '1';
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            board1[i][j] = c;   // Fill with '1'..'16'
            c++;
        }
    }
}

void Hard_Board1() 
{
    int i, j;
    char c = '1';
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            board2[i][j] = c;   // Fill with '1'..'25'
            c++;
        }
    }
}

void Easy_Board2() 
{
    int i, j;
    printf("\n");
    for (i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i != 2) {
            printf("\n---|---|---\n");
        }
    }
    printf("\n");
}

void Medium_Board2() 
{
    int i, j;
    printf("\n");
    for (i = 0; i < 4; i++) {
        printf(" %c | %c | %c | %c ", board1[i][0], board1[i][1], board1[i][2], board1[i][3]);
        if (i != 3) {
            printf("\n---|---|---|---\n");
        }
    }
    printf("\n");
}

void Hard_Board2() 
{
    int i, j;
    printf("\n");
    for (i = 0; i < 5; i++) {
        printf(" %c | %c | %c | %c | %c ", board2[i][0], board2[i][1], board2[i][2], board2[i][3], board2[i][4]);
        if (i != 4) {
            printf("\n---|---|---|---|---\n");
        }
    }
    printf("\n");
}

int checkWin() 
{
    int i;
    // Rows
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            return 1;
        }
    }
    // Columns
    for (i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            return 1;
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        return 1;
    }
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        return 1;
    }

    return 0;  // No winner
}

int checkWin1() 
{
    int i;
    // Rows
    for (i = 0; i < 4; i++) {
        if (board1[i][0] == board1[i][1] &&
            board1[i][1] == board1[i][2] &&
            board1[i][2] == board1[i][3]) {
            return 1;
        }
    }
    // Columns
    for (i = 0; i < 4; i++) {
        if (board1[0][i] == board1[1][i] &&
            board1[1][i] == board1[2][i] &&
            board1[2][i] == board1[3][i]) {
            return 1;
        }
    }
    // Diagonals
    if (board1[0][0] == board1[1][1] &&
        board1[1][1] == board1[2][2] &&
        board1[2][2] == board1[3][3]) {
        return 1;
    }
    if (board1[0][3] == board1[1][2] &&
        board1[1][2] == board1[2][1] &&
        board1[2][1] == board1[3][0]) {
        return 1;
    }

    return 0;  // No winner
}

int checkWin2() 
{
    int i;
    // Rows
    for (i = 0; i < 5; i++) {
        if (board2[i][0] == board2[i][1] &&
            board2[i][1] == board2[i][2] &&
            board2[i][2] == board2[i][3] &&
            board2[i][3] == board2[i][4]) {
            return 1;
        }
    }
    // Columns
    for (i = 0; i < 5; i++) {
        if (board2[0][i] == board2[1][i] &&
            board2[1][i] == board2[2][i] &&
            board2[2][i] == board2[3][i] &&
            board2[3][i] == board2[4][i]) {
            return 1;
        }
    }
    // Diagonals
    if (board2[0][0] == board2[1][1] &&
        board2[1][1] == board2[2][2] &&
        board2[2][2] == board2[3][3] &&
        board2[3][3] == board2[4][4]) {
        return 1;
    }
    if (board2[0][4] == board2[1][3] &&
        board2[1][3] == board2[2][2] &&
        board2[2][2] == board2[3][1] &&
        board2[3][1] == board2[4][0]) {
        return 1;
    }

    return 0;  // No winner
}

int isDraw() 
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0;  // Still empty cell
            }
        }
    }
    return 1;  // No empty cells, draw
}

int isDraw1() 
{   
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (board1[i][j] != 'X' && board1[i][j] != 'O') {
                return 0;  // Still empty cell
            }
        }
    }
    return 1;  // No empty cells, draw
}

int isDraw2() 
{
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (board2[i][j] != 'X' && board2[i][j] != 'O') {
                return 0;  // Still empty cell
            }
        }
    }
    return 1;  // No empty cells, draw
}

int main() 
{
    int n;
    printf("--------------------Menu--------------------\n");
    printf("1. Easy   Level\n");
    printf("2. Medium Level\n");
    printf("3. Hard   Level\n");
    printf("--------------------------------------------\n");
    printf("Enter The Value Of N :");
    scanf("%d",&n);
    switch (n)
    {
    case 1 :
        printf("Easy Level Selected\n");
    int player = 1;       // Player 1 starts
    int choice;
    char mark;            // 'X' or 'O'
    int row, col;
    int gameOver = 0;

    Easy_Board1();

    while (!gameOver) {
        Easy_Board2();
        printf("Player %d, enter a number (1-9): ", player);
        scanf("%d", &choice);

        if (choice < 1 || choice > 9) {
            printf("Invalid move! Try again.");
            continue;
        }

        // Convert choice 1-9 to row and col (0-2)
        choice--;              // make it 0-8
        row = choice / 3;
        col = choice % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Cell already taken! Try again.");
            continue;
        }

        if (player == 1) 
        {
            mark = 'X';
        } 
        else 
        {
            mark = 'O';
        }
        board[row][col] = mark;

        if (checkWin()) {
            Easy_Board2();
            printf("Player %d wins!", player);
            gameOver = 1;
        } else if (isDraw()) {
            Easy_Board2();
            printf("Game is a draw!");
            gameOver = 1;
        } else {
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

    return 0;
        break;
    case 2 :
        printf("Medium Level Selected\n");
    int player1 = 1;       // Player 1 starts
    char mark1;            // 'X' or 'O'    
    int choice1,row1, col1,gameOver1 = 0;
    Medium_Board1();
    while (!gameOver1) 
    {
        Medium_Board2();
        printf("Player %d, enter a number (1-16): ", player1);
        scanf("%d", &choice1);
        if (choice1 < 1 || choice1 > 16) {
            printf("Invalid move! Try again.");
            continue;
        }

        // Convert choice 1-16 to row and col (0-3)
        choice1--;              // make it 0-15
        row1 = choice1 / 4;
        col1 = choice1 % 4;

        if (board1[row1][col1] == 'X' || board1[row1][col1] == 'O') {
            printf("Cell already taken! Try again.");
            continue;
        }

        if (player1 == 1) 
        {
            mark1 = 'X';
        } 
        else 
        {
            mark1 = 'O';
        }

        board1[row1][col1] = mark1;

        if (checkWin1()) 
        {
            Medium_Board2();
            printf("Player %d wins!", player1);
            gameOver1 = 1;
        } 
        else if (isDraw1()) 
        {
            Medium_Board2();
            printf("Game is a draw!");
            gameOver1 = 1;
        } 
        else 
        {
            // Switch player
            if (player1 == 1) 
            {
                player1 = 2;
            } 
            else 
            {
                player1 = 1;
            }

        }
    }
    return 0;
        break;
    case 3 :
        printf("Hard Level Selected\n");
    int player2 = 1;       // Player 1 starts
    char mark2;            // 'X' or 'O'
    int choice2,row2, col2,gameOver2 = 0;
    Hard_Board1();
    while (!gameOver2)
    {
        Hard_Board2();
        printf("Player %d, enter a number (1-25): ", player2);
        scanf("%d", &choice2);
        if (choice2 < 1 || choice2 > 25) {
            printf("Invalid move! Try again.");
            continue;
        }
        // Convert choice 1-25 to row and col (0-4)
        choice2--;              // make it 0-24
        row2 = choice2 / 5;
        col2 = choice2 % 5;
        if (board2[row2][col2] == 'X' || board2[row2][col2] == 'O') {
            printf("Cell already taken! Try again.");
            continue;
        }
        if (player2 == 1) 
        {
            mark2 = 'X';
        } 
        else 
        {
            mark2 = 'O';
        }
        board2[row2][col2] = mark2;
        if (checkWin2())
        {
            Hard_Board2();
            printf("Player %d wins!", player2);
            gameOver2 = 1;
        } 
        else if (isDraw2()) 
        {
            Hard_Board2();
            printf("Game is a draw!");
            gameOver2 = 1;
        } 
        else 
        {
            // Switch player
            if (player2 == 1) 
            {
                player2 = 2;
            } 
            else 
            {
                player2 = 1;
            }
        }
    }
    return 0;
        break;
    default :       
    printf("--------------------Menu--------------------\n");
    printf("1. Easy   Level\n");
    printf("2. Medium Level\n");
    printf("3. Hard   Level\n");
    printf("--------------------------------------------\n");
        break;
    }
}
}