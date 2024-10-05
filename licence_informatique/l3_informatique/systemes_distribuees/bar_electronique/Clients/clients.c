
#include "clients.h"


  int running = 1;
  int sockfd;

int main(int argc, char *argv[]) {
    char buffer[TAILLEBUF];
    char server_name[SERVER_NAME_LEN_MAX + 1] = { 0 };
    int server_port;
    struct hostent *server_host;
    struct sockaddr_in server_address;

        // Vérifier que l'utilisateur a fourni deux arguments en ligne de commande : l'adresse IP et le port du serveur
    if (argc != 3) {
        printf("compilation: %s <adresse_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Get server name from command line arguments or stdin. */
    if (argc > 1) {
        strncpy(server_name, argv[1], SERVER_NAME_LEN_MAX);
    } else {
        printf("entrez un nom de serveur: ");
        scanf("%s", server_name);
    }

    /* Get server port from command line arguments or stdin. */
    server_port = argc > 2 ? atoi(argv[2]) : 0;
    if (!server_port) {
        printf("entrez le port du serveur: ");
        scanf("%d", &server_port);
    }

    /* Get server host from server name. */
    server_host = gethostbyname(server_name);
      if (server_host == NULL) {
        perror("echec lors de la recuperation de l'hote serveur");
        exit(EXIT_FAILURE);
    }

    /* Initialise IPv4 server address with server host. */
    memset(&server_address, 0, sizeof server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    memcpy(&server_address.sin_addr.s_addr, server_host->h_addr, server_host->h_length);

    /* Create TCP socket. */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("echec lors de la creation de la socket TCP");
        exit(EXIT_FAILURE);
    }


    /* Connect to socket with server address. */
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof server_address) == -1) {
		perror("erreur connexion serveur");
        exit(EXIT_FAILURE);
	}
    printf("  - Connexion etablie avec succès\n");

    // Création d'une socket TCP client
    int choix, biere, quantite;
    int running = 1;
    char input[BUF];
    

    // Afficher une bannière de bienvenue
    system("clear");
    printf("\n                    ***    Bienvenue au ni-bar    ***                    ");
    printf("\n                                                                         ");
    printf("\n                                                                         ");
    printf("\n                              ****     ****                              ");
    printf("\n                           **      ***      **                           ");
    printf("\n                         **                   **                         ");
    printf("\n                         **   0     *     0   **                         ");
    printf("\n                          **        *        **                          ");
    printf("\n                            *******   *******                            ");
    printf("\n                                                                         ");

    while (running) {
        // Afficher le menu et demander le choix de l'utilisateur
        printf("\n                                                                         ");
        printf("\n  +---------------------------------------------------------------------+");
        printf("\n  |                               Menu:                                 |");
        printf("\n  +---------------------------------------------------------------------+");
        printf("\n  |            1. Informations sur les bières disponibles               |");
        printf("\n  |                     2. Commander une bière                          |");
        printf("\n  |                       3. Quitter le bar                             |");
        printf("\n  +---------------------------------------------------------------------+");
        printf("\n\n\n");
        printf("  - Que souhaitez-vous: ");
        

        // Lire l'entrée de l'utilisateur
        fgets(input, BUF, stdin);
        printf("\n");

        // Vérifier que l'entrée est un chiffre et convertir l'entrée en entier
        if (isdigit(input[0])) {
            choix = atoi(input);
        } else {
            printf("choix invalide\n\n");
            continue;
        }

        switch (choix) {
            case 1:
                sprintf(buffer, "%d,%d,%d", choix, biere, quantite);
                // Envoyer la requête au serveur
                send(sockfd, buffer, strlen(buffer), 0);
                        
                // Recevoir la réponse du serveur
                int read_bytes = recv(sockfd, buffer, BUF, 0);
                if (read_bytes <= 0) {
                    printf("erreur lors de la réception de la confirmation\n");
                    return -1;
                }
                // Afficher la confirmation
                printf("  %s  \n", buffer);
                break;
            case 2:
                do {
                    printf("  - Quelle type de bière voulez-vous? blonde(1) ou ambrée(2): ");
                    fgets(input, BUF, stdin);
                    if (isdigit(input[0])) {
                        biere = atoi(input);
                    } else {
                        printf("type de bière invalide\n\n");
                        biere=0;
                        continue;
                    }
                } while (biere < 1 || biere > 2);

                do {
                    printf("  - En quelle quantité? demi(1) ou pinte(2): ");
                    fgets(input, BUF, stdin);
                    if (isdigit(input[0])) {
                        quantite = atoi(input);
                    } else {
                        printf("quantité invalide\n\n");
                        quantite=0;
                        continue;
                    }
                } while (quantite < 1 || quantite > 2);

                printf("  - Votre commande: ");
                if (biere == 1) {
                    printf("blonde ");
                } else if (biere == 2) {
                    printf("ambrée ");
                }
                printf("en ");
                if (quantite == 1) {
                    printf("demi, ");
                } else if (quantite == 2) {
                    printf("pinte, ");
                }
                printf("confirmation? (o/n): ");
                fgets(input, BUF, stdin);
                if (input[0] == 'o' || input[0] == 'O') {
                    printf("préparation de votre commande...");
                    sprintf(buffer, "%d,%d,%d", choix, biere, quantite);
                    send(sockfd,buffer,strlen(buffer), 0);
                    int read_bytes = recv(sockfd, buffer, BUF, 0);
                if (read_bytes <= 0) {
                    printf("erreur lors de la réception de la confirmation\n");
                    return -1;
                }
                    // Afficher la confirmation
                    printf("\n\n\n  %s  \n", buffer);
                } else if (input[0] == 'n' || input[0] == 'N') {
                    printf("retour au menu...\n");
                } else {
                    printf("confirmation invalide, êtes vous saoul...\n");
                }

                break;

            case 3:
                printf("\ndéconnexion du bar...\n");
                close(sockfd);
                exit(EXIT_FAILURE);

            default:
                printf("\noption du menu invalide\n");

                break;
        }
    }
    return 0;
}
