// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef CLIENTS_H
#define CLIENTS_H


#define TAILLEBUF 1024
#define SERVER_NAME_LEN_MAX 255

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>


// Inclusions du fichier header d'un autre module
#include "tcp/tcp.h"
#include "../Bar/Tireuses/tireuses.h"
#include "../Bar/Barman/controle/mutex/mutex.h"
#include "../Bar/Barman/controle/utils/utils.h"
#include "../Bar/Barman/controle/cleaning/cleaning.h"


extern Tireuse *tireuses;
extern int running;

// Déclaration des la fonction principale
int main(int argc, char *argv[]);

// Fin de la directive de préprocesseur
#endif
