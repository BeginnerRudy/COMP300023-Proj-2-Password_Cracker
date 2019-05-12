#define DEBUG

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

/****************************** MACROS ******************************/
#define PWD4SHA256_PATH "./pwd4sha256"
#define PWD6SHA256_PATH "./pwd6sha256"
#define GUESS_FAILED "F"

#define SIZE_OF_SHA256 32



// #define ASCII_START 32 + 65
// #define ASCII_START 32
#define ASCII_START 32 + 16
#define ASCII_END 126
#define GUSS "s"


typedef struct{
    BYTE** pwd_sha256_list;
    int pwd_count;
}pwd_sha256_t;

/*********************** FUNCTION PROTOTYPES ***********************/
pwd_sha256_t* pwd_reader(char* filePath);
void pwd_printer(char* pwd);
BYTE* str_to_sha_256(char* str);
char* is_cracked(pwd_sha256_t* pwdNsha256, char* guess);
void print_hash(BYTE* hash);

/*********************** FUNCTION DEFINITIONS ***********************/
int main(int argc, char* argv[]){
    /* read pwd4sha256*/

    if (argc == 1){
        pwd_sha256_t* pwd4sha256 = pwd_reader(PWD4SHA256_PATH);
        pwd_sha256_t* pwd6sha256 = pwd_reader(PWD6SHA256_PATH);
        // hack 4 char pwd first
        char* word4 = (char*)malloc(4*sizeof(char));
        word4[4] = '\0'; // terminate at 5th char
        for (int i = ASCII_START; i <= ASCII_END; i++){
            word4[0] = i;
            for (int j = ASCII_START; j <= ASCII_END; j++){
                word4[1] = j;
                for (int k = ASCII_START; k <= ASCII_END; k++){
                    word4[2] = k;
                    for (int p = ASCII_START; p <= ASCII_END; p++){
                        word4[3] = p;
                        is_cracked(pwd4sha256, word4);
                        // printf("%s\n", word4);
                    }
                }
            }
        }

        // then, hack 6 char pwd
        char* word6 = (char*)malloc(6*sizeof(char));
        word6[6] = '\0'; // terminate at 7th char
        for (int i = ASCII_START; i <= ASCII_END; i++){
            word6[0] = i;
            for (int j = ASCII_START; j <= ASCII_END; j++){
                word6[1] = j;
                for (int k = ASCII_START; k <= ASCII_END; k++){
                    word6[2] = k;
                    for (int p = ASCII_START; p <= ASCII_END; p++){
                        word6[3] = p;
                        for (int q = ASCII_START; q <= ASCII_END; q++){
                            word6[4] = q;
                            for (int z = ASCII_START; z<= ASCII_END; z++){
                                word6[5] = z;
                                is_cracked(pwd6sha256, word6);
                            }
                        }
                    }
                }
            }
        }

    }else if(argc == 2){
        int total_num_guesses = atoi(argv[1]);
        int curr_guess_count = 0;
        printf("%d arguments\n", argc);
    }else if (argc == 3){
        char* guesses_filepath = argv[1];
        char* pwdNsha256_filepath = argv[2];

        // read pwdNsha256 file into 2D array of BYTES
        pwd_sha256_t* pwdNsha256 = pwd_reader(pwdNsha256_filepath);
        // read the guess file and get the file length

        FILE * fp;
        char * word = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen(guesses_filepath, "r");
        if (fp == NULL){
            exit(EXIT_FAILURE);
        }
        while ((read = getline(&word, &len, fp)) != -1) {
            // printf("%s\n", is_cracked(pwdNsha256, word));
            is_cracked(pwdNsha256, word);
            // printf("%s\n", word);
        }

        fclose(fp);
        if (word){
            free(word);
        }
        exit(EXIT_SUCCESS);



        // result
        printf("%d arguments\n", argc);
    }

    return 0;
}

/*This function is responsible for read the pwdNsha256 into a 2D array of BYTE*/
pwd_sha256_t* pwd_reader(char* filePath){
    // read the file and get the file length
    unsigned char * buffer = 0;
    long length;
    FILE * f = fopen (filePath, "rb");

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
    int count = length/SIZE_OF_SHA256;
    pwd_sha256_t* pwdNsha256 = (pwd_sha256_t*)malloc(sizeof(pwd_sha256_t));
    pwdNsha256->pwd_sha256_list = (BYTE**)malloc(count*sizeof(BYTE*));
    pwdNsha256->pwd_count = count;

    for (int i = 0; i < count; i++){
        pwdNsha256->pwd_sha256_list[i] = (BYTE*)malloc(SIZE_OF_SHA256*sizeof(BYTE));
    }

    // storing
    if (buffer){
        for (int i = 0; i < count; i++){
            for (int j = 0; j < 32; j++){
                pwdNsha256->pwd_sha256_list[i][j] = buffer[i*SIZE_OF_SHA256+j];
            }
        }
    }

    return pwdNsha256;
}

/*This function takes in a string, and return its SHA256 in an array of BYTE*/
BYTE* str_to_sha_256(char* str){
    /* use sha256 to generate hash*/
    int string_size = strlen(str);

    BYTE* data0 = (unsigned char*)str;
    BYTE data[string_size];
    memcpy(data, data0, string_size);

    BYTE* hash = (BYTE*)malloc(SIZE_OF_SHA256*sizeof(BYTE));
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx,data, string_size);
    sha256_final(&ctx, hash);

    return hash;
}

/*This is the helper function used to print out hash value stored in BYTE*/
void print_hash(BYTE* hash){
    for (int i = 0; i < SIZE_OF_SHA256; i ++){
        printf("%02x", hash[i]);
    }
    printf("-\n");
}

/*This function takes guess and sha256 of pwds and check if the guess matches*/
char* is_cracked(pwd_sha256_t* pwdNsha256, char* guess){
    // hash the guess to get its sha256
    BYTE* hash_guess = str_to_sha_256(guess);
    // compare the sha256 of guess to each pwd's sha256
    for (int i = 0; i < pwdNsha256->pwd_count; i++){
        // if guess matches, print it out and return it
        if (memcmp(pwdNsha256->pwd_sha256_list[i], hash_guess, SIZE_OF_SHA256) == 0){
            printf("%s %d\n", guess, i);
            free(hash_guess);
            return guess;
        }
    }
    // free guess
    free(hash_guess);

    // guess matches nothing, return GUESS_FAILED
    return GUESS_FAILED;
}
