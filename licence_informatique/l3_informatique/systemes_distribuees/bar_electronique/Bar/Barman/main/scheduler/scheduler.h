#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../main.h"


typedef struct Node {
    Commande cmd;
    struct Node* next;
} Node;

bool handle_request(int client_id, int biere, int quantite);
void push_commande(Commande cmd);
bool pop_commande(Commande* cmd);
void *fifo_scheduler(void *arg);

#endif
