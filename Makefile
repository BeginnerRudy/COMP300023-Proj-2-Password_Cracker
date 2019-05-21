CC = gcc
CFLAGS = -Wall

EXE = crack
OBJ = crack.o sha256.o sha256_utility.o pwd_utility.o


$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)


sha256.o: sha256.c sha256.h
	$(CC) $(CFLAGS) -c sha256.c

sha256_utility.o: sha256_utility.c sha256_utility.h
	$(CC) $(CFLAGS) -c sha256_utility.c

pwd_utility.o: pwd_utility.c pwd_utility.h
	$(CC) $(CFLAGS) -c pwd_utility.c

crack.o: crack.c
	$(CC) $(CFLAGS) -c crack.c

clean:
	rm -f $(OBJ) $(EXE)
