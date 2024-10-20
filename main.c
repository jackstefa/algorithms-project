#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_LEN 15
#define BUFFER_SIZE 3000
#define MAX_INT 200000000
#define MAX_MEM 99999999

typedef struct Nodo{
    unsigned int indice;
    unsigned int valore;
} Nodo;

typedef struct Grafo{
    unsigned int somma;
    unsigned int indice;
} Grafo;


void AggiungiGrafo(unsigned int **PtrMatrix, unsigned int n, char *buffer);
unsigned int SommaCammini(unsigned int **PtrMatrix, unsigned int n);
struct Nodo TrovaMinimo(unsigned int **PtrMatrix, unsigned int row, unsigned int n);
void CountingSort(struct Grafo *PtrGrafo, unsigned int *Classifica, int lenght, int k);

int main() {
    unsigned int RetUnsignedInt;
    char *RetChar;
    char buffer[BUFFER_SIZE];
    unsigned int n, k, i, somma;
    unsigned int **PtrMatrix;
    char comando[COMMAND_LEN];
    int indice = -1;
    //int cnt = 1;
    struct Grafo *PtrGrafo;
    unsigned int *Classifica;

    //TEST
    //unsigned int j;

    RetUnsignedInt = scanf("%u", &n);
    RetUnsignedInt = scanf("%u", &k);


    PtrMatrix = (unsigned int **) malloc(n * sizeof(unsigned int *));
    for (i = 0; i < n; i++) {
        PtrMatrix[i] = (unsigned int *) malloc(n * sizeof(unsigned int));
    }

    PtrGrafo = (struct Grafo *) malloc(MAX_MEM * sizeof(struct Grafo *));

    Classifica = (unsigned int *) malloc(k * sizeof(unsigned int *));

    RetChar = fgets(comando, COMMAND_LEN, stdin);

    while (1) {

        RetChar = fgets(comando, COMMAND_LEN, stdin);

        if (RetChar == NULL) {
            //free(Classifica);
            exit(0);
        }

        if (strcmp(comando, "AggiungiGrafo\n") == 0) {

            indice++;

            /*
            if(indice!=0) {
                if (indice % (MULT_COEFF * cnt) == 0) {
                    PtrGrafo = (struct Grafo *) realloc(PtrGrafo, ((indice) + MULT_COEFF));
                    cnt++;
                }
            }
            */

            AggiungiGrafo(PtrMatrix, n, buffer);
            somma = SommaCammini(PtrMatrix, n);

            PtrGrafo[indice].indice = indice;
            PtrGrafo[indice].somma = somma;


            //TEST VALORE SOMMA
            //printf("la somma è: %u\n", somma);

            //TEST VALORI ASSEGNATI
            /*
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    printf("%u ", PtrMatrix[i][j]);
                }
                printf("\n");
            }
            */
        }

        if (strcmp(comando, "TopK\n") == 0) {

            //TEST
            //printf("stampo classifica\n");

            /*
            for (i = 0; i < indice+1; i++) {
                printf("%u ", PtrGrafo[i].indice);
                printf("%u", PtrGrafo[i].somma);
                printf("\n");
            }
            */




            if(indice+1<=k && indice != -1){
                for(i=0;i<indice;i++){
                    printf("%u ", PtrGrafo[i].indice);
                }
                printf("%u", PtrGrafo[i].indice);
            }


            else if(indice != -1){
                CountingSort(PtrGrafo, Classifica, indice+1, k);


                for(i=1;i<=k-1;i++){
                    printf("%u ", Classifica[i]);
                }
                printf("%u", Classifica[i]);


            }
            printf("\n");


        }
    }

        if (RetUnsignedInt) {}
        if (RetChar) {}

        return 0;
}


void AggiungiGrafo(unsigned int **PtrMatrix, unsigned int n, char *buffer) {
        char *RetValue;
        unsigned int i, val, index;
        unsigned int r = 0;
        for (i = 0; i < n; i++) {                   //scorro le righe in ingresso
            RetValue = fgets(buffer, BUFFER_SIZE, stdin);               //prendo in input una riga
            val = 0;
            index = 0;
            while (buffer[index] != '\n') {

                if (buffer[index] ==
                    ',') {                             //le cifre del numero sono finite, quindi assegno il valore alla cella
                    if (i == r) {                                          //metto a 0 gli autoanelli
                        PtrMatrix[i][r] = 0;
                    } else {
                        PtrMatrix[i][r] = val;
                        if (PtrMatrix[i][r] == 0) {                         //se un nodo è irraggiungibile, lo metto a infinito (per Dijkstra)
                            PtrMatrix[i][r] = MAX_INT;
                        }
                    }
                    r++;                                                //scorro alla prossima cella della matrice
                    index++;                                            //scorro al prossimo carattere della stringa
                    val = 0;                                            //ri-inizializzo val
                } else {
                    //se le cifre del numero non sono finite
                    val = val * 10 + (buffer[index] - '0');             //aggiorno val
                    index++;
                }
            }
            if (i == r) {
                PtrMatrix[i][r] = 0;              //stringa finita, assegno l'ultimo numero all'ultima cella
            } else {
                PtrMatrix[i][r] = val;
                if (PtrMatrix[i][r] == 0) {             //se un nodo è irraggiungibile, lo metto a infinito (per Dijkstra)
                    PtrMatrix[i][r] = MAX_INT;
                }
            }
            r = 0;
        }

        if (RetValue) {}

    }

unsigned int SommaCammini(unsigned int **PtrMatrix, unsigned int n) {
    Nodo nodo;
    unsigned int i;
    unsigned int somma;
    nodo = TrovaMinimo(PtrMatrix, 0, n);
    PtrMatrix[0][nodo.indice] = 0;
    somma = nodo.valore;
    while (nodo.valore != 0 && nodo.indice != 0) {
        for (i = 0; i < n; i++) {
            if (PtrMatrix[nodo.indice][i] == 0) {}
            else {
                if ((PtrMatrix[nodo.indice][i] + nodo.valore) < PtrMatrix[0][i]) {
                    PtrMatrix[0][i] = PtrMatrix[nodo.indice][i] + nodo.valore;
                }
            }
        }
        nodo = TrovaMinimo(PtrMatrix, 0, n);
        PtrMatrix[0][nodo.indice] = 0;
        somma = somma + nodo.valore;
    }
    return somma;
}

struct Nodo TrovaMinimo(unsigned int **PtrMatrix, unsigned int row, unsigned int n) {
Nodo nodo;
    unsigned int i;
    unsigned int min = 0;
    unsigned int flag = 0;
    unsigned int index = 0;

    for (i = 0; i < n; i++) {
        if (PtrMatrix[row][i] == 0) {}               //skippo se trovo uno 0
        else if (PtrMatrix[row][i] == MAX_INT) {}     //skippo se trovo un inf
        else {
            if (flag == 0) {                            //assegno a min il primo numero valido che trovo
                min = PtrMatrix[row][i];
                index = i;
                flag = 1;
            } else {
                if (PtrMatrix[row][i] < min) {
                    min = PtrMatrix[row][i];
                    index = i;
                }
            }
        }
    }
    nodo.indice = index;
    nodo.valore = min;
    return nodo;
}

void CountingSort(struct Grafo *PtrGrafo, unsigned int *Classifica, int lenght, int k){
    unsigned int max;
    long int i;
    unsigned int *C;
    max = 0;
    //max = PtrGrafo[0].somma;
    //min = PtrGrafo[0].somma;

    //Calcolo max e min
    for(i=0;i<lenght;i++){
        if(PtrGrafo[i].somma > max){
            max = PtrGrafo[i].somma;
        }
        /*
        else if(PtrGrafo[i].somma < min){
            min = PtrGrafo[i].somma;
        }
        */
    }

    //Costruisco array Counting e lo inizializzo
    C = (unsigned int *)malloc((max+1)*sizeof(unsigned int *));
    for(i=0;i<max+1;i++){
        C[i] = 0;
    }

    //Faccio il counting (funziona)
    for(i=0;i<lenght;i++){
        //ho cancellato perchè i nodi non raggiungibili sono da considerare in classifica
        //if(PtrGrafo[i].somma==0){}
        C[PtrGrafo[i].somma] = C[PtrGrafo[i].somma] + 1;
    }

    //TEST del counting
    /*
    for(i=0;i<=max;i++) {
        printf("%u  %u\n", i, C[i]);
    }
    */

    //Sommo il valore corrente al successivo (funziona)
    for(i=0;i<max;i++){
        C[i+1] = C[i+1] + C[i];

        //TEST
        //printf("%u\n", C[i+1]);
    }


    //ordino

    for(i=lenght-1;i>=0;i--){
        if((C[PtrGrafo[i].somma]) > k){
            C[PtrGrafo[i].somma] = C[PtrGrafo[i].somma] - 1;
        }

        else{
            Classifica[(C[PtrGrafo[i].somma])] = PtrGrafo[i].indice;
            C[PtrGrafo[i].somma] = C[PtrGrafo[i].somma] - 1;
        }
    }



    /*
    //Ordino
    for(i=0;i<lenght;i++) {
        // if (PtrGrafo[i].somma == 0) {}

        if ((C[PtrGrafo[i].somma]) <= k) {
            Classifica[(C[PtrGrafo[i].somma])] = PtrGrafo[i].indice;
            C[PtrGrafo[i].somma] = C[PtrGrafo[i].somma] - 1;
        }
    }
    */



    //free(C);
}


