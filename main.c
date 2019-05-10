#define DEBUG

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

/****************************** MACROS ******************************/
#define PWD4SHA256_PATH "./pwd4sha256"
#define PWD6SHA256_PATH "./pwd6sha256"

#define NUM_OF_PWD4 10
#define NUM_OF_PWD6 20
#define SIZE_OF_SHA256 32



#define ASCII_START 32 + 65
#define ASCII_END 126

/*********************** FUNCTION PROTOTYPES ***********************/
BYTE** pwd_reader(char* filePath, int num_of_pwd);
void pwd_printer(char* pwd);
BYTE* str_to_sha_256(char* str);
char* is_cracked(BYTE** pwdNsha256, int num_of_pwd, char* guess);
void print_hash(BYTE* hash);

/*********************** FUNCTION DEFINITIONS ***********************/
int main(int argc, char* argv[]){
    /* read pwd4sha256*/
    // BYTE** pwd4sha256 = pwd_reader(PWD4SHA256_PATH, NUM_OF_PWD4);
    BYTE** pwd6sha256 = pwd_reader(PWD6SHA256_PATH, NUM_OF_PWD6);

    if (argc == 3){
        char* guesses_filepath = argv[1];
        char* pwdNsha256_filepath = argv[2];
        printf("%d arguments\n", argc);
    }else if (argc == 1){
        /* use sha256 to generate hash*/

        // FILE * fp;
        // char * line = NULL;
        // size_t len = 0;
        // ssize_t read;
        //
        // fp = fopen(argv[1], "r");
        // if (fp == NULL){
            //     exit(EXIT_FAILURE);
            // }
            // while ((read = getline(&line, &len, fp)) != -1) {
                //     printf("%s", line);
                // }
                //
                // fclose(fp);
                // if (line){
                    //     free(line);
                    // }
                    // exit(EXIT_SUCCESS);


                    // char* word = (char*)malloc(4*sizeof(char));
                    // for (int i = ASCII_START; i <= ASCII_END; i++){
                        //     word[0] = i;
                        //     for (int j = ASCII_START; j <= ASCII_END; j++){
                            //         word[1] = j;
                            //         for (int k = ASCII_START; k <= ASCII_END; k++){
                                //             word[2] = k;
                                //             for (int p = ASCII_START; p <= ASCII_END; p++){
                                    //                 word[3] = p;
                                    //                 char* res = is_cracked(pwd4sha256, NUM_OF_PWD4, word);
                                    //             }
                                    //         }
                                    //     }
                                    // }
                                    char* word = (char*)malloc(6*sizeof(char));
                                    for (int i = ASCII_START; i <= ASCII_END; i++){
                                        word[0] = i;
                                        for (int j = ASCII_START; j <= ASCII_END; j++){
                                            word[1] = j;
                                            for (int k = ASCII_START; k <= ASCII_END; k++){
                                                word[2] = k;
                                                for (int p = ASCII_START; p <= ASCII_END; p++){
                                                    word[3] = p;
                                                    for (int q = ASCII_START; q <= ASCII_END; q++){
                                                        word[4] = q;
                                                        for (int z = ASCII_START; z<= ASCII_END; z++){
                                                            word[5] = z;
                                                            is_cracked(pwd6sha256, NUM_OF_PWD6, word);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    // char* res = is_cracked(pwd6sha256, NUM_OF_PWD6, "renjie");

                                    /* generate all combinations of 4*/

                                    /* make them into sha256*/

                                    /* start cracking*/
                                    // how to check equlity

    }else if(argc == 2){
        int total_num_guesses = atoi(argv[1]);
        printf("%d arguments\n", argc);
    }

    return 0;
}

/*This function is responsible for read the pwdNsha256 into a 2D array of BYTE*/
BYTE** pwd_reader(char* filePath, int num_of_pwd){

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

    int count;
    if (num_of_pwd == NUM_OF_PWD6){
        count = 20;
    }else if(num_of_pwd == NUM_OF_PWD4){
        count = 10;
    }

    BYTE** pwdNsha256 = (BYTE**)malloc(count*sizeof(BYTE*));
    for (int i = 0; i < count; i++){
        pwdNsha256[i] = (BYTE*)malloc(SIZE_OF_SHA256*sizeof(BYTE));
    }

    // print out the result
    if (buffer){
        for (int i = 0; i < num_of_pwd; i++){
            for (int j = 0; j < 32; j++){
                pwdNsha256[i][j] = buffer[i*SIZE_OF_SHA256+j];
            }
            // print_hash(pwdNsha256[i/8]);
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

char* is_cracked(BYTE** pwdNsha256, int num_of_pwd, char* guess){
    BYTE* hash_guess = str_to_sha_256(guess);
    for (int i = 0; i < num_of_pwd; i++){
        if (memcmp(pwdNsha256[i], hash_guess, SIZE_OF_SHA256) == 0){
            printf("%s %d\n", guess, i+11);
            return guess;
        }
    }
    free(hash_guess);
    return "N";
}
