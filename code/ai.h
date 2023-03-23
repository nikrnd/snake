#include <unistd.h>

extern char** mappa; //mappa
extern int x; //testa
extern int y; //testa
extern int c;
extern int r;

void auto_solve(void){

    sleep(1);

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