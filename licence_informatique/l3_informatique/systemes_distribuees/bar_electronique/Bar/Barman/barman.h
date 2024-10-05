// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef BARMAN_H
#define BARMAN_H

#define NB_PROCESSUS 3 // nombre de procesus
#define TEMPS_EXECUTION_MAX 100000 // temps d'exécution maximal en microsecondes

// Inclusion de bibliothèques standard de C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <netinet/in.h>

// Déclaration de la fonction principale
int main(int argc, char *argv[]);
void alarm_handler();

// Fin de la directive de préprocesseur
#endif
