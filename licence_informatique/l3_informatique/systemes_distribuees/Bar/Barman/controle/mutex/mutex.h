// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef MUTEX_H
#define MUTEX_H

// Définition d'un constante pour la taille de la commande
#define PATH_MAX 200

// Inclusions de bibliothèques standard de C
#include <pthread.h>
#include <sys/shm.h>

// Inclusion de la structure Tireuse définie dans un autre fichier
#include "../../../Tireuses/tireuses.h"

// Déclaration des variables externes définies dans un autre fichier
extern pthread_mutex_t mutex;
extern int running;
extern char *adresse_ip;
extern char *adresse_fournisseur;
extern int port;
extern int fut_vide[];
extern void cleanup();

// Déclaration des fonctions
void init_shm(Tireuse **tireuses);
void *check_tireuses(void *arg);
void lancer_processus_commande(char *adresse_ip, int port, char *adresse_fournisseur, int num_fut);

// Fin de la directive de préprocesseur
#endif
