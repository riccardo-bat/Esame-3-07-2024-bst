#include "hotel.h"
#include "bst.h"

#define MAX_CARATTERI_BUFFER 100

//prototipi 
void create_bst(FILE* fp, bst* bst_hotels);
void stampa(bst t);

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



    //chiusura dei file aperti
    if(fclose(file_hotel) == EOF){
        printf("\n\nERRORE NELLA CHIUSURA DEI FILE");
        exit(1);
    }

    printf("\n\n");
    return 0;
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