/*********************************************************************
 *			COMP30023 Computer Systems - Assignment 2				 *
 *					Author: Renjie(Rudy) Meng						 *
 *						Date: 23th May 2019							 *
 *																	 *
 *********************************************************************/

/*************************** HEADER FILES ***************************/
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/****************************** MACROS ******************************/
#define DEBUG
#define MAX_SIZE_OF_INT 64
#define BUFFER_SIZE 2048
/*********************** FUNCTION PROTOTYPES ***********************/
int setup_client_socket(const int port, const char* server_name,
						struct sockaddr_in* serv_addr);
void send_data(int sockfd, char* data);
void read_data(int sockfd, char* buffer, int buffer_size);
int hex_to_decimal(char hex);
int parse_two_hex_digits_to_integer(char* two_hex_digit);
char* dh_calculator( int g,  int p,  int b);


/*********************** FUNCTION DEFINITIONS ***********************/
int main(int argc, char* argv[]) {
	/*Decalre and initialize variables for connection*/
	struct sockaddr_in serv_addr;
	char* server = "172.26.37.44";
	int port = 7800;
	int sockfd;
	char* buffer = (char*)malloc(BUFFER_SIZE*sizeof(char));


	/* Make connection */
	sockfd = setup_client_socket(port, server, &serv_addr);
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
    		perror("connect");
    		exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("Connect the server successfully\n");
    #endif

	/*send my username to server*/
    char* username = "renjiem\n";
    send_data(sockfd, username);
    #ifdef DEBUG
    printf("Username: renjiem send successful\n");
    #endif

	/* get b(decimal) from command line argument*/
	int b = atoi(argv[1]);
	printf("b = (decimal) %d. \n", b);

	/* calculate g^b(mod p), g = 15, p = 97*/
	int g = 15, p = 97;
	char* g_b_mod_p = dh_calculator(g, p, b);
	#ifdef DEBUG
	printf("g^b mod p = %s", g_b_mod_p);
	#endif
	// send the result
	send_data(sockfd, g_b_mod_p);
    #ifdef DEBUG
	printf("client send: ");
    printf("%s", g_b_mod_p);
    #endif

    /* Read initial message, that is the result that the server wish to exchange */
	read_data(sockfd, buffer, BUFFER_SIZE);
    #ifdef DEBUG
    printf("read from server: %s", buffer);
    #endif


    /* calculate (g^b)^a(mod p), g = 15, p = 97 */
    int received = atoi(buffer);
    char* received_b_mod_p = dh_calculator(received, p, b);

	send_data(sockfd, received_b_mod_p);
    #ifdef DEBUG
	printf("client send: ");
    printf("%s", received_b_mod_p);
    #endif

    /* Read message, to see whether dh is successful */
	read_data(sockfd, buffer, BUFFER_SIZE);
    #ifdef DEBUG
    printf("read from server: %s", buffer);
    #endif


	/* Close to let server know that we've finished sending our message */
	close(sockfd);
}

// This function is repsonsible for sending data to the server
void send_data(int sockfd, char* data){
	int n = write(sockfd, data, strlen(data));
	if (n < 0) {
    		perror("write");
    		exit(EXIT_FAILURE);
    }
}

// This function is responsible for reading data from the server
void read_data(int sockfd, char* buffer, int buffer_size){
	int n = read(sockfd, buffer, buffer_size);
	if (n < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buffer[n] = '\0';
}
//This function is used to convert hex number to decimal number
int hex_to_decimal(char hex){
	// first convert hex to lowercase
    hex = tolower(hex);
	// map hex to its decimal reppresentation
    if (hex == '0'){
        return 0;
    }else if (hex == '1'){
        return 1;
    }else if (hex == '2'){
        return 2;
    }else if (hex == '3'){
        return 3;
    }else if (hex == '4'){
        return 4;
    }else if (hex == '5'){
        return 5;
    }else if (hex == '6'){
        return 6;
    }else if (hex == '7'){
        return 7;
    }else if (hex == '8'){
        return 8;
    }else if (hex == '9'){
        return 9;
    }else if (hex == 'a'){
        return 10;
    }else if (hex == 'b'){
        return 11;
    }else if (hex == 'c'){
        return 12;
    }else if (hex == 'd'){
        return 13;
    }else if (hex == 'e'){
        return 14;
    }else if (hex == 'f'){
        return 15;
		// if it is invalid assign it to -99999 to indicates
    }else{
        return -99999;
    }
}

// Thi funcion is used to convert 2 hex digits into a decimal representation
 int parse_two_hex_digits_to_integer(char* two_hex_digit){
    if (strlen(two_hex_digit) != 2){
        perror("Please enter exactly 2 hex digits!!!");
        exit(EXIT_FAILURE);
    }

    return 16*hex_to_decimal(two_hex_digit[0]) + hex_to_decimal(two_hex_digit[1]);

}

// This function is responsible for calculating dh result
char* dh_calculator( int g,  int p,  int b){
    /* reduce factor before multiplication */
    // first reduce each g to g%p, and stores it in k
    int k = g%p;
    // z is the result of the multiplication of the first two terms
    int z = k;

    // keep reduce factor if there is more than one multiplication term
    while(b > 1){
        z = (z*k)%p;
        b--;
    }

    // do the final modular
    int result = z % p;

    // Convert int to char
    char* res = (char*)malloc(MAX_SIZE_OF_INT*sizeof(char));
	// add a new line char to it, since it is the requirenment from the spec
    sprintf(res, "%d%c", result, '\n');
    return res;
}



/* Create and return a socket bound to the given port and server */
int setup_client_socket(const int port, const char* server_name,
						struct sockaddr_in* serv_addr) {
	// delcare vars
	int sockfd;
	struct hostent* server;

	// get server
	server = gethostbyname(server_name);
	if (!server) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(EXIT_FAILURE);
	}

	// assign address
	bzero((char*)serv_addr, sizeof(serv_addr));
	serv_addr->sin_family = AF_INET;
	bcopy(server->h_addr_list[0], (char*)&serv_addr->sin_addr.s_addr,
		  server->h_length);
	serv_addr->sin_port = htons(port);

	/* Create socket */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}
