/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include "pwd_utility.h"

/****************************** MACROS ******************************/
#define PWD4SHA256_PATH "./pwd4sha256"
#define PWD6SHA256_PATH "./pwd6sha256"

#define ASCII_START 32 + 16
#define ASCII_END 126
#define GUSS "s"

/*********************** FUNCTION PROTOTYPES ***********************/
void brute_force();
