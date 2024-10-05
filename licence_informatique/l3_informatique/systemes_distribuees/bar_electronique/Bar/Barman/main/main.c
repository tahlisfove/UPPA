#include "main.h"

pthread_t check_thread, udp_thread;
pthread_mutex_t mutex;
Tireuse *tireuses;

int sockfd;
char *adresse_ip;
int port;
char *adresse_fournisseur;




int main() {
    pthread_t scheduler_thread;

    init_shm(&tireuses);

    unlink(PIPE_PATH);
    unlink(PIPE_CONFIRM_PATH);

    if (mkfifo(PIPE_PATH, 0666) == -1) {
        perror("Erreur lors de la création du pipe");
        exit(1);
    }

    if (mkfifo(PIPE_CONFIRM_PATH, 0666) == -1) {
        perror("Erreur lors de la création du pipe de confirmation");
        exit(1);
    }

    int pipe_fd = open(PIPE_PATH, O_RDWR);
    if (pipe_fd == -1) {
        perror("Erreur lors de l'ouverture du pipe");
        exit(1);
    }

    while (access("/tmp/server_ready", F_OK) == -1) {
        usleep(100000);
    }

    if (pthread_create(&scheduler_thread, NULL, fifo_scheduler, (void *)&pipe_fd) != 0) {
        perror("Erreur lors de la création du thread");
        exit(2);
    }

    pthread_join(scheduler_thread, NULL);

    close(pipe_fd);
    unlink(PIPE_PATH);
    unlink(PIPE_CONFIRM_PATH);
    free(tireuses);
    unlink("/tmp/server_ready");

    return 0;
}
