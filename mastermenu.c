#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
void welcomePrint(){
    int choose = 0;
    char name[50],c;
    
    printf("Enter your name: ");
    fgets(name,50,stdin);
    
    name[strcspn(name, "\n")] = '\0';
    printf("\nWelcome %s to Codeplay-A C based gaming arcade\n\n\n", name);
printf("+-------------------------------------+\n");
printf("|        CODEPLAY - GAMING ARCADE     |\n");
printf("|      A C based Gaming Experience    |\n");
printf("|                                     |\n");
printf("+-------------------------------------+\n");
printf("|           :Available Games:         |\n");
printf("|   1. TIC-TAC-TOE                    |\n");
printf("|   2. HANGMAN                        |\n");
printf("+-------------------------------------+\n");
    do {
        
        printf("+-------------------------------------+\n");
        printf("|            Select Game:             |\n");
        printf("|   1. Play Tic-Tac-Toe               |\n");
        printf("|   2. Play Hangman                   |\n");
        printf("|   3. Exit Program                   |\n");
        printf("+-------------------------------------+\n");
        printf("\n\nEnter selection: ");
        scanf("%d", &choose);
        
        switch(choose){
            case 1:
                printf("TIC-TAC-TOE GAME RULES MANU:\n");
                printf("");//Rules for the TIC-TAC-TOE game
                printf("\n\n");
                break;
            case 2:
                printf("\n\nHANGMAN GAME MENU:\n");
                printf("-> Guess letters to reveal the hidden word!\n-> You get 6 wrong guesses before GAME OVER\n-> No proper nouns, slang, or abbreviations\n-> Fill ALL blanks to WIN before hangman completes\n-> Choose level: A=Easy (short)(3 letters words), B=Medium(4 letters words), C=Hard (long)(5 letters words)\n->Two/Three letter per turn - good luck!\nGet ready to play...\n");
                
                printf("\n\n");
                break;
            case 3:
                printf("Thanks for using this programme!");
                break;
            default:
                printf("Please enter valid choice (1-3)");
                break;
        }
    } while(choose != 3);
}
int main(){
    welcomePrint();
    return 0;
}