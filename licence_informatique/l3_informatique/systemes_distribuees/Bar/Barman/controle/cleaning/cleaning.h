// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef CLEANING_H
#define CLEANING_H

// Inclusion de bibliothèques standard de C
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>

// Inclusion de la structure Tireuse définie dans un autre fichier
#include "../../../Tireuses/tireuses.h"
// Inclusions des fichiers header d'autres modules
#include "../utils/utils.h"

// Déclaration de variables globales externes
extern int running;
extern int sockfd;
extern Tireuse *tireuses;
extern pthread_mutex_t mutex;
extern pthread_t check_thread, udp_thread;

// Déclaration des fonctions
void signal_handler(int sig);
void cleanup();

// Fin de la directive de préprocesseur
#endif
