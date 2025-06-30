#include "hotel.h"
#include "bst.h"
#include <stdbool.h>

#define MAX_CARATTERI_BUFFER 100

//prototipi 
int int_input(char* msg, int minimum_value, int max_value, size_t maxLengthinput);
void string_input(char* msg, char* dest, size_t maxLengthInput);
void create_bst(FILE* fp, bst* bst_hotels);
void stampa(bst t);
void ricerca(bst, int, bool);
int media(bst bst_hotels, int threshold, char* place);
void per_luogo(bst bst_hotels, char* place);

int main(){
    //PUNTO 1   
    //apertura del file hotel.txt
    FILE* file_hotel = fopen("hotel.txt", "r");
    if(file_hotel == NULL){
        printf("\nERRORE NELL'APERTURA DEL FILE");
        exit(1);
    }

    //lettura del file hotel.txt per acquisire i dati
    bst bst_hotels = NULL;
    create_bst(file_hotel, &bst_hotels);

    stampa(bst_hotels);


    //punto 2a
    printf("\n\n--------------------------------------------------");
    int threshold_stelle = int_input("\nInserire il numero di stelle come limite: ", 1, 5, 1);
    printf("\n1) valuta gli hotel con le stelle > di %d. \n0) altrimenti", threshold_stelle);
    bool maggiori = int_input("\nValore: ", 0, 1, 1); 

    //1 = true, 0 = false
    ricerca(bst_hotels, threshold_stelle, maggiori);

    //punto 2b
    printf("\n\n--------------------------------------------------");
    char place[MAX_PLACE_LEN]; 
    string_input("\nInserire il luogo per il calcolo della media: ", place, MAX_PLACE_LEN);
    threshold_stelle = int_input("\nInserire il numero di stelle come limite: ", 1, 5, 1);

    printf("\n\nIl calcolo della media, stabiliti i parametri [soglia = %d, luogo = '%s'], risulta %d",
         threshold_stelle, place, media(bst_hotels, threshold_stelle, place));



    //punto 3
    printf("\n\n--------------------------------------------------");
    string_input("\nInserire il luogo di ricerca degli hotel: ", place, MAX_PLACE_LEN);
    per_luogo(bst_hotels, place);



    //chiusura dei file aperti
    if(fclose(file_hotel) == EOF){
        printf("\n\nERRORE NELLA CHIUSURA DEI FILE");
        exit(1);
    }

    printf("\n\n");
    return 0;
}

int int_input(char* msg, int minimum_value, int max_value, size_t maxLengthinput){
    printf("%s", msg); 
    char buffer[maxLengthinput+1]; //includo il '\0'

    while(fgets(buffer, (maxLengthinput+1), stdin) == NULL){
        printf("\n\t-Input non valido, reinserire: ");
    }

    //a questo punto devo pulire il buffer
    int c; 
    while((c = getchar()) != '\n' && c != EOF)
        ;

    char* endpoint = NULL;
    int to_return = (int) strtol(buffer, &endpoint, 10);

    //se nessun carattere è stato convertito
    if(endpoint == buffer || to_return < minimum_value || to_return > max_value){
        printf("\n\nERRORE NELL'ACQUISIZIONE DELL'INPUT AL PUNTO 2A");
        return int_input(msg, minimum_value, max_value, maxLengthinput);
    }

    return to_return;
}

void string_input(char* msg, char* dest, size_t maxLengthInput){
    printf("%s", msg);
    char buffer[maxLengthInput+1]; 

    while(fgets(buffer, maxLengthInput+1, stdin) == NULL){
        printf("\n\t- Reinserire: ");
    }

    //rimpiazzo il primo '\n' con il terminatore
    buffer[strcspn(buffer, "\n")] = '\0'; //al posto del "\n" inserisco il terminatore
    strcpy(dest, buffer);
}


/**
 * @brief Creo un albero bst leggendo un file 
 * 
 * @param fp 
 * @param bst_hotels 
 */
void create_bst(FILE* fp, bst* bst_hotels){
    //Convenzione: la prima riga indica il numero di hotel totali 
    //per ogni hotel --> 3 righe (stelle, nome, luogo)

    int riga_per_hotel = 0; 
    char buffer[MAX_CARATTERI_BUFFER]; 
    char* endptr;

    //variabili temporanee per la raccolta dei dati
    tipo_key chiave; 
    tipo_inf tmp; 

    while(fgets(buffer, MAX_CARATTERI_BUFFER-1, fp) != NULL){
        //se sto leggendo la prima riga, non faccio nulla
        if(riga_per_hotel != 0){
            buffer[strcspn(buffer, "\n")] = '\0'; //elimino la prima occorenza del \n
            
            //in base alla riga che sto leggendo viene considerato un valore diverso
            //se sto leggendo la prima riga (riferita all'hotel), sto leggendo il numero di stelle
            if(riga_per_hotel == 1){
                //leggo la chiave
                //printf("\nStelle lette: %s", buffer);
                chiave = (int) strtol(buffer, &endptr, 10); //leggo il numero in base 10 
                if(endptr == buffer){
                    printf("\n\nERRORE NELLA LETTURA");
                    exit(1);
                }
            } else if(riga_per_hotel == 2){
                //printf("\nNome hotel: %s", buffer);
                //leggo il nome dell'hotel
                strcpy(tmp.nomeHotel, buffer);
            } else{
                //leggo il luogo dell'hotel
                //printf("\nLuogo hotel: %s", buffer);
                strcpy(tmp.luogo, buffer);
            }

        } //else --> non faccio nulla

        //aggiorno il numero della riga che sto leggendo, considerando che per ogni hotel si scrivono 3 righe
        if(riga_per_hotel == 3){ //se ho finito di leggere un hotel
            //inserisco l'hotel nel bst
            bst_insert(bst_hotels, bst_newNode(chiave, tmp));
            //ripristino la riga 
            riga_per_hotel = 1;
        } else
            riga_per_hotel++; 

    }
}

/**
 * @brief Stampa del BST in ordine decrescente per chiave
 * 
 * @param t 
 */
void stampa(bst t){
    //caso base --> albero vuoto
    
    if(t == NULL) return; 

    stampa(t->left);
    //stampa del nodo
    print_tipo_inf(t->inf);
    printf(" --> ");
    print_key(t->key);

    stampa(t->right);
}

/**
 * @brief Tramite una visit DFS valuto maggiore per stampare gli hotel con un numero di stelle
 * > threshold se maggiori = 1 = true, i minori altrimenti
 * 
 * @param bst_hotels 
 * @param threshold 
 * @param maggiori 
 */
void ricerca(bst bst_hotels, int threshold, bool maggiori){
    //caso base --> albero vuoto
    if(bst_hotels == NULL) return;

    //sfrutto la stampa INORDER per stampare secondo l'ordine decrescente delle chiavi
    ricerca(bst_hotels->left, threshold, maggiori);
    
    //stampo il nodo
    //se maggiori = true stampo solo gli hotel con un numero di stelle > soglia
    if((maggiori && bst_hotels->key > threshold) || (!maggiori && bst_hotels->key <= threshold)){
        print_tipo_inf(bst_hotels->inf);
        printf(" --> ");
        print_key(bst_hotels->key);
    } //else --> se maggiori = true ma la chiave è minore (e viceversa) non stampo nulla

    //se la chiave del nodo attuale è già minore della soglia, non vado a vedere i nodi minore del nodo stesso
    ricerca(bst_hotels->right, threshold, maggiori);
}

/**
 * @brief Calcolo il numero di hotel nel luogo specificato con un #stelle > soglia. Per contarli 
 * in ordine decrescente uso una DFS in order
 * 
 * @param bst_hotels 
 * @param threshold 
 * @param place 
 * @return int 
 */
int media(bst bst_hotels, int threshold, char* place){
    if(bst_hotels == NULL) return 0; 
    int tot = 0;

    //visita in order
    tot += media(bst_hotels->left, threshold, place);

    //analizzo il nodo 
    if(strcmp(bst_hotels->inf.luogo, place) == 0 && bst_hotels->key > threshold)
        tot++; 

    //se il nodo attule ha una chiave già minore della soglia, è inutile andare a destra verso nodi con chiavi più piccole
    tot += media(bst_hotels->right, threshold, place);
    return tot;
}

/**
 * @brief Stampo gli hotel che si trovano in place. per stamparli in ordine decrescente utilizzo una DFS inorder
 * 
 * @param bst_hotels 
 * @param place 
 */
void per_luogo(bst bst_hotels, char* place){
    //caso base --> albero vuoto
    if(bst_hotels == NULL) return; 

    per_luogo(bst_hotels->left, place); 

    //analizzo il nodo
    if(strcmp(bst_hotels->inf.luogo, place) == 0){
        print_tipo_inf(bst_hotels->inf);
        printf(" --> ");
        print_key(bst_hotels->key);
    }

    per_luogo(bst_hotels->right, place);
}