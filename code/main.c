/**
 @file
 @brief File principale
 @author Delton Nicolas <896295@stud.unive.it>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if !defined _WIN32
#include <termios.h>
#include <unistd.h>

int _getch(void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

#endif

#include "coda.h"
#include "basicFun.h"
#include "mappe.h"
#include "ai.h"

void get_move(void);

#include "read_map_from_file.h"

/**Array dinamico contenente la mappa**/
char** mappa;

/**
 @brief Funzione che legge la mossa da tastiera e gestisce le direzioni
 */
void get_move(void){
    char c = _getch();
    switch (c) {
        case 'w':
        case 'W':
            verifica_cella(-1, 0, 'N');
            break;
        
        case 's':
        case 'S':
            verifica_cella(1, 0, 'S');
            break;
            
        case 'd':
        case 'D':
            verifica_cella(0, 1, 'E');
            break;
            
        case 'a':
        case 'A':
            verifica_cella(0, -1, 'O');
            break;
            
        default:
            get_move();
            break;
    }
    stampa_mappa();
    get_move();
}

int main(int argc, const char * argv[]) {
    system("clear");
    sequenza = malloc(sizeof(char));

    int mode;
    do {
        printf("Vuoi giocare da solo o trovare il percorso migliore in automatico?\n[1] da solo\n[2] in automatico\n[3] da file in manuale\n[4] da file in automatico\n");
        scanf("%d", &mode);
    } while (mode < 1 || mode > 4);
    getchar();

    if (mode == 3) {
        readFromFile();
        get_move();
    } else if(mode == 4){
        readFromFile();
        auto_solve();
    }
    
    int level;
    do {
        printf("Scegli livello da 1 a 4: ");
        scanf("%d", &level);
    } while (level < 1 || level > 4);
    getchar();

    mappe(level);

    stampa_mappa();

    switch (mode)
    {
        case 1: get_move();
            break;

        case 2:
            auto_solve();
            break;
    }

    flushMap();
    free(sequenza);
    return 0;
}
