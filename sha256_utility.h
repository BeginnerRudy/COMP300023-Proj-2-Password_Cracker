/*************************** HEADER FILES ***************************/
#include <string.h>
#include <stdlib.h>
#include "sha256.h"

/****************************** MACROS ******************************/
#define SIZE_OF_SHA256 32 // The number of bytes need for a SHA256 

/*********************** FUNCTION PROTOTYPES ***********************/
BYTE* str_to_sha_256(char* str);
