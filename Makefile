CC = gcc
CFLAGS = -Wall

EXE = crack
OBJ = crack.o sha256.o sha256_utility.o pwd_utility.o brute_force.o good_guess.o checking.o


$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)


sha256.o: sha256.c sha256.h
	$(CC) $(CFLAGS) -c sha256.c

sha256_utility.o: sha256_utility.c sha256_utility.h
	$(CC) $(CFLAGS) -c sha256_utility.c

pwd_utility.o: pwd_utility.c pwd_utility.h
	$(CC) $(CFLAGS) -c pwd_utility.c

brute_force.o: brute_force.c brute_force.h
	$(CC) $(CFLAGS) -c brute_force.c

good_guess.o: good_guess.c good_guess.h
	$(CC) $(CFLAGS) -c good_guess.c

checking.o: checking.c checking.h
	$(CC) $(CFLAGS) -c checking.c

crack.o: crack.c
	$(CC) $(CFLAGS) -c crack.c

clean:
	rm -f $(OBJ) $(EXE)
