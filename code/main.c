/**
 @file
 @brief File principale
 @author Delton Nicolas <896295@stud.unive.it>
 */

#include <stdio.h>
#include <stdlib.h>

#include "coda.h"
#include "basicFun.h"
#include "mappe.h"
#include "ai.h"
#include "read_map_from_file.h"

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

/**Array dinamico contenente la mappa**/
char** mappa;
/**Array dinamico contenente la sequenza di mosse effettuate**/
/**Numero di passi effettuati**/


//Firme funzioni
void get_move(void);

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
        printf("Vuoi giocare da solo o trovare il percorso migliore in automatico?\n[1] da solo\n[2] in automatico\n");
        scanf("%d", &mode);
    } while (mode < 1 || mode > 2);
    getchar();

    int level;
    do {
        printf("Scegli livello da 1 a 4: ");
        scanf("%d", &level);
    } while (level < 1 || level > 4);
    getchar();

    mappe(level);

    stampa_mappa();

    if(mode == 1){
        //DA SOLO     
        get_move();
        
    } else {
        //IN AUTOMATICO
        auto_solve();
    }

    flushMap();
    free(sequenza);
    return 0;
}
