#define DEBUG

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256_utility.h"
#include "pwd_utility.h"

/****************************** MACROS ******************************/
#define PWD4SHA256_PATH "./pwd4sha256"
#define PWD6SHA256_PATH "./pwd6sha256"


#define ASCII_START 32 + 16
#define ASCII_END 126
#define GUSS "s"



/*********************** FUNCTION PROTOTYPES ***********************/


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
            // Terminate the word at the new line char
            strtok(word, "\n");
            is_cracked(pwdNsha256, word);
            // printf("%s the length is %ld\n", word, strlen(word));
        }

        fclose(fp);
        if (word){
            free(word);
        }
        exit(EXIT_SUCCESS);
    }

    return 0;
}
