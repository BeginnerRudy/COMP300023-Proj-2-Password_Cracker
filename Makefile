CC = gcc
CFLAGS = -Wall

EXE = crack
OBJ = main.o sha256.o


$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)


sha256.o: sha256.c sha256.h
	$(CC) $(CFLAGS) -c sha256.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJ) $(EXE)
