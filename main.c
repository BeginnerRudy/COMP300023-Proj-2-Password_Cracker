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

/*********************** FUNCTION PROTOTYPES ***********************/
unsigned int* pwd_reader(char* filePath, int num_of_pwd);
void pwd_printer(char* pwd);

/*********************** FUNCTION DEFINITIONS ***********************/
int main(int argc, char* argv[]){
    /* read pwd4sha256*/
    // pwd_reader(PWD4SHA256_PATH, NUM_OF_PWD4);
    // pwd_reader(PWD6SHA256_PATH, NUM_OF_PWD6);

    /* use sha256 to generate hash*/
    char* foobar = "foobar";
    int string_size = strlen(foobar);

    BYTE* data0 = (unsigned char*)foobar;
    BYTE data[string_size];
    memcpy(data, data0, string_size);

    BYTE hash[32];
    SHA256_CTX ctx;

    sha256_init(&ctx);
    sha256_update(&ctx,data, string_size);
    sha256_final(&ctx, hash);

    for (int i = 0; i < 32; i++){
        printf("%x", hash[i]);
    }
    printf("\n");


    /* generate all combinations of 4*/

    /* make them into sha256*/

    /* start cracking*/
    // how to check equlity
    return 0;
}

unsigned int* pwd_reader(char* filePath, int num_of_pwd){
    unsigned int * buffer = 0;
    long length;
    FILE * f = fopen (filePath, "rb");

    if (f){
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer){
            fread (buffer, 1, length, f);
        }
    fclose (f);
    }


    // print out the result
    if (buffer){
    #ifdef DEBUG
    int count = 1;
    if (num_of_pwd == NUM_OF_PWD6){
        count = 11;
    }
    for (int i = 0; i < 8*num_of_pwd; i+=8){
        printf("sha256(pwd%3d) :    ", count++);
        for (int j = 0; j < 8; j++){
            printf("%x", buffer[i+j]);
        }
        printf("\n");
    }
    #endif
    }

    return buffer;
}
