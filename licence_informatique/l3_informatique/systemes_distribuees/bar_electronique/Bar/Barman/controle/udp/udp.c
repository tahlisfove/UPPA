// Inclusion du fichier header "udp.h"
#include "udp.h"


// Fonction de création de socket UDP
int creerSocketUDP(int port) {
    // Déclaration d'une structure pour l'adresse du serveur
    struct sockaddr_in servaddr;

    // Création d'un descripteur de fichier pour la socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Initialisation de l'adresse du serveur
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    // Attachement de la socket à l'adresse du serveur
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind failed");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Retourne le descripteur de fichier de la socket créée
    return sockfd;
}

// Fonction de gestion du thread UDP
void *handle_udp_thread(void *arg) {
    // Récupération des arguments passés à la fonction
    UdpThreadArgs *udp_thread_args = (UdpThreadArgs *)arg;
    int sockfd = udp_thread_args->sockfd;
    Tireuse *tireuses = udp_thread_args->tireuses;

    // Déclaration de variables pour recevoir les données du client
    char buffer[1024];
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);

    // Boucle de réception des données du client
    while (running) {
        // Initialisation du buffer à zéro
        memset(buffer, 0, sizeof(buffer));
        // Réception des données du client
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);

        // Affichage de la nouvelle bière reçue
        printf("\n");
        printf("\n  +---------------------------------------------------------------------+");
        printf("\n       Nouvelle bière reçue : %-20s", buffer);
        printf("\n  +---------------------------------------------------------------------+");
        printf("\n");

        // Initialisation des variables utiles pour récupérer les informations sur la biére reçu
        char *type;
        char *nom;
        char *degre;

        // Séparation des données reçues en type, nom et degré d'alcool
        type = strtok(buffer, ",");
        nom = strtok(NULL, ",");
        degre = strtok(NULL, ",");

        // Mise à jour de la tireuse vide
        if (tireuses[0].quantite == 0) {
            update_tireuse(&tireuses[0], type, nom, degre);
        } else if (tireuses[1].quantite == 0) {
            update_tireuse(&tireuses[1], type, nom, degre);
        } else {
            printf("\n  +---------------------------------------------------------------------+");
            printf("\n                Aucun fût vide pour mettre à jour la bière               ");
            printf("\n  +---------------------------------------------------------------------+");
            printf("\n\n");
        }
        // Affichage des tireuses mises à jour
        afficher_tireuses(tireuses);
    }
    // Fin de la fonction
    return NULL;
}
