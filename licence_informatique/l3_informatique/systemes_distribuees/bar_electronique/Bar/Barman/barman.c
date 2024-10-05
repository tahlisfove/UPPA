#include "barman.h"

int shm_id;
int *current_process;

void alarm_handler() {
    *current_process = (*current_process + 1) % 3;
    alarm(1);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "compilation: %s <tcp_port> <ip_bar> <ip_fournisseur> <udp_port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    char *ip_address = argv[2];
    int udp_port = atoi(argv[3]);
    char *ip_bar = argv[4];

    pid_t main_pid, server_pid, control_pid;
    pid_t pids[3];

    // Crée un segment de mémoire partagée
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Attache le segment de mémoire partagée
    current_process = (int *)shmat(shm_id, NULL, 0);
    if (current_process == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    *current_process = 0;

    // Crée le processus "Main"
    main_pid = fork();
    if (main_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (main_pid == 0) {
        // Attache le segment de mémoire partagée dans le processus enfant
        current_process = (int *)shmat(shm_id, NULL, 0);
        if (current_process == (int *)-1) {
            perror("shmat");
            exit(1);
        }

        while (1) {
            if (*current_process == 0) {
                if (execl("./build/main", "Main.out", (char *)NULL) == -1) {
                    perror("execl");
                    exit(1);
                }
            }
            usleep(1000);
        }
    }
    // Crée le processus "Serveur"
    server_pid = fork();
    if (server_pid == 0) {
        // Attache le segment de mémoire partagée dans le processus enfant
        current_process = (int *)shmat(shm_id, NULL, 0);
        if (current_process == (int *)-1) {
            perror("shmat");
            exit(1);
        }

        while (1) {
            if (*current_process == 1) {
                char port_str[6];
                snprintf(port_str, sizeof(port_str), "%d", port);
                if(execl("./build/communication", "serveur.out", port_str, (char *)NULL)== -1){
                    perror("execl");
                    exit(1);
                }
            }
            usleep(1000);
        }
    }

    control_pid = fork();
    if (control_pid == 0) {
        // Attach shared memory segment in child process
        current_process = (int *)shmat(shm_id, NULL, 0);
        if (current_process == (int *)-1) {
            perror("shmat");
            exit(1);
        }

        while (1) {
            if (*current_process == 2) {
                char udp_port_str[6];
                snprintf(udp_port_str, sizeof(udp_port_str), "%d", udp_port);
                if(execl("./build/controle", "controle.out", ip_address, udp_port_str, ip_bar, (char *)NULL)== -1){
                    perror("execl");
                    exit(1);
                }
            }
            usleep(1000);
        }
    }

    pids[0] = main_pid;
    pids[1] = server_pid;
    pids[2] = control_pid;

    signal(SIGALRM, alarm_handler);
    alarm(1);

    int status;
    for (int i = 0; i < 3; i++) {
        waitpid(pids[i], &status, 0);
    }

    // Detach shared memory segment
    shmdt(current_process);

    // Remove shared memory segment
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

