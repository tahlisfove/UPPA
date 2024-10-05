// Inclusion du fichier header "cleaning.h"
#include "cleaning.h"
int running = 1;
// Fonction pour gérer les signaux reçus
void signal_handler(int sig) {
    printf("\n");
    printf("\n  +---------------------------------------------------------------------+");
    printf("\n              Signal reçu : %d, arrêt du programme en cours...", sig);
    printf("\n  +---------------------------------------------------------------------+");
    printf("\n");

    // Mettre la variable "running" à 0 pour arrêter les threads
    running = 0;

    // Annuler les threads et attendre leur terminaison
    pthread_cancel(check_thread);
    pthread_cancel(udp_thread);
    pthread_join(check_thread, NULL);
    pthread_join(udp_thread, NULL);

    // Appeler la fonction "cleanup"
    cleanup();

    // Quitter le programme */
    exit(0);
}

// Fonction pour nettoyer les ressources utilisées par le programme
void cleanup() {
    // Fermer le socket s'il est ouvert
    if (sockfd != -1) {
        close(sockfd);
    }

    // Détacher la mémoire partagée
    if (tireuses != NULL) {
        shmdt(tireuses);
    }

    // Supprimer la mémoire partagée
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 2 * sizeof(Tireuse), 0666);
    shmctl(shmid, IPC_RMID, NULL);

    // Détruire le mutex
    pthread_mutex_destroy(&mutex);

    // Réactiver l'affichage des caractères saisis au clavier
    enable_echo();
}
