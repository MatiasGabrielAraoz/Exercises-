#include <asm-generic/socket.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};

	if ((server_fd = socket(AF_INET, SOCK_STREAM), 0) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))){
		perror("bind failed");
		exit(EXIT_FAILURE)
	}

	if (listen(server_fd, 3) < 0) {
			perror("listen");
			exit(EXIT_FAILURE);
	}

    std::cout << "Servidor escuchando en el puerto 8080..." << std::endl;
	return 0
}
