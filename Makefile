#Variabili utili per le regole
CC = gcc
CFLAGS = -Wall

#Regole

#fase di linking - generazione del file eseguibile
esame: compito.o hotel.o bst.o
	$(CC) $(CFLAGS) -o $@ $^
	del /F *.o *.out *.gch


#fase di traduzione - generazione dei file oggetto 
compito.o: compito.c hotel.h bst.h 
	$(CC) $(CFLAGS) -c $^

hotel.o: hotel.c hotel.h	
	$(CC) $(CFLAGS) -c $^

bst.o: bst.c bst.h hotel.h	
	$(CC) $(CFLAGS) -c $^



clean: 
	del /F *.o *.out *.exe *.gch

:PHONY: clean 