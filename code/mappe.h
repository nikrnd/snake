/**
 @file
 @brief Mappe de default
 @author Delton Nicolas <896295@stud.unive.it>
 */

#include <time.h>

extern char** mappa;
extern int c, r, x, y;

void genera_elementi(int nMonete, int nTrapani, int nImprevisti);

int n_map;
/**
 @brief Funzione che genera la mappa desiderata
 @param n Inserire codice della mappa da selezionare
 */
void mappe(int n){
    n_map = n;
    switch (n) {
        case 1:
            c = 20;
            r = 10;
            mappa = (char**)malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = (char*)malloc(sizeof(char) * c);
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
            genera_elementi(20, 2, 2);
            break;
        
        case 2:
            c = 20;
            r = 10;
            mappa = (char**)malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = (char*)malloc(sizeof(char) * c);
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
            mappa = (char**)malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = (char*)malloc(sizeof(char) * c);
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
            mappa = (char**)malloc(sizeof(char*) * r);
            for (int i = 0; i < r; i++) {
                mappa[i] = (char*)malloc(sizeof(char) * c);
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
                if(rand()%2 && rand()%2 && rand()%2 && nMonete > 0){
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