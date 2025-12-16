#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int main(){
    int choose = 0;
    char name[50],c;
    
    printf("Enter your name: ");
    fgets(name,50,stdin);
    
    name[strcspn(name, "\n")] = '\0';
    
printf("\nwelocome %s to our c codplay\n\n\n", name);
printf("*\n");
printf("*      C CODEPLAY - C PROJECT         *\n");
printf("*      First Semester, Group 5        *\n");
printf("*\n");
printf("*                                     *\n");
printf("*Available Games:                     *\n");
printf("*                                     *\n");
printf("-------------------------------------\n");
printf("*1. TIC-TAC-TOE                       *\n");
printf("*                                     *\n");
printf("*2. HANGMAN                           *\n");
printf("-------------------------------------\n");
printf("-------------------------------------\n");
printf("*Select Game:                         *\n");
printf("*1. Play Tic-Tac-Toe                  *\n");
printf("*2. Play Hangman                      *\n");
printf("*3. Exit Program                      *\n");
printf("-------------------------------------\n");
    do {
        
        printf("-------------------------------------\n");
        printf("*Select Game:                         *\n");
        printf("*1. Play Tic-Tac-Toe                  *\n");
        printf("*2. Play Hangman                      *\n");
        printf("*3. Exit Program                      *\n");
        printf("-------------------------------------\n");
        printf("\n\nEnter selection: ");
        scanf("%d", &choose);
        
        switch(choose){
            case 1:
                printf("TIC-TAC-TOE GAME RULES MANU:\n");
                printf("");
                printf("\n\n");
                break;
            case 2:
                printf("\n\nHANGMAN GAME MANU:\n");
                printf("• Guess letters to reveal the hidden word!\n• You get 6 wrong guesses before GAME OVER\n• No proper nouns, slang, or abbreviations\n• Fill ALL blanks to WIN before hangman completes\n• Choose level: A=Easy (short), B=Medium, C=Hard (long)\n•Two letter per turn - good luck!\nPress Enter to play...\n");
                printf("\n\n");
                break;
            case 3:
                printf("Thanks for using this programme! 😊");
                break;
            default:
                printf("Please enter valid choice (1-3)");
                break;
        }
    } while(choose != 3);
    
    return 0;
}