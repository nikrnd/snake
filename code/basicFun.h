extern char** mappa;
extern int r;

/**Punteggio totale**/
int punteggio = 1000;
/**Lunghezza dello snake**/
int lunghezza = 1;
/**Numero di trapani**/
int trapani = 0;

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
