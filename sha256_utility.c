#include "sha256_utility.h"

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
