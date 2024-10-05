
#include "communication.h"


int global_client_id = 1;
	
	int main(int argc, char *argv[]) {
		if (argc != 2) {
			printf("compilation: %s <port>\n", argv[0]);
			exit(EXIT_FAILURE);
		}

		int port = atoi(argv[1]);

		int server_socket, client_socket;
		struct sockaddr_in server_address, client_address;
		socklen_t client_address_len = sizeof(client_address);

		int pipe_fd = open("/tmp/pipe", O_RDWR);
		if (pipe_fd == -1) {
			perror("erreur lors de l'ouverture du pipe");
			exit(EXIT_FAILURE);
		}

		server_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (server_socket == -1) {
			perror("erreur lors de la création de la socket serveur");
			exit(EXIT_FAILURE);
		}

		memset(&server_address, 0, sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = INADDR_ANY;
		server_address.sin_port = htons(port);

		int enable = 1;
		if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
			perror("setsockopt");
			close(server_socket);
			exit(EXIT_FAILURE);
		}

		if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
			perror("erreur lors du bind");
			close(server_socket);
			exit(EXIT_FAILURE);
		}

		if (listen(server_socket, 50) == -1) {
			perror("erreur lors de l'écoute");
			close(server_socket);
			exit(EXIT_FAILURE);
		}

		FILE *ready_file = fopen("/tmp/server_ready", "w");
		if (ready_file == NULL) {
			perror("erreur lors de la création du fichier temporaire");
			close(server_socket);
			exit(EXIT_FAILURE);
		} else {
			fclose(ready_file);
		}

	while (1) {
		client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
		if (client_socket == -1) {
			perror("erreur lors de l'acceptation de la connexion du client");
			continue;
		}
		
		client_data_t *client_data = (client_data_t *)malloc(sizeof(client_data_t));
		if (client_data == NULL) {
			perror("erreur lors de l'allocation de la mémoire pour la structure client_data_t");
			close(client_socket);
			continue;
		} 
			client_data->client_id = global_client_id++;
			client_data->client_socket = client_socket;
			client_data->pipe_fd = pipe_fd;

			printf("\n  - Paire %d connecté depuis %s\n", client_data->client_id, inet_ntoa(client_address.sin_addr));

			pthread_t client_thread;
			if (pthread_create(&client_thread, NULL, client_handler, (void *)client_data) != 0) {
				perror("erreur lors de la création du thread");
				free(client_data);
				close(client_socket);
				continue;
			}

			pthread_detach(client_thread);
		}

	close(server_socket);
	close(pipe_fd);
	unlink("/tmp/pipe");
	unlink("/tmp/server_ready");

	return 0;
}
