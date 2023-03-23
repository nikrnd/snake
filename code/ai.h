extern char** mappa; //mappa
extern int x; //testa
extern int y; //testa
extern int c;
extern int r;

void auto_solve(void){
    if (y == 0) {
        verifica_cella(0, 1, 'E');
        stampa_mappa();
    }
    
}