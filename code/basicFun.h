/**
 @file
 @brief File che contiene funzioni utilizzate spesso
 @author Delton Nicolas <896295@stud.unive.it>
 */

#include <stdbool.h>

extern char** mappa;
extern int n_map;
/**Punteggio totale**/
int punteggio = 1000;
/**Lunghezza dello snake**/
int lunghezza = 1;
/**Numero di trapani**/
int trapani = 0;
int conta_passi = 0;
char* sequenza;
/**Dimensione della mappa (colonne)**/
int c;
/**Dimensione della mappa (righe)**/
int r;
/**Coordinata x della testa**/
int x;
/**Coordinata y della testa**/
int y;

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
 @brief Funzione eseguita in modalità automatica quanto la testa trova un vicolo ceco o non riesce a risolvere il labirinto
 */
void restart(void){
    mappe(n_map);
    remove(sequenza);
    sequenza = malloc(sizeof(char)); 
    trapani = 0;
    punteggio = 1000;
    lunghezza = 1;
    conta_passi = 0;
}

/**
 @brief Funzione eseguita quanto si ha perso
 */
void end(void){
    printf("TRY AGAIN\n");
    exit(0);
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
    
    if (lunghezza == 0) end();
}

/**
 @brief Funzione eseguita quanto la testa trova un imprevisto in modalità automatica
 */
void imprevisto_a(void){
    punteggio /= 2;
    lunghezza /= 2;
    
    if (lunghezza == 0) {
        restart();
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
 @brief Funzione eseguita quanto la testa trova l'uscita in modalità automatica
 */
void win_a(void){
    printf("WIN\n");
    exit(0);
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
bool verifica_cella(int x0, int y0, char dir){
    if (punteggio <= 0) restart();
    if (x+x0 >= 0 && x+x0 < r && y+y0 >= 0 && y+y0 < c){
        if (mappa[x+x0][y+y0] == '$') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            moneta();
            aggiorna_coda();
            return true;
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
            return true;
        }
        else if (mappa[x+x0][y+y0] == 'T') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            trapano();
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == '!') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            imprevisto();
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == ' ') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == '#' && trapani > 0) {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            usa_trapano();
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == '.') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            lunghezza = verifica_morso();
            aggiorna_coda();
            return true;
        }
    }
    return false;
}

/**
 @brief Funzione che verifica se è possibile effettuare la mossa desiderata e in caso positivo la fa, modalità automatica
 @param x0 Valore di dove la testa deve spostarsi verticalmente
 @param y0 Valore di dove la testa deve spostarsi orizzontalmente
 @param dir Valore della direzione utilizzato per salvare le mosse effettuate
 */
bool verifica_cella_a(int x0, int y0, char dir){
    if (punteggio <= 0) restart();
    if (x+x0 >= 0 && x+x0 < r && y+y0 >= 0 && y+y0 < c){
        if (mappa[x+x0][y+y0] == '$') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            moneta();
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == '_') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            aggiorna_coda();
            win_a();
            return true;
        }
        else if (mappa[x+x0][y+y0] == 'T') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            trapano();
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == '!') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            imprevisto_a();
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == ' ') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == '#' && trapani > 0) {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            usa_trapano();
            aggiorna_coda();
            return true;
        }
        else if (mappa[x+x0][y+y0] == '.') {
            salva_passo(dir);
            mappa[x][y] = ' ';
            x += x0;
            y += y0;
            mappa[x][y] = 'o';
            lunghezza = verifica_morso();
            aggiorna_coda();
            return true;
        } //else restart();
    }
    else {
        restart();
    }
    return false;
}