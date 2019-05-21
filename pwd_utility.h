/*************************** HEADER FILES ***************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sha256_utility.h"

/****************************** MACROS ******************************/
#define GUESS_FAILED "F"

typedef struct{
    BYTE** pwd_sha256_list;
    int pwd_count;
}pwd_sha256_t;

/*********************** FUNCTION PROTOTYPES ***********************/
pwd_sha256_t* pwd_reader(char* filePath);
char* is_cracked(pwd_sha256_t* pwdNsha256, char* guess);
