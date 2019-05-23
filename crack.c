/*********************************************************************
 *			COMP30023 Computer Systems - Assignment 2				 *
 *					Author: Renjie(Rudy) Meng						 *
 *						Date: 23th May 2019							 *
 *																	 *
 *********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "sha256_utility.h"
#include "pwd_utility.h"

/****************************** MACROS ******************************/
#define PWD4SHA256_PATH "./pwd4sha256"
#define PWD6SHA256_PATH "./pwd6sha256"


#define DEBUG
#define ASCII_START 32 + 16
#define ASCII_END 126
#define GUSS "s"
#define TO_UPPER_PROB 0.07

// This is the cummulative density function table, which would be used in good guess
#define _e 0.095388
#define _a 0.088034 + _e
#define _r 0.067375 + _a
#define _o 0.066070 + _r
#define _n 0.062320 + _o
#define _i 0.061211 + _n
#define _s 0.058227 + _i
#define _t 0.050254 + _s
#define _l 0.049439 + _t
#define _c 0.033915 + _l
#define _d 0.032888 + _c
#define _m 0.031828 + _d
#define _h 0.028877 + _m
#define _g 0.026284 + _h
#define _b 0.025975 + _g
#define _u 0.025502 + _b
#define _p 0.024099 + _u
#define _1 0.022029 + _p
#define _y 0.021751 + _1
#define _k 0.017691 + _y
#define _f 0.014234 + _k
#define _w 0.013762 + _f
#define _2 0.009587 + _w
#define _v 0.009424 + _2
#define _j 0.007337 + _v
#define _3 0.006473 + _j
#define _z 0.006098 + _3
#define _0 0.005984 + _z
#define _4 0.0054624 + _0
#define _5 0.005348 + _4
#define _9 0.005234 + _5
#define _6 0.005038 + _9
#define _x 0.005022 + _6
#define _7 0.004484 + _x
#define _8 0.003587 + _7
#define _q 0.003081 + _8
#define star 0.000244 + _q
#define question_mark 0.000179 + star

/*********************** FUNCTION PROTOTYPES ***********************/
void brute_force();
void guess(int total_num_guesses);
void checking(char* guesses_filepath, char* pwdNsha256_filepath);
char pick_char(double num);
char randomly_converting(char character);
char choose_from_special();
char* generate_guess(int len_of_pwd);

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

/*This function implements when there is no argument passed through.
 It would implement brute force to crack the pwd.
*/
void brute_force(){
    // read pwd first
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
                    // decide whether the word is corrected
                    is_cracked(pwd4sha256, word4);
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
                            // decide whether the word is corrected
                            is_cracked(pwd6sha256, word6);
                        }
                    }
                }
            }
        }
    }
}

/*This function implements when there is 1 argument passed through.
 The 1st argument is number of guess need to be generated
*/
void guess(int total_num_guesses){
    int curr_guess_count = 0;
    srand(time(NULL));
    while(curr_guess_count < total_num_guesses){
        char* guess = generate_guess(6);
        printf("%s\n", guess);
        free(guess);
        curr_guess_count++;
    }
    //generate 6-char guess
}

/*This function implements when there is 2 arguments passed through.
 The 1st argument is guess word file path and 2nd argument is the pwd sha256 file
*/
void checking(char* guesses_filepath, char* pwdNsha256_filepath){
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

    // close the file
    fclose(fp);

    // free memory
    if (word){
        free(word);
    }
}

/*This function is responsible for picking
 a char based on the given num, this num
 has a value between 0 and 1, which plays
 a role as probability
 @param: num => the probability in [0, 1]
*/
char pick_char(double num){
    if (num < _e){
        return 'e';
    }else if(num < _a){
        return 'a';
    }else if(num < _r){
        return 'r';
    }else if(num < _o){
        return 'o';
    }else if(num < _n){
        return 'n';
    }else if(num < _i){
        return 'i';
    }else if(num < _s){
        return 's';
    }else if(num < _t){
        return 't';
    }else if(num < _l){
        return 'l';
    }else if(num < _c){
        return 'c';
    }else if(num < _d){
        return 'd';
    }else if(num < _m){
        return 'm';
    }else if(num < _h){
        return 'h';
    }else if(num < _g){
        return 'g';
    }else if(num < _b){
        return 'b';
    }else if(num < _u){
        return 'u';
    }else if(num < _p){
        return 'p';
    }else if(num < _1){
        return '1';
    }else if(num < _y){
        return 'y';
    }else if(num < _k){
        return 'k';
    }else if(num < _f){
        return 'f';
    }else if(num < _w){
        return 'w';
    }else if(num < _2){
        return '2';
    }else if(num < _v){
        return 'v';
    }else if(num < _j){
        return 'j';
    }else if(num < _3){
        return '3';
    }else if(num < _z){
        return 'z';
    }else if(num < _0){
        return '0';
    }else if(num < _4){
        return '4';
    }else if(num < _5){
        return '5';
    }else if(num < _9){
        return '9';
    }else if(num < _6){
        return '6';
    }else if(num < _x){
        return 'x';
    }else if(num < _7){
        return '7';
    }else if(num < _8){
        return '8';
    }else if(num < _q){
        return 'q';
    }else if(num < star){
        return '*';
    }else if(num < question_mark){
        return '?';
    }else{
        return choose_from_special();
    }
}

/*This function is responsible for convert given
 lower case char to upper case at predefined probability
 @param: character => the char given for converting
*/
char randomly_converting(char character){
    double X=((double) rand()/(double)RAND_MAX);
    if (X < TO_UPPER_PROB && isalpha(character)){
        return toupper(character);
    }else{
        // it is not letter, return it back
        return character;
    }
}

/*This function is responsible for picking very seldom used char*/
char choose_from_special(){
    // randomly select one float from 0 to 1
    double X=((double) rand()/(double)RAND_MAX);
    if (X < 2/12.0){
        return '.';
    }else if (X < 4/12.0){
        return '&';
    }else if (X < 6/12.0){
        return '+';
    }else if (X < 8/12.0){
        return '-';
    }else if (X < 9/12.0){
        return '!';
    }else if (X < 10/12.0){
        return '\'';
    }else if (X < 11/12.0){
        return ';';
    }

    return '\\';
}

/*This function is responsible for generate pwd of given length
	based on predefined distribution
 @param: int len_of_pwd => specified length of a pwd
*/
char* generate_guess(int len_of_pwd){
    char* guess =  (char*)malloc(len_of_pwd*sizeof(char));
    for (int count = 0; count < len_of_pwd; count++){
        double X=((double) rand()/(double)RAND_MAX);
        guess[count] = randomly_converting(pick_char(X));
    }
    return guess;
}
