#include "checking.h"

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
