# Syntaxe
# -------
# cible : dependances
#	commande # utiliser obligatoirement la touche TAB
CC = gcc
EXEC = finder.exe
OBJ = finder.o ListFile.o 
CFLAGS = -Wall

all : $(EXEC)
	./$(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o finder.exe

finder.o : finder.c
	$(CC) -c finder.c

ListFile.o : ListFile.c
	$(CC) -c ListFile.c


run : $(EXEC)
	./$(EXEC)
clean :
	rm -rf *.o