#include "hotel.h"

void copy(tipo_inf *dest, tipo_inf src){
    *dest = src; 
}

int compare(tipo_inf a, tipo_inf b){
    //comparo il nome dell'hotel
    int result = strcmp(a.nomeHotel, b.nomeHotel);
    if(result != 0) return result; 

    //se il nome dell'hotel è lo stesso (result = 0), considero il luogo 
    return strcmp(a.luogo, b.luogo);
}

void print_tipo_inf(tipo_inf obj){
    printf("\nL'hotel %s e' situato in/a %s", obj.nomeHotel, obj.luogo);
}