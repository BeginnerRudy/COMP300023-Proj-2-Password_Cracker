/*********************************************************************
 *			COMP30023 Computer Systems - Assignment 2				 *
 *					Author: Renjie(Rudy) Meng						 *
 *						Date: 23th May 2019							 *
 *																	 *
 *********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include "checking.h"

/*********************** FUNCTION DEFINITIONS ***********************/
int main(int argc, char* argv[]){
    if (argc == 1){
        // start to crack
        brute_force();
    }else if(argc == 2){
        // start to generate guesses
        guess(atoi(argv[1]));
    }else if (argc == 3){
        // start to checking guesses
        checking(argv[1], argv[2]);
    }
    return 0;
}
