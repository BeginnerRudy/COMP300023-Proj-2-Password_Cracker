#include "pwd_utility.h"

/*This function is responsible for read the pwdNsha256 into a 2D array of BYTE*/
pwd_sha256_t* pwd_reader(char* filePath){
    // initialize some variable for storing file
    unsigned char * buffer = 0;
    long length;
    FILE * f = fopen (filePath, "rb");

    // read the file and get the file length
    if (f){
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer){
            fread (buffer, sizeof(unsigned int), length, f);
        }
    fclose (f);
    }

    // delcare and initialize for storing sha256 of pwd

    // calculate number of pwd inside given file
    int count = length/SIZE_OF_SHA256;
    pwd_sha256_t* pwdNsha256 = (pwd_sha256_t*)malloc(sizeof(pwd_sha256_t));
    pwdNsha256->pwd_sha256_list = (BYTE**)malloc(count*sizeof(BYTE*));
    pwdNsha256->pwd_count = count;

    // allocate memory to each pwd stored in pwd_sha256_list
    for (int i = 0; i < count; i++){
        pwdNsha256->pwd_sha256_list[i] = (BYTE*)malloc(SIZE_OF_SHA256*sizeof(BYTE));
    }

    // storing sha256
    if (buffer){
        for (int i = 0; i < count; i++){
            for (int j = 0; j < 32; j++){
                pwdNsha256->pwd_sha256_list[i][j] = buffer[i*SIZE_OF_SHA256+j];
            }
        }
    }

    return pwdNsha256;
}


/*This function takes guess and sha256 of pwds and check if the guess matches*/
char* is_cracked(pwd_sha256_t* pwdNsha256, char* guess){
    // hash the guess to get its sha256
    BYTE* hash_guess = str_to_sha_256(guess);
    // compare the sha256 of guess to each pwd's sha256
    for (int i = 0; i < pwdNsha256->pwd_count; i++){
        // if guess matches, print it out and return it
        if (memcmp(pwdNsha256->pwd_sha256_list[i], hash_guess, SIZE_OF_SHA256) == 0){
            printf("%s %d\n", guess, i+1); // increment 1 to make the first pwd with index 1
            free(hash_guess);
            return guess;
        }
    }
    // free guess
    free(hash_guess);

    // guess matches nothing, return GUESS_FAILED
    return GUESS_FAILED;
}
