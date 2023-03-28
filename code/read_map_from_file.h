extern char** mappa;
extern int c;
extern int r;
extern int x;
extern int y;

void getNumColsAndRows(void){
    FILE *f = fopen("mapInput.txt", "r");
	if(f == NULL)
	{
		printf("Errore");
		exit(1);
	}
	char **matrice, buffer[100];
	int righe = 0, colonne = 0, i = 0;
	
	while(!feof(f))
	{
		fgets(buffer, 100, f);
		righe++;
	}
	while(buffer[i] != '\0')
	{
		if(buffer[i] != ' ')
			colonne++;
		i++;
	}

    fclose(f);
    c = colonne+1;
    r = righe;
}

void getHeadPosition(void){

}
void readFromFile(void){

    FILE* ptr;
    ptr = fopen("mapInput.txt", "r");
 
    if (ptr == NULL) {
        fclose(ptr);
        FILE* new = fopen("mapInput.txt", "w");
        fclose(new);

        printf("File appena creato, inserisci la mappa e premi qualunque tasto");
        _getch();

        readFromFile();
    }

    getNumColsAndRows();

    //creazione mappa
    mappa = (char**)malloc(sizeof(char*) * r);
    for (int i = 0; i < r; i++) {
        mappa[i] = (char*)malloc(sizeof(char) * c);
    }

    char ch;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            ch = fgetc(ptr);
            if ((int)ch != 10 && (int)ch != -1) mappa[i][j] = ch;
            if (ch == 'o') {
                x = i;
                y = j;
            }
        }
    }

    stampa_mappa();
    get_move();
    
    fclose(ptr);
}