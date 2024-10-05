#include "scheduler.h"

Node* commandes = NULL;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

bool handle_request(int client_id, int biere, int quantite) {
    printf("Commande reçue du client %d : bière ", client_id);
    if (biere == 1) {
        printf("blonde ");
    } else if (biere == 2) {
        printf("ambrée ");
    }
    printf("en quantité de ");
    if (quantite == 1) {
        printf("demi");
        quantite = 250;
    } else if (quantite == 2) {
        printf("pinte");
        quantite = 500;
    }
    printf("\n");

    bool boisson_ok = servir(quantite, &tireuses[biere - 1]);

    if (boisson_ok == true) {
        return true;
    } 
    return false;
}

void push_commande(Commande cmd) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->cmd = cmd;
    new_node->next = NULL;

    if (commandes == NULL) {
        commandes = new_node;
    } else {
        Node* temp = commandes;
        while (temp->next != NULL) {
            temp = temp->next;

        }
        temp->next = new_node;
    }}

bool pop_commande(Commande* cmd) {
    if (commandes == NULL) {
        return false;
    }

    Node* temp = commandes;
    *cmd = temp->cmd;
    commandes = commandes->next;
    free(temp);
    return true;
}


void *fifo_scheduler(void *arg) {
    Commande cmd;
    int pipe_fd = *(int *)arg;
    int client_id, biere, quantite;
    char buffer[BUFFER_SIZE];
    char confirmation[BUFFER_SIZE];
    char beer_info[BUFFER_SIZE];

    int pipe_confirm_fd = open(PIPE_CONFIRM_PATH, O_WRONLY);
    if (pipe_confirm_fd == -1) {
        perror("Erreur lors de l'ouverture du pipe de confirmation");
        exit(1);
    }

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t read_bytes = read(pipe_fd, buffer, BUFFER_SIZE);
        if (read_bytes == -1) {
            perror("Erreur lors de la lecture du pipe");
            break;
        }
        if (read_bytes == 0) {
            printf("Pipe fermé, arrêt du thread\n");
            break;
        }
        int client_choice;
        sscanf(buffer, "%d,%d,%d,%d", &client_choice,&client_id,&biere,&quantite);
        if (client_choice == 1) {
            // Traiter le choix 1
            printf("  - Paire %d demande des informations sur les bières\n", client_id);

            // Préparer le message avec les informations des deux bières
                        snprintf(beer_info, BUFFER_SIZE, "  - Bière %s:%s,%s\n    - Bière %s:%s,%s\n", tireuses[0].type, tireuses[0].nom, tireuses[0].degre, tireuses[1].type, tireuses[1].nom, tireuses[1].degre);

            write(pipe_confirm_fd, beer_info, strlen(beer_info) + 1);
            // Envoyer les informations des bières au client
        }
        else if (client_choice==2){
            sscanf(buffer, "%d,%d,%d,%d", &client_choice,&client_id, &biere, &quantite);
            pthread_mutex_lock(&queue_mutex); // Verrouillage du mutex
            Commande cmd = {client_id, biere, quantite};
            push_commande(cmd); // Ajout de la commande à la file d'attente
            pthread_mutex_unlock(&queue_mutex); // Déverrouillage du mutex

            // Traitement des commandes dans l'ordre
            while (true) {
                pthread_mutex_lock(&queue_mutex);
                if (pop_commande(&cmd)) {
                    pthread_mutex_unlock(&queue_mutex);
                    bool rep = handle_request(cmd.client_id, cmd.biere, cmd.quantite);

                    if (rep) {
                        afficher_tireuses(tireuses);
                        snprintf(confirmation, BUFFER_SIZE, "votre boisson est prête, voici votre %s de %s", (quantite == 1) ? "demi" : "pinte", (biere == 1) ? "bière blonde" : "bière ambrée");
                        } else {
                        snprintf(confirmation, BUFFER_SIZE, "votre boisson ne peut pas etre servi, nous sommes à sec...");
                        }
                        write(pipe_confirm_fd, confirmation, strlen(confirmation) + 1);
                    } else {
                        pthread_mutex_unlock(&queue_mutex);
                        break;
                    }
            }
        }
    }
    close(pipe_fd);
    close(pipe_confirm_fd);
    unlink(PIPE_PATH);
    unlink(PIPE_CONFIRM_PATH);
    return NULL;
}
