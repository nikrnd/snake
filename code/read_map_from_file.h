/**
 @file
 @brief File che gestisce la lettura della mappa da file
 @author Delton Nicolas <896295@stud.unive.it>
 */

extern char** mappa;
extern int c;
extern int r;
extern int x;
extern int y;

/**
 @brief Funzione che salva il numero di righe e colonne della mappa inserita nel file
 */
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

/**
 @brief Funzione che legge la mappa dal file
 */
void readFromFile(void){

    FILE* ptr;
    ptr = fopen("mapInput.txt", "r");
 
    int err_counter = 0;
    if (ptr == NULL) {
        err_counter = 0;
        fclose(ptr);
        FILE* new = fopen("mapInput.txt", "w");
        fclose(new);
        FILE* ptr = fopen("mapInput.txt", "r");
        fseek (ptr, 0, SEEK_END);
        fclose(ptr);
        while (0 == ftell(ptr)) {
            err_counter++;
            system("clear");
            printf("Errore numero %d: File appena creato, inserisci la mappa e premi qualunque tasto\n", err_counter);
            _getch();
            FILE* ptr = fopen("mapInput.txt", "r");
            fseek (ptr, 0, SEEK_END);
            fclose(ptr);
        }
        
        readFromFile();
    } else if (ptr != NULL) {
        err_counter = 0;
        FILE* ptr = fopen("mapInput.txt", "r");
        fseek (ptr, 0, SEEK_END);
        fclose(ptr);
        while (0 == ftell(ptr)) {
            err_counter++;
            system("clear");
            printf("Errore numero %d: File appena creato, inserisci la mappa e premi qualunque tasto\n", err_counter);
            _getch();
            FILE* ptr = fopen("mapInput.txt", "r");
            fseek (ptr, 0, SEEK_END);
            fclose(ptr);
        }
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
    
    fclose(ptr);
}