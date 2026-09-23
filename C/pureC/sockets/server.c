#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define port 8080

int main(){
	int server_fd, client_fd;
	int socc = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address = {0};
	size_t addr_len = sizeof(address);

	if (socc < 0){
		perror("Error creando socket");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);

	if (bind(server_fd, (struct sockaddr*)&address, sizeof(addr_len)) < 0){
		perror("No se pudo bindear");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0){
		perror("No se puede escuchar");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("escuchando en el puerto %d", 8080);

	send(client_fd, "Hola", strlen("hola"), 0);

	return 0;
}
