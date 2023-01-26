//
//  main.c
//  Snake
//
//  Created by Nicolas Delton on 24/01/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x, y; //o coords
int c, r; //map dimensions
int punteggio = 1000, lunghezza = 1, trapani = 0; //game values
char** mappa; //map
char* sequenza;
int conta_passi = 0;

void get_move(void);
void stampa_mappa(void);
void genera_elementi(int nMonete, int nTrapani, int nImprevisti);

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
            
        default:
            break;
    }
}

void genera_elementi(int nMonete, int nTrapani, int nImprevisti){
    srand((int)time(NULL));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)  {
            if(mappa[i][j] != '#' && mappa[i][j] != 'o' && mappa[i][j] != '_'){
                if(rand()%2 && rand()%2 && rand()%2 && rand()%2 && nMonete > 0){
                    mappa[i][j] = '$';
                    nMonete--;
                }
                if(rand()%2 && rand()%2 && rand()%2 && rand()%2 && nTrapani > 0){
                    mappa[i][j] = 'T';
                    nTrapani--;
                }
                if(rand()%2 && rand()%2 && rand()%2 && rand()%2 && nImprevisti > 0){
                    mappa[i][j] = '!';
                    nImprevisti--;
                }
            }
        }
    }
}

void flushMap(void){
    for (int i = 0; i < r; i++) {
        free(mappa[i]);
        mappa[i] = NULL;
    }
    free(mappa);
    mappa = NULL;
}

void moneta(void){
    punteggio += 10;
    lunghezza++;
}

void imprevisto(void){
    punteggio /= 2;
    lunghezza /= 2;
    
    if (lunghezza == 0) {
        printf("TRY AGAIN");
        exit(0);
    }
}

void trapano(void) {
    trapani += 3;
}

void usa_trapano(void){
    trapani--;
}

void win(void){
    printf("WIN\n");
    exit(0);
}

void salva_passo(char dir){
    sequenza = realloc(sequenza, conta_passi * sizeof(char));
    if (sequenza == NULL) {
        printf("Spazio insufficiente");
        exit(0);
    }
    sequenza[conta_passi-1] = dir;
}

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
    }
}

void passo(char dir){
    
    switch (dir) {
        case 'N':
            
            break;
            
        case 'S':
            verifica_cella(1, 0, dir);
            break;
            
        case 'E':
            verifica_cella(0, 1, dir);
            break;
            
        case 'O':
            verifica_cella(0, -1, dir);
            break;
    }
    
}

void stampa_mappa(void){
    system("clear");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%c", mappa[i][j]);
        }
        if (i == r-4) {
            printf("    Sequenza: ");
            for (int i = 0; i < conta_passi; i++) {
                printf("%c", sequenza[i]);
            }
        }
        if (i == r-3) printf("    Trapani: %d", trapani);
        if (i == r-2) printf("    Lunghezza: %d", lunghezza);
        if (i == r-1) printf("    Punteggio: %d", punteggio);
        printf("\n");
    }
}

void get_move(void){
    conta_passi++;
    char c = getchar();
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
    mappe(1);
    stampa_mappa();
    
    get_move();
    //printf("%c", c);
    
    flushMap();
    return 0;
}
