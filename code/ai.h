#include <unistd.h>
#define DELAY 100000

extern char** mappa; //mappa
extern int x; //testa
extern int y; //testa
extern int c;
extern int r;
extern char* sequenza;
extern int conta_passi;

void first_move(void){
    if (y == 0) {
        verifica_cella(0, 1, 'E');
        stampa_mappa();
    } else if (y == c-1) {
        verifica_cella(0, -1, 'O');
        stampa_mappa();
    } else if (x == 0) {
        verifica_cella(1, 0, 'S');
        stampa_mappa();
    } else if (y == r-1) {
        verifica_cella(-1, 0, 'N');
        stampa_mappa();
    }
}

void last_move(void){
    if (mappa[x+1][y] == '_') verifica_cella(-1, 0, 'N');
    else if (mappa[x-1][y]== '_') verifica_cella(1, 0, 'S');
    else if (mappa[x][y+1] == '_') verifica_cella(0, 1, 'E');
    else if (mappa[x][y-1] == '_') verifica_cella(0, -1, 'O');
}

void mid_moves() {
    
}

void auto_solve(void){

    usleep(DELAY);

    first_move();

    usleep(DELAY);

    while (true)
    {
        mid_moves();

        stampa_mappa();

        usleep(DELAY);

    }
    
}