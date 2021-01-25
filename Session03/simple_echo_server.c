#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	char message[BUF_SIZE];
	int str_len;
	
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_sz;
	
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	// TODO: socket()
	serv_sock = socket(PF_INET,SOCK_STREAM,0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	// TODO: bind()
	bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
		
	printf("Server Listen...\n");

	// TODO: listen()
	listen(serv_sock, 3);
	clnt_adr_sz = sizeof(clnt_adr);
 	
 	// TODO: accept()
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);

	puts("Client is connected!");
	
	// TODO: 2. read message from client
	read(clnt_sock, message, BUF_SIZE);
	printf("Client's message: %s", message);

	// TODO: 3. write message to client 
	write(clnt_sock, message, BUF_SIZE);

	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}