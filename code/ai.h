#include <unistd.h>

extern char** mappa; //mappa
extern int x; //testa
extern int y; //testa
extern int c;
extern int r;
extern char* sequenza;
extern int conta_passi;

void auto_solve(void){

    usleep(200000);

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

    usleep(200000);

    while (true)
    {
        if (sequenza[conta_passi-1] != 'N' && !verifica_cella(1, 0, 'S')) 
            if (sequenza[conta_passi-1] != 'O' && !verifica_cella(0, 1, 'E'))
                if (sequenza[conta_passi-1] != 'S' && !verifica_cella(-1, 0, 'N'))
                    if (sequenza[conta_passi-1] != 'E' && !verifica_cella(0, -1, 'O'))
                        ;

        stampa_mappa();

        usleep(200000);

        if (mappa[x+1][y] == '_') verifica_cella(-1, 0, 'N');
        else if (mappa[x-1][y]== '_') verifica_cella(1, 0, 'S');
        else if (mappa[x][y+1] == '_') verifica_cella(0, 1, 'E');
        else if (mappa[x][y-1] == '_') verifica_cella(0, -1, 'O');
    }
    
}