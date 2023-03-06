extern char** mappa; //mappa
extern int lunghezza; //lunghezza coda
extern int conta_passi;
extern int x; //testa
extern int y; //testa
extern char* sequenza;
extern int c;
extern int r;

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