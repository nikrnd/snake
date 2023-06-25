extern char** mappa; //mappa
extern int lunghezza; //lunghezza coda

/**Numero di passi effettuati**/
extern int conta_passi;
extern int x; //testa
extern int y; //testa

/**Array dinamico contenente la sequenza di mosse effettuate**/
extern char* sequenza;
extern int c;
extern int r;

char last(void){
    return sequenza[(sizeof(*sequenza)/sizeof(char))-1];
}

void aggiorna_coda(void){
    int tx = x, ty = y;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (mappa[i][j] == '.')
            {
                mappa[i][j] = ' ';
            }
            
        }
        
    }
    
    for (int i = conta_passi; i > conta_passi - lunghezza; i--)
    {
        //printf("%c", sequenza[i]);
        switch (sequenza[i]) {
            case 'N':
                tx += 1;
                mappa[tx][ty] = '.';
                break;
            
            case 'S':
                tx -= 1;
                mappa[tx][ty] = '.';
                break;

            case 'E':
                ty -= 1;
                mappa[tx][ty] = '.';
                break;

            case 'O':
                ty += 1;
                mappa[tx][ty] = '.';
                break;

            default:
                break;
        }
    }
}

int verifica_morso(){
    int tx = x, ty = y;
    int conta_coda = 0;

    if ((sequenza[conta_passi-1] == 'N' && sequenza[conta_passi-2] == 'S') ||
        (sequenza[conta_passi-1] == 'S' && sequenza[conta_passi-2] == 'N') ||
        (sequenza[conta_passi-1] == 'E' && sequenza[conta_passi-2] == 'O') ||
        (sequenza[conta_passi-1] == 'O' && sequenza[conta_passi-2] == 'E'))
    {
        return 1;
    }
    

    for (int i = conta_passi; (i > conta_passi - lunghezza); i--)
    {
        //printf("%c", sequenza[i]);
        switch (sequenza[i]) {
            case 'N':
                tx += 1;
                break;
            
            case 'S':
                tx -= 1;
                break;

            case 'E':
                ty -= 1;
                break;

            case 'O':
                ty += 1;
                break;

            default:
                break;
        }
        if (mappa[tx][ty] == '.') conta_coda++;
    }

    if (!conta_coda) conta_coda++;

    return conta_coda;
}