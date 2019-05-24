#include "brute_force.h"

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
