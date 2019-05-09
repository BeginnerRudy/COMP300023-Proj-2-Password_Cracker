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

void process_download(const int sockfd, const char* file_name);
int setup_client_socket(const int port, const char* server_name,
						struct sockaddr_in* serv_addr);
void process_upload(const int sockfd, const char* file_name);

long int hex_to_decimal(char hex);
long int parse_two_hex_digits_to_integer(char* two_hex_digit);
long int mod(long int a, long int b);
long int exponential(long int base, long int exp);
char* dh_first_calculator(long int g, long int p, long int b);
char* dh_second_calculator(long int received, long int p, long int b);
long int get_b();



int main(int argc, char* argv[]) {
	struct sockaddr_in serv_addr;
	char* server = "172.26.37.44";
	int port = 7800;
	int sockfd;
	char buffer[256];

	if (argc < 3) {
		fprintf(stderr, "usage: %s hostname port\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	port = atoi(argv[2]);
	server = argv[1];

    // get b from stdin
    long int b = get_b();

    // calculate g^b(mod p), g = 15, p = 97
    long int g = 15, p = 97;
    char* g_b_mod_p = dh_first_calculator(g, p, b);
    printf("%s\n", g_b_mod_p);



	/* Make connection */
	sockfd = setup_client_socket(port, server, &serv_addr);
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
    		perror("connect");
    		exit(EXIT_FAILURE);
    }

    printf("Connect successful\ n");

    char* username = "renjiem\n";
    int n = write(sockfd, username, strlen(username));
	if (n < 0) {
    		perror("write");
    		exit(EXIT_FAILURE);
    }
    printf("Username send successful\n");

    n = write(sockfd, g_b_mod_p, strlen(g_b_mod_p));
	if (n < 0) {
    		perror("write");
    		exit(EXIT_FAILURE);
    }
    printf("g_b_mod_p send successful\n");

    /* Read initial message */
	n = read(sockfd, buffer, 2047);
	if (n < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buffer[n] = '\0';
    printf("%s", buffer);
    printf("read successful\n");


    // calculate (g^b)^a(mod p), g = 15, p = 97
    long int received = atoi(buffer);
    printf("%ld\n", received);

    char* received_b_mod_p = dh_second_calculator(received, p, b);
    n = write(sockfd, received_b_mod_p, strlen(received_b_mod_p));
	if (n < 0) {
    		perror("write");
    		exit(EXIT_FAILURE);
    }
    printf("received_b_mod_p send successful\n");

    /* Read initial message */
	n = read(sockfd, buffer, 2047);
	if (n < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buffer[n] = '\0';
    printf("%s", buffer);
    printf("read successful\n");


	/* Close to let server know that we've finished sending our message */
	close(sockfd);

}

long int get_b(){
    char* two_hex = (char*)malloc(2*sizeof(char));
    char hex_buff[10];
    printf("Enter b for Diffie-Hellman key exchange: ");
    gets(hex_buff);
    sscanf(hex_buff, "%s", two_hex);
    return parse_two_hex_digits_to_integer(two_hex);
}

long int hex_to_decimal(char hex){
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

long int parse_two_hex_digits_to_integer(char* two_hex_digit){
    if (strlen(two_hex_digit) != 2){
        perror("Please enter exactly 2 hex digits!!!");
        exit(EXIT_FAILURE);
    }

    return 16*hex_to_decimal(two_hex_digit[0]) + hex_to_decimal(two_hex_digit[1]);

}

long int mod(long int a, long int b){
    return a - (a/b)*b;
}

long int exponential(long int base, long int exp){
    long int result = 1;
    for (int i = 0; i < exp; i++){
        result *= base;
    }
    return result;
}

char* dh_first_calculator(long int g, long int p, long int b){
    // g^b(mod p) = ((g mod p)^b)mod p
    long int result = 1;
    

    char* res = (char*)malloc(MAX_SIZE_OF_INT*sizeof(char));
    printf("%d\n", exponential(mod(g, p), b));
    sprintf(res, "%ld%c", result, '\n');
    return res;
}

char* dh_second_calculator(long int received, long int p, long int b){
    // (received)^b(mod p) = (received mod p)^b mod p
    long int result = mod(exponential(mod(received, p), b), p);
    char* res = (char*)malloc(MAX_SIZE_OF_INT*sizeof(char));
    sprintf(res, "%ld%c", result, '\n');
    return res;
}


/* Handles DOWNLOAD command */
void process_download(const int sockfd, const char* file_name) {
	int filefd;
	char buffer[2048];
	int n;

	/* Send download command to server */
	sprintf(buffer, "DOWNLOAD %s", file_name);
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) {
		perror("write");
		exit(EXIT_FAILURE);
	}

	/* Read initial message */
	n = read(sockfd, buffer, 2047);
	if (n < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buffer[n] = '\0';

	/* Take action depending on server response */
	if (strncmp(buffer, "NOT-FOUND", 9) == 0) {
		fprintf(stderr, "Server could not find %s\n", file_name);
		return;
	} else if (strncmp(buffer, "OK ", 3) == 0) {
		/* Open file for writing */
		filefd = open(file_name, O_WRONLY | O_CREAT, 0600);

		/* Write initial buffer contents */
		n = write(filefd, buffer + 3, n - 3);
		if (n < 0) {
			perror("write");
			exit(EXIT_FAILURE);
		}
	} else {
		fprintf(stderr, "Wrong response from server, ignoring\n");
		return;
	}

	// Read from socket until whole file is received
	while (1) {
		n = read(sockfd, buffer, 2048);
		if (n == 0) {
			break;
		}
		if (n < 0) {
			perror("read");
			exit(EXIT_FAILURE);
		}

		n = write(filefd, buffer, n);
		if (n < 0) {
			perror("write");
			exit(EXIT_FAILURE);
		}
	}

	printf("Received file %s\n", file_name);
}

/* Handles UPLOAD command */
void process_upload(const int sockfd, const char* file_name) {
	int filefd;
	int n, re;
	char buffer[2048];

	if (access(file_name, F_OK) != -1) {
		/* Open file */
		filefd = open(file_name, O_RDONLY);
		if (!filefd) {
			perror("open");
			exit(EXIT_FAILURE);
		}

		/* Write "UPLOAD " and file name */
		n = sprintf(buffer, "UPLOAD %s ", file_name);
		n = write(sockfd, buffer, n);
		if (n < 0) {
			perror("write");
			exit(EXIT_FAILURE);
		}

		/* Send file contents */
		re = 0;
		do {
			re = sendfile(sockfd, filefd, NULL, 2048);
		} while (re > 0);
		if (re < 0) {
			perror("ERROR sending file");
			exit(EXIT_FAILURE);
		}
	} else {
		fprintf(stderr, "File not found\n");
	}
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
