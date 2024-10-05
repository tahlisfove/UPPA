// Inclusion du fichier header "mutex.h"
#include "mutex.h"

// Fonction pour initialiser la mémoire partagée
void init_shm(Tireuse **tireuses) {
    // Initialiser le mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        // Supprimer le fichier partagé
        remove("shmfile");
        // Exécuter une fonction de nettoyage
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Obtenir une clé unique pour la mémoire partagée
    key_t key = ftok("shmfile", 65);
    // Obtenir un identifiant de mémoire partagée
    int shmid = shmget(key, 2 * sizeof(Tireuse), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget() failed");
        // Supprimer le fichier partagé
        remove("shmfile");
        // Exécuter une fonction de nettoyage
        cleanup();
        exit(EXIT_FAILURE);
    }
    // Attacher la mémoire partagée
    *tireuses = (Tireuse*)shmat(shmid, NULL, 0);
    // Initialiser les tireuses dans la mémoire partagée
    init_tireuses(*tireuses);
}

// Fonction pour surveiller les tireuses
void *check_tireuses(void *arg) {
    // Convertir l'argument en pointeur Tireuse
    Tireuse *tireuses = (Tireuse *)arg;
    // Boucle infinie tant que le programme n'est pas stoppé
    while (running) {
        // Attendre deux secondes
        sleep(2);
        // Verrouiller le mutex
        pthread_mutex_lock(&mutex);

        // Parcourir les tireuses
        for (int i = 0; i < 2; i++) {
            // Récupérer la tireuse courante
            Tireuse *tireuse = &tireuses[i];
            // Vérifier si la tireuse est vide et si un signal n'a pas déjà été envoyé
            if (tireuse->quantite == 0 && fut_vide[i] == 0) {
                // Marquer que le signal a été envoyé
                fut_vide[i] = 1;
                // Déverrouiller le mutex
                pthread_mutex_unlock(&mutex);

                // Affichage qui previens le barman qu'un fut est vide
                printf("\n");
                printf("\n  +---------------------------------------------------------------------+");
                printf("\n       Fût de bière %s vide, lancement du processus de commande.", tireuse->type );
                printf("\n  +---------------------------------------------------------------------+");
                printf("\n");

                // Lancer le processus de commande
                lancer_processus_commande(adresse_ip, port, adresse_fournisseur, i+1);

                // Verrouiller le mutex
                pthread_mutex_lock(&mutex);
            }
        }
        // Déverrouiller le mutex
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Fonction pour lancer le processus de commande
void lancer_processus_commande(char *adresse_ip, int port, char *adresse_fournisseur, int num_fut) {
    // Initialisation des chaînes de caractéres nécessaire a l'ouverture du terminal
    char commande[500];
    char repertoire[PATH_MAX];

    // Récupérer le répertoire courant
    if (getcwd(repertoire, sizeof(repertoire)) == NULL) {
        perror("getcwd() error");
        // Supprimer le fichier partagé
        remove("shmfile");
        // Exécuter la fonction de nettoyage
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Ajouter le nom du dossier contenant le processus de commande
    strcat(repertoire, "/Bar/Barman/commande");

    // Utilisation de snprintf pour éviter le dépassement de mémoire
    snprintf(commande, sizeof(commande), "gnome-terminal -- bash -c 'cd %s && javac ProcessusCommande.java && java ProcessusCommande %s %d %s %d; exec bash'", repertoire, adresse_ip, port, adresse_fournisseur, num_fut);
    //snprintf(commande, sizeof(commande), "gnome-terminal -- bash -c 'javac ProcessusCommande.java && mv ProcessusCommande.class build/ && cd build && java ProcessusCommande %s %d %s %d; exec bash'", adresse_ip, port, adresse_fournisseur, num_fut);

    // Exécution la commande
    int system_ret = system(commande);
    if (system_ret == -1) {
        perror("system() failed");
        // Supprimer le fichier partagé
        remove("shmfile");
        // Exécuter la fonction de nettoyage
        cleanup();
        exit(EXIT_FAILURE);
    }
}
