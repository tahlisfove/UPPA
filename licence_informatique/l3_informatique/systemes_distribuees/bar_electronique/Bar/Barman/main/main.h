// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef MAIN_H
#define MAIN_H

typedef struct {
    int client_id;
    int biere;
    int quantite;
} Commande;

#include "../controle/utils/utils.h"
#include "../../Tireuses/tireuses.h"
#include "../controle/mutex/mutex.h"
#include "../controle/udp/udp.h"
#include "../controle/cleaning/cleaning.h"
#include "scheduler/scheduler.h"


#define BUFFER_SIZE 256

#define PIPE_PATH "/tmp/pipe"
#define PIPE_CONFIRM_PATH "/tmp/pipe_confirm"



extern pthread_t check_thread, udp_thread;
extern pthread_mutex_t mutex;
extern Tireuse *tireuses;
extern int running;
extern int sockfd;
extern int fut_vide[];
extern int port;
extern char *adresse_fournisseur;

bool handle_request(int client_id, int biere, int quantite);
void push_commande(Commande cmd);
void *fifo_scheduler(void *arg);
int main();

// Fin de la directive de préprocesseur
#endif