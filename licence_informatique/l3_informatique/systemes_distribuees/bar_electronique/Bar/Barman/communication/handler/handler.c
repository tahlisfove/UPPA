
#include "handler.h"


void *client_handler(void *arg) {
    
client_data_t *client_data = (client_data_t *)arg;
	int client_socket = client_data->client_socket;
	int pipe_fd = client_data->pipe_fd;
	int client_id = client_data->client_id;
	int biere, quantite;
	int choix;
	char buffer[BUFFER_SIZE];
	char pipe_message[BUFFER_SIZE];

	int pipe_confirm_fd = open(PIPE_CONFIRM_PATH, O_RDONLY);
	if (pipe_confirm_fd == -1) {
		perror("erreur lors de l'ouverture du pipe de confirmation");
		close(client_socket);
		close(pipe_fd);
		exit(EXIT_FAILURE);
	}

	while (1) {
		
		memset(buffer, 0, BUFFER_SIZE);
		int len = recv(client_socket, buffer, BUFFER_SIZE, 0);
		if (len <= 0) {
			printf("  - Paire %d déconnecté\n", client_data->client_id);
			close(client_socket);
			break;
		}
		sscanf(buffer, "%d,%d,%d", &choix,&biere, &quantite);
			switch(choix){
				case 1:
					memset(pipe_message, 0, BUFFER_SIZE);
					snprintf(pipe_message, BUFFER_SIZE, "%d,%d,0,0", choix,client_id);
					write(pipe_fd, pipe_message, strlen(pipe_message));              
					break;
				case 2:
					memset(pipe_message, 0, BUFFER_SIZE);
					snprintf(pipe_message, BUFFER_SIZE, "%d,%d,%d,%d", choix,client_id, biere, quantite);
					write(pipe_fd, pipe_message, strlen(pipe_message));
					break;

				default:
					printf("  - Paire %d a envoyé un choix invalide\n", client_id);
			}
			memset(buffer, 0, BUFFER_SIZE);
			ssize_t read_bytes = read(pipe_confirm_fd, buffer, BUFFER_SIZE);
			send(client_socket, buffer, strlen(buffer) + 1, 0);
		}

		close(client_socket);
		close(pipe_confirm_fd);
		free(arg);
		return NULL;
	}