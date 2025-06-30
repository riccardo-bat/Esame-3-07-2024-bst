#ifndef HOTEL_H 
    #define HOTEL_H

    #define MAX_NAMEHOTEL_LEN 21
    #define MAX_PLACE_LEN 21

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct{
        char nomeHotel[MAX_NAMEHOTEL_LEN];
        char luogo[MAX_PLACE_LEN];
    }tipo_inf;

    //primitive tipo_inf

    /**
     * @brief Primitiva per la copia del contenuto di src in dest
     * 
     * @param dest 
     * @param src 
     */
    void copy(tipo_inf *dest, tipo_inf src); 

    /**
     * @brief Comparazione di due oggetti di tipo tipo_inf
     * se a < b return -1
     * se a> b return 1 
     * se a = b return 0
     * 
     * @param a 
     * @param b 
     * @return int 
     */
    int compare(tipo_inf a, tipo_inf b);

    /**
     * @brief Funzione di print per un oggetto di tipo tipo_inf
     * 
     * @param obj 
     */
    void print_tipo_inf(tipo_inf obj);



#endif