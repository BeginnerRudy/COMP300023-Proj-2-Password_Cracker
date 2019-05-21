/*************************** HEADER FILES ***************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sha256_utility.h"

/****************************** MACROS ******************************/
#define GUESS_FAILED "F" // This indicate the guessing word does not matching any pwd

typedef struct{
    BYTE** pwd_sha256_list; // the array of pwd sha256
    int pwd_count; // the number of pwd sha256
}pwd_sha256_t;

/*********************** FUNCTION PROTOTYPES ***********************/
/*This function is responsible for read the pwdNsha256 into a 2D array of BYTE*/
pwd_sha256_t* pwd_reader(char* filePath);
/*This function takes guess and sha256 of pwds and check if the guess matches*/
char* is_cracked(pwd_sha256_t* pwdNsha256, char* guess);
