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

void mid_moves(void){

    /* NOL VA
    if (sequenza[conta_passi-1] == 'N')
        if (!verifica_cella(-1, 0, 'N'))
        if (!verifica_cella(0, 1, 'E'))
        if (!verifica_cella(0, -1, 'O'))
            ;

    if (sequenza[conta_passi-1] == 'S')
        if (!verifica_cella(1, 0, 'S'))
        if (!verifica_cella(0, 1, 'E'))
        if (!verifica_cella(0, -1, 'O'))
            ;

    if (sequenza[conta_passi-1] == 'E')
        if (!verifica_cella(0, 1, 'E'))
        if (!verifica_cella(-1, 0, 'N'))
        if (!verifica_cella(1, 0, 'S'))
            ;

    if (sequenza[conta_passi-1] == 'O')
        if (!verifica_cella(0, -1, 'O'))
        if (!verifica_cella(-1, 0, 'N'))
        if (!verifica_cella(1, 0, 'S'))
            ;
    */

    /* QUESTO ANCORA MANCO :-)
    if (sequenza[conta_passi-1] != 'N' && !verifica_cella(1, 0, 'S')) 
            if (sequenza[conta_passi-1] != 'O' && !verifica_cella(0, 1, 'E'))
                if (sequenza[conta_passi-1] != 'S' && !verifica_cella(-1, 0, 'N'))
                    if (sequenza[conta_passi-1] != 'E' && !verifica_cella(0, -1, 'O'))
                        ;
    */
}

void last_move(void){
    if (mappa[x+1][y] == '_') verifica_cella(-1, 0, 'N');
    else if (mappa[x-1][y]== '_') verifica_cella(1, 0, 'S');
    else if (mappa[x][y+1] == '_') verifica_cella(0, 1, 'E');
    else if (mappa[x][y-1] == '_') verifica_cella(0, -1, 'O');
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

        last_move();
    }
    
}