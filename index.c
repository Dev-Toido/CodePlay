#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
/* forward declarations */
void playtictactoe(void);
void playHangman(void);
char hm[300] = "  ++----------------+\n  ++------------+---+\n  ||     //     |\n  ||    //      |\n  ||   //       |\n  ||  //        |\n  || //         |\n  ||//           \n  ||/            \\\n  ||             \n  ||              \n  ||\n  ||\n+=++=======================+\n+==========================+\n";
char* hangman_image(int n){
    if(n>6 || n<0) return NULL;
    else{
    for(int i=0;i<=n;i++){
        if (i==0){hm[150]=' ';hm[167]=' ';hm[168]=' ';hm[187]=' ';hm[169]=' ';hm[204]=' ';hm[206]=' ';}
        if (i==1){hm[150]='0';}
        if (i==2){hm[167]='/';}
        if (i==3){hm[168]='|';hm[187]='|';}
        if (i==4){hm[169]='\\';}
        if (i==5){hm[204]='/';}
        if (i==6){hm[206]='\\';}
    }}
        return hm;
}
/* simple portable strdup replacement */
char *my_strdup(const char *s){
    char *p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}
char* strupper(char* str){
    if (!str) return NULL;
    for (int i = 0; str[i] != '\0'; ++i) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }
    return str;
}
char* randword(int n){
    FILE *fprt = NULL;
    switch (n){
    case 1:fprt=fopen("files/easy.txt","r");break;
    case 2:fprt=fopen("files/med.txt","r");break;
    case 3:fprt=fopen("files/hard.txt","r");break;
    default:
        fprintf(stderr, "invalid difficulty: %d\n", n);
        return NULL;
        break;
    }
    if (!fprt) {
        perror("fopen");
        return NULL;
    }

    char buf[256];
    char *selected = NULL;
    int count = 0;

    /* Reservoir sampling: pick one random word from the file */
    while (fscanf(fprt, "%255s", buf) == 1) {
        ++count;
        if (rand() % count == 0) {
            free(selected);
            selected = my_strdup(buf);
        }
    }

    fclose(fprt);

    if (!selected) {
        fprintf(stderr, "no words found in file\n");
    }
    return selected;
}
char* maskword(const char *word) {
    int len = strlen(word);
    char *masked = my_strdup(word);
    int num_underscores;
    if (len == 3) {
        num_underscores = 2;
    } else if (len == 4) {
        num_underscores = 2;
    } else if (len == 5) {
        num_underscores = 3;
    } else {
        return masked;
    }

    /* pick unique positions to replace with underscores */
    int *used = calloc(len, sizeof(int));
    if (!used) return masked;
    int chosen = 0;
    while (chosen < num_underscores) {
        int pos = rand() % len;
        if (!used[pos]) {
            used[pos] = 1;
            masked[pos] = '_';
            chosen++;
        }
    }
    free(used);
    return masked;
}
int inpstr_check(char *str,int n){
    int numchar = 0, index = 0;
    if (!str) return 0;
    while (str[index] != '\0') {
        if (isalpha((unsigned char)str[index])) numchar++;
        index++;
    }
    return numchar == n;
}
int update_mask(char *masked_word, const char *original_word, char *guess) {
    if (!masked_word || !original_word || !guess) return 0;
    int match_word = 0;
    int len_mword = strlen(masked_word);

    /* Normalize guess to uppercase and reveal any matching letters */
    for (int gi = 0; guess[gi] != '\0'; ++gi) {
        char g = guess[gi];
        if (!isalpha((unsigned char)g)) continue;
        g = (char)toupper((unsigned char)g);
        for (int i = 0; i < len_mword; ++i) {
            if (masked_word[i] == '_' && original_word[i] == g) {
                masked_word[i] = original_word[i];
                match_word++;
            }
        }
    }
    return match_word;
}

void playHangman(){
    int flag = 1, die = 1;
    srand((unsigned)time(NULL));
    printf("%40s","WELCOME TO THE GAME OF HANGMAN!!\n");
    //The fancy printing part is to be done here
    char ch, inpstr[64];
    char *w = NULL, *m = NULL;
    do {
        printf("Choose the difficulty \nE for Easy \nM for Medium\nH for Hard\nX to Exit\n");
        printf("Enter Your choice ");
        if (scanf(" %c", &ch) != 1) break;
        ch = (char)toupper((unsigned char)ch);
        /* consume rest of line so subsequent fgets() works as expected */
        int __ch;
        while ((__ch = getchar()) != '\n' && __ch != EOF) ;

        if (ch == 'X') break;

        switch (ch) {
            case 'E': w = strupper(randword(1)); break;
            case 'M': w = strupper(randword(2)); break;
            case 'H': w = strupper(randword(3)); break;
            default: flag = 0; break;
        }
        if (!flag) break;
        if (!w) continue; /* failed to get a word, try again */

        m = maskword(w);
        die = 1;
        int tries = 0;
        int expected = (ch == 'H') ? 3 : 2;

        while (tries <= 6) {
            char *image = hangman_image(tries);
            if (image) printf("%s\n", image);
            if(tries==6)break;
            //if (w) printf("pWord: %s\n", w);
            if (m) printf("Word: %s\n", m);
            printf("Enter the guess in sequential order: ");
            /* read guess line */
            if (!fgets(inpstr, sizeof inpstr, stdin)) break;
            /* strip newline */
            size_t L = strlen(inpstr);
            if (L && inpstr[L-1] == '\n') inpstr[L-1] = '\0';
            
            if (!inpstr_check(inpstr, expected)) {
                printf("Invalid input: please enter %d letters.\n", expected);
                continue;}
            
            int matched = update_mask(m, w, inpstr);
            expected = expected - matched;
            printf("You have entered %d correct letters.\n", matched);
            if (m && w && strcmp(m, w) == 0) {
                printf("You have guessed it right congrats!!\nThe word was %s.\n", m);
                die = 0;
                break;
            }
            if (matched == 0) tries++;
        }
        if (die) {
            printf("Sorry for the poor man, your poor guesses made him die. Better try next time!!\nThe word was %s.\n", m);
        }
        free(w); w = NULL;
        free(m); m = NULL;
    } while (flag);
}
void welcomePrint(){
    int choose = 0;
    char name[50];
    
    printf("Enter your name: ");
    fgets(name,50,stdin);
    
    name[strcspn(name, "\n")] = '\0';
    printf("\nWelcome %s to Codeplay-A C based gaming arcade\n\n\n", name);
    printf("+-------------------------------------+\n");
    printf("|        CODEPLAY - GAMING ARCADE     |\n");
    printf("|      A C based Gaming Experience    |\n");
    printf("|                                     |\n");
    printf("+-------------------------------------+\n");
    printf("|            Available Games:         |\n");
    printf("|   1. TIC-TAC-TOE                    |\n");
    printf("|   2. HANGMAN                        |\n");
    printf("+-------------------------------------+\n");
    do {
        
        printf("+-------------------------------------+\n");
        printf("|            Select Game:             |\n");
        printf("|   1. Play Tic-Tac-Toe               |\n");
        printf("|   2. Play Hangman                   |\n");
        printf("|   0. Exit Program                   |\n");
        printf("+-------------------------------------+\n");
        printf("\n\nEnter selection: ");
        scanf("%d", &choose);
        
        switch(choose){
            case 1:
                printf("TIC-TAC-TOE GAME RULES MENU:\n");
                printf("");//Rules for the TIC-TAC-TOE game
                playtictactoe();
                printf("\n\n");
                break;
            case 2:
                printf("\n\nHANGMAN GAME MENU:\n");
                printf("-> Guess letters to reveal the hidden word!\n-> You get 6 wrong guesses before GAME OVER\n-> No proper nouns, slang, or abbreviations\n-> Fill ALL blanks to WIN before hangman completes\n-> Choose level: A=Easy (short)(3 letters words), B=Medium(4 letters words), C=Hard (long)(5 letters words)\n->Two/Three letter per turn - good luck!\nGet ready to play...\n");
                playHangman();
                printf("\n\n");
                break;
            case 0:
                printf("Thanks for playing and do play again!!");
                break;
            default:
                printf("Please enter valid choice (1-3)");
                break;
        }
    } while(choose != 0);
}
//tictactoe functions
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
void playtictactoe(){
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
}
int main(){
    welcomePrint();
    return 0;
}