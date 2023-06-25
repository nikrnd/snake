#include <unistd.h>
#define DELAY 100

extern char** mappa; //mappa
extern int x; //testa
extern int y; //testa
extern int c;
extern int r;
extern char* sequenza;
extern int conta_passi;
extern int n_map;

void last_move(void);

void first_move(void){
    if (y == 0) {
        verifica_cella_a(0, 1, 'E');
        //stampa_mappa();
    } else if (y == c-1) {
        verifica_cella_a(0, -1, 'O');
        //stampa_mappa();
    } else if (x == 0) {
        verifica_cella_a(1, 0, 'S');
        //stampa_mappa();
    } else if (y == r-1) {
        verifica_cella_a(-1, 0, 'N');
        //stampa_mappa();
    }
    //stampa_mappa();
}

void mid_moves(void) {
    int r;
    int try_count = 0, x_prec = x, y_prec = y;
        last_move();
        if (x_prec == x && y_prec == y && try_count > 39) restart();
        else if (x_prec == x && y_prec == y) try_count++;
        else try_count = 0;

        x_prec = x;
        y_prec = y;

        r = (rand()%9)/2;
        switch (r)
        {
        case 0: //N
            if (last() != 'S') verifica_cella_a(-1, 0, 'N');
            break;
        
        case 1: //S
            if (last() != 'N') verifica_cella_a(1, 0, 'S');
            break;

        case 2: //E
            if (last() != 'O') verifica_cella_a(0, 1, 'E');
            break;

        case 3: //O
            if (last() != 'E') verifica_cella_a(0, -1, 'O');
            break;
        }

        //stampa_mappa();
        //usleep(DELAY);
}

void last_move(void){
    if (x+1 < r && mappa[x+1][y] == '_') verifica_cella_a(-1, 0, 'N');
    else if (x-1 >= 0 && mappa[x-1][y]== '_') verifica_cella_a(1, 0, 'S');
    else if (y+1 < c && mappa[x][y+1] == '_') verifica_cella_a(0, 1, 'E');
    else if (y-1 >= 0 && mappa[x][y-1] == '_') verifica_cella_a(0, -1, 'O');
}

void auto_solve(void){

    //usleep(DELAY);

    srand(time(NULL));
    //usleep(DELAY);

    for (int i = 0; 1 == 1; i++) {
        stampa_mappa();
        first_move();
        mid_moves();
        usleep(DELAY);
        if (i == (c*r)/2) restart();
    }
    
}