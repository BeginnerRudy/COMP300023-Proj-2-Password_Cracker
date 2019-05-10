/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>

/****************************** MACROS ******************************/
#define ASCII_START 32
#define ASCII_END 126

/*********************** FUNCTION DEFINITIONS ***********************/
int main(int argc, char* argv[]){
    char word[4];
    for (int i = ASCII_START; i <= ASCII_END; i++){
        word[0] = i;
        for (int j = ASCII_START; j <= ASCII_END; j++){
            word[1] = j;
            for (int k = ASCII_START; k <= ASCII_END; k++){
                word[2] = k;
                for (int p = ASCII_START; p <= ASCII_END; p++){
                    word[3] = p;
                    printf("%s\n", word);
                }
            }
        }
    }

    return 0;
}
