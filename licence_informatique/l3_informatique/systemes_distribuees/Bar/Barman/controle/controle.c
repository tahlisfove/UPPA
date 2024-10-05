// Inclusion du fichier header "controle.h"
#include "controle.h"

// Variables globales
pthread_t check_thread, udp_thread;
pthread_mutex_t mutex;
Tireuse *tireuses; // Pointeur vers la mémoire partagée contenant les états des tireuses
int sockfd; // Descripteur de socket pour le socket UDP
char *adresse_ip; // Adresse IP du client
char *adresse_fournisseur; // Adresse IP du fournisseur
int port; // Port utilisé pour le socket UDP

// Fonction principale de controle
int main(int argc, char *argv[]) {

    // Vérifier que les arguments sont corrects
    if (argc != 4) {
        printf("compilation du processus de controle: ./%s <adresse_ip_client> <udp_port> <ip_fournisseur>\n", argv[0]);
        cleanup(); // Fonction de nettoyage des ressources
        exit(EXIT_FAILURE); 
    }

    // Récupérer les arguments
    adresse_ip = argv[1];
    port = atoi(argv[2]); 
    adresse_fournisseur = argv[3];

    // Initialiser la mémoire partagée
    init_shm(&tireuses); 

    // Créer le socket UDP
    sockfd = creerSocketUDP(port); 

    // Afficher l'état des tireuses
    afficher_tireuses(tireuses); 

    // Gérer les signaux
    signal(SIGINT, signal_handler); // Capturer le signal SIGINT (Ctrl+C)
    signal(SIGTERM, signal_handler); // Capturer le signal SIGTERM (fin de processus)
    signal(SIGPIPE, signal_handler); // Capturer le signal SIGPIPE (erreur lors de l'envoi ou de la réception de données)

    // Créer le thread pour surveiller l'état des tireuses
    pthread_create(&check_thread, NULL, check_tireuses, tireuses);
    UdpThreadArgs udp_thread_args = {sockfd, tireuses};

    // Créer les threads pour traiter les messages UDP
    pthread_create(&udp_thread, NULL, handle_udp_thread, &udp_thread_args); 

    // Attendre la terminaison du thread UDP
    pthread_join(udp_thread, NULL); 

    // Si le programme a été arrêté par un signal, arrêter les threads et fermer le socket
    if (!running) {
        close(sockfd); 
        pthread_cancel(check_thread); 
        pthread_cancel(udp_thread); 
        pthread_join(check_thread, NULL); 
        pthread_join(udp_thread, NULL);
    }

    return 0;
}
