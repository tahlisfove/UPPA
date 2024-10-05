// Inclusion du fichier header "tcp.h"
#include "tcp.h"

// Fonction pour créer une socket TCP client
int creerSocketTCP(char *adress_ip, int port) {
    int client_socket;
    struct sockaddr_in server_address;

    // Créer la socket client
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("erreur lors de la création de la socket client");
        exit(EXIT_FAILURE);
    }

    // Initialiser l'adresse du serveur
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(adress_ip);

    // Se connecter au serveur
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("erreur lors de la connexion");
        exit(EXIT_FAILURE);
    }
    return client_socket;
}
