/**
 @file
 @brief File principale
 @author Delton Nicolas <896295@stud.unive.it>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
/**Punteggio totale**/
int punteggio = 1000;
/**Lunghezza dello snake**/
int lunghezza = 1;
/**Numero di trapani**/
int trapani = 0;
/**Array dinamico contenente la mappa**/
char** mappa;
/**Array dinamico contenente la sequenza di mosse effettuate**/
char* sequenza;
/**Numero di passi effettuati**/
int conta_passi = 0;

//Firme funzioni
void get_move(void);
void stampa_mappa(void);
void genera_elementi(int nMonete, int nTrapani, int nImprevisti);

/**
 @brief Funzione che genera la mappa desiderata
 @param n Inserire codice della mappa da selezionare
 */
void mappe(int n){
    switch (n) {
        case 1:
            c = 20;
            r = 10;
            mappa = malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = malloc(sizeof(char) * c);
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (i == 0 || j == 0 || i == r-1 || j == c-1) mappa[i][j] = '#';
                    else mappa[i][j] = ' ';
                }
            }
            mappa[3][0] = 'o';
            x = 3;
            y = 0;
            mappa[7][c-1] = '_';
            genera_elementi(7, 2, 2);
            break;
        
        case 2:
            c = 20;
            r = 10;
            mappa = malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = malloc(sizeof(char) * c);
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (i == 0 || j == 0 || i == r-1 || j == c-1) mappa[i][j] = '#';
                    else mappa[i][j] = ' ';
                }
            }
            mappa[3][0] = 'o';
            x = 3;
            y = 0;
            mappa[2][c-1] = '_';
            
            for (int i = 1; i < 6; i++) {
                mappa[i][4] = '#';
            }
            for (int i = 1; i < 11; i++) {
                mappa[4][c-i] = '#';
            }
            
            genera_elementi(7, 3, 2);
            break;
            
        case 3:
            c = 30;
            r = 10;
            mappa = malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = malloc(sizeof(char) * c);
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (i == 0 || j == 0 || i == r-1 || j == c-1) mappa[i][j] = '#';
                    else mappa[i][j] = ' ';
                }
            }
            mappa[3][0] = 'o';
            x = 3;
            y = 0;
            mappa[8][c-1] = '_';
            
            for (int i = 1; i < 6; i++) {
                mappa[i][4] = '#';
            }
            for (int i = 1; i < 16; i++) {
                mappa[4][c-i] = '#';
            }
            for (int i = r-1; i > 2; i--) {
                mappa[i][7] = '#';
            }
            for (int i = 1; i < 7; i++) {
                mappa[r-3][c-14+i] = '#';
            }
            
            genera_elementi(15, 10, 5);
            break;
            
        case 4:
            c = 32;
            r = 14;
            mappa = malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = malloc(sizeof(char) * c);
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (i == 0 || j == 0 || i == r-1 || j == c-1) mappa[i][j] = '#';
                    else mappa[i][j] = ' ';
                }
            }
            mappa[3][0] = 'o';
            x = 3;
            y = 0;
            mappa[8][c-1] = '_';
            
            for (int i = 1; i < 6; i++) {
                mappa[i][4] = '#';
            }
            for (int i = 1; i < 16; i++) {
                mappa[4][c-i] = '#';
            }
            for (int i = r-1; i > 6; i--) {
                mappa[i][7] = '#';
            }
            for (int i = 1; i < 7; i++) {
                mappa[r-3][c-14+i] = '#';
            }
            for (int i = 3; i < 10; i++) {
                mappa[i][12] = '#';
            }
            
            genera_elementi(15, 10, 5);
            break;
            
        case 5:
            break;
        default:
            break;
    }
}

/**
 @brief Funzione che genera monete, trapani e imprevisti
 @param nMonete Inserire il numero di monete desiderate
 @param nTrapani Inserire il numero di trapani desiderate
 @param nImprevisti Inserire il numero di imprevisti desiderate
 */
void genera_elementi(int nMonete, int nTrapani, int nImprevisti){
    srand((int)time(NULL));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)  {
            if(mappa[i][j] != '#' && mappa[i][j] != 'o' && mappa[i][j] != '_'){
                if(rand()%2 && rand()%2 && rand()%2 && rand()%2 && rand()%2 && nMonete > 0){
                    mappa[i][j] = '$';
                    nMonete--;
                }
                if(rand()%2 && rand()%2 && rand()%2 && rand()%2 && rand()%2 && nTrapani > 0){
                    mappa[i][j] = 'T';
                    nTrapani--;
                }
                if(rand()%2 && rand()%2 && rand()%2 && rand()%2 && rand()%2 && nImprevisti > 0){
                    mappa[i][j] = '!';
                    nImprevisti--;
                }
            }
        }
    }
}

/**
 @brief Funzione che libera la memoria
 */
void flushMap(void){
    for (int i = 0; i < r; i++) {
        free(mappa[i]);
        mappa[i] = NULL;
    }
    free(mappa);
    mappa = NULL;
}

/**
 @brief Funzione eseguita quanto la testa trova una moneta
 */
void moneta(void){
    punteggio += 10;
    lunghezza++;
}

/**
 @brief Funzione eseguita quanto la testa trova un imprevisto
 */
void imprevisto(void){
    punteggio /= 2;
    lunghezza /= 2;
    
    if (lunghezza == 0) {
        printf("TRY AGAIN\n");
        exit(0);
    }
}

/**
 @brief Funzione eseguita quanto la testa trova un trapano
 */
void trapano(void) {
    trapani += 3;
}

/**
 @brief Funzione eseguita quanto la testa vuole usare un trapano
 */
void usa_trapano(void){
    trapani--;
}

/**
 @brief Funzione eseguita quanto la testa trova l'uscita
 */
void win(void){
    printf("WIN\n");
    exit(0);
}

/**
 @brief Funzione che salva il passo effettuato
 @param dir Direzione del passo effetuato
 */
void salva_passo(char dir){
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
            
        }
        else if (mappa[x+x0][y+y0] == '_') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
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
        }
        else if (mappa[x+x0][y+y0] == '!') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            imprevisto();
        }
        else if (mappa[x+x0][y+y0] == ' ') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
        }
        else if (mappa[x+x0][y+y0] == '#' && trapani > 0) {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            usa_trapano();
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
    conta_passi++;
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
    punteggio--;
    stampa_mappa();
    get_move();
}

int main(int argc, const char * argv[]) {
    sequenza = malloc(sizeof(char));
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
    return 0;
}
