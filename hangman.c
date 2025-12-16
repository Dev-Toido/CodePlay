#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
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
            if (w) printf("pWord: %s\n", w);
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
            printf("Sorry for the poor man, your poor guesses made him die. Better try next time!!\n");
        }
        free(w); w = NULL;
        free(m); m = NULL;
    } while (flag);
}
int main(void){
    playHangman();
    return 0;
}