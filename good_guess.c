#include "good_guess.h"

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
