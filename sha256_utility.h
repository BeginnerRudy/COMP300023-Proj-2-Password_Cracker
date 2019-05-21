/*************************** HEADER FILES ***************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sha256.h"

/****************************** MACROS ******************************/
#define SIZE_OF_SHA256 32 // The number of bytes need for a SHA256

/*********************** FUNCTION PROTOTYPES ***********************/
/*This function takes in a string, and return its SHA256 in an array of BYTE*/
BYTE* str_to_sha_256(char* str);
/*This is the helper function used to print out hash value stored in BYTE*/
void print_hash(BYTE* hash);
