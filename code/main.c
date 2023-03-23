/**
 @file
 @brief File principale
 @author Delton Nicolas <896295@stud.unive.it>
 */

#include <stdio.h>
#include <stdlib.h>

#include "mappe.h"
#include "coda.h"
#include "ai.h"
#include "basicFun.h"

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

/**Coordinata x della testa**/
int x;
/**Coordinata y della testa**/
int y;
/**Dimensione della mappa (colonne)**/
int c;
/**Dimensione della mappa (righe)**/
int r;
/**Array dinamico contenente la mappa**/
char** mappa;
/**Array dinamico contenente la sequenza di mosse effettuate**/
char* sequenza;
char* coda_seq;
/**Numero di passi effettuati**/
int conta_passi = 0;

//Firme funzioni
void get_move(void);
void stampa_mappa(void);

/**
 @brief Funzione che salva il passo effettuato
 @param dir Direzione del passo effetuato
 */
void salva_passo(char dir){
    conta_passi++;
    punteggio--;
    sequenza = realloc(sequenza, conta_passi * sizeof(char));
    if (sequenza == NULL) {
        printf("Spazio insufficiente");
        exit(0);
    }
    sequenza[conta_passi-1] = dir;
}

/**
 @brief Funzione che verifica se è possibile effettuare la mossa desiderata e in caso positivo la fa
 @param x0 Valore di dove la testa deve spostarsi verticalmente
 @param y0 Valore di dove la testa deve spostarsi orizzontalmente
 @param dir Valore della direzione utilizzato per salvare le mosse effettuate
 */
void verifica_cella(int x0, int y0, char dir){
    if (x+x0 >= 0 && x+x0 < r && y+y0 >= 0 && y+y0 < c){
        if (mappa[x+x0][y+y0] == '$') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            moneta();
            aggiorna_coda();
            
        }
        else if (mappa[x+x0][y+y0] == '_') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            aggiorna_coda();
            stampa_mappa();
            win();
        }
        else if (mappa[x+x0][y+y0] == 'T') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            trapano();
            aggiorna_coda();
        }
        else if (mappa[x+x0][y+y0] == '!') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            imprevisto();
            aggiorna_coda();
        }
        else if (mappa[x+x0][y+y0] == ' ') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            aggiorna_coda();
        }
        else if (mappa[x+x0][y+y0] == '#' && trapani > 0) {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            usa_trapano();
            aggiorna_coda();
        }
        else if (mappa[x+x0][y+y0] == '.') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            lunghezza = verifica_morso();
            aggiorna_coda();
        }
    }
}

/**
 @brief Funzione che stampa la mappa aggiornata
 */
void stampa_mappa(void){
    system("clear");
    for (int i = 0; i < r; i++) {
        if (i == 0) {
            printf("Sequenza: ");
            for (int i = 0; i < conta_passi; i++) {
                printf("%c", sequenza[i]);
            }
            printf("\n");
        }
        for (int j = 0; j < c; j++) {
            printf("%c", mappa[i][j]);
        }
        if (i == r-3) printf("    Trapani: %d", trapani);
        if (i == r-2) printf("    Lunghezza: %d", lunghezza);
        if (i == r-1) printf("    Punteggio: %d", punteggio);
        printf("\n");
    }
}

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
    coda_seq = malloc(sizeof(char));
    int level;
    do {
        printf("Scegli livello da 1 a 4: ");
        scanf("%d", &level);
    } while (level < 1 || level > 4);
    getchar();

    mappe(level);

    stampa_mappa();
    
    get_move();
    //printf("%c", c);
    
    flushMap();
    free(sequenza);
    free(coda_seq);
    return 0;
}
