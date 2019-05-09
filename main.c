#define DEBUG

#include "stdio.h"
#include "stdlib.h"

#define PWD4SHA256_PATH "./pwd4sha256"
#define PWD6SHA256_PATH "./pwd6sha256"

unsigned int* pwd_reader(char* filePath);
void pwd_printer(char* pwd);

int main(int argc, char* argv[]){
    // read pwd4sha256
    pwd_reader(PWD4SHA256_PATH);

    // print out pwd4sha256

    // use sha256 to generate hash

    // generate all combinations of 4

    // make them into sha256

    // start cracking
    return 0;
}

unsigned int* pwd_reader(char* filePath){
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

    if (buffer){
    #ifdef DEBUG
    int count = 1;
    for (int i = 0; i < 80; i+=8){
        printf("sha256 of word %2d :     ", count++);
        for (int j = 0; j < 8; j++){
            printf("%x", buffer[i+j]);
        }
        printf("\n");
    }
    #endif
    }

    return buffer;
}
