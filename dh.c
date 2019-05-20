#define DEBUG

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

#define MAX_SIZE_OF_INT 64

int setup_client_socket(const int port, const char* server_name,
						struct sockaddr_in* serv_addr);

 int hex_to_decimal(char hex);
 int parse_two_hex_digits_to_integer(char* two_hex_digit);
char* dh_calculator( int g,  int p,  int b);
 int get_b();



int main(int argc, char* argv[]) {
	struct sockaddr_in serv_addr;
	char* server = "172.26.37.44";
	int port = 7800;
	int sockfd;
	char buffer[256];


    // get b from stdin
     int b = get_b();

    // calculate g^b(mod p), g = 15, p = 97
    int g = 15, p = 97;
    char* g_b_mod_p = dh_calculator(g, p, b);
    #ifdef DEBUG
    printf("%s\n", g_b_mod_p);
    #endif



	/* Make connection */
	sockfd = setup_client_socket(port, server, &serv_addr);
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
    		perror("connect");
    		exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("Connect successful\n");
    #endif

    char* username = "renjiem\n";
    int n = write(sockfd, username, strlen(username));
	if (n < 0) {
    		perror("write");
    		exit(EXIT_FAILURE);
    }
    #ifdef DEBUG
    printf("Username send successful\n");
    #endif

    n = write(sockfd, g_b_mod_p, strlen(g_b_mod_p));
	if (n < 0) {
    		perror("write");
    		exit(EXIT_FAILURE);
    }
    #ifdef DEBUG
    printf("g_b_mod_p send successful\n");
    #endif

    /* Read initial message */
	n = read(sockfd, buffer, 2047);
	if (n < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buffer[n] = '\0';
    #ifdef DEBUG
    printf("%s", buffer);
    printf("read successful\n");
    #endif


    // calculate (g^b)^a(mod p), g = 15, p = 97
    int received = atoi(buffer);
    #ifdef DEBUG
    printf("%d\n", received);
    #endif

    char* received_b_mod_p = dh_calculator(received, p, b);
    n = write(sockfd, received_b_mod_p, strlen(received_b_mod_p));
	if (n < 0) {
    		perror("write");
    		exit(EXIT_FAILURE);
    }
    #ifdef DEBUG
    printf("received_b_mod_p send successful\n");
    #endif

    /* Read initial message */
	n = read(sockfd, buffer, 2047);
	if (n < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buffer[n] = '\0';
    #ifdef DEBUG
    printf("%s", buffer);
    printf("read successful\n");
    #endif


	/* Close to let server know that we've finished sending our message */
	close(sockfd);



}

 int get_b(){
    char* two_hex = (char*)malloc(2*sizeof(char));
    char hex_buff[10];
    printf("Enter b for Diffie-Hellman key exchange: ");
    gets(hex_buff);
    sscanf(hex_buff, "%s", two_hex);
    return parse_two_hex_digits_to_integer(two_hex);
}

 int hex_to_decimal(char hex){
    hex = tolower(hex);
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
    }else{
        return -99999;
    }
}

 int parse_two_hex_digits_to_integer(char* two_hex_digit){
    if (strlen(two_hex_digit) != 2){
        perror("Please enter exactly 2 hex digits!!!");
        exit(EXIT_FAILURE);
    }

    return 16*hex_to_decimal(two_hex_digit[0]) + hex_to_decimal(two_hex_digit[1]);

}

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
    sprintf(res, "%d%c", result, '\n');
    return res;
}



/* Create and return a socket bound to the given port and server */
int setup_client_socket(const int port, const char* server_name,
						struct sockaddr_in* serv_addr) {
	int sockfd;
	struct hostent* server;

	server = gethostbyname(server_name);
	if (!server) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(EXIT_FAILURE);
	}
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
