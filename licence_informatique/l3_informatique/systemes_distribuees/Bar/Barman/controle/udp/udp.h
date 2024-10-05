// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef UDP_H
#define UDP_H

// Inclusions de bibliothèques standard de C
#include <string.h>
#include <arpa/inet.h>

// Inclusion de la structure Tireuse définie dans un autre fichier
#include "../../../Tireuses/tireuses.h"
// Inclusion des fonctions utilitaires définies dans un autre fichier
#include "../utils/utils.h"
#include "../cleaning/cleaning.h"
#include "../../main/main.h"


// Définition d'une structure pour stocker les arguments passés à la fonction handle_udp_thread
typedef struct {
    int sockfd;
    Tireuse *tireuses;
} UdpThreadArgs;

// Déclaration des variables externes définies dans un autre fichier
extern int running;
extern Tireuse *tireuses;
extern void cleanup();

// Déclaration des fonctions
int creerSocketUDP(int port);
void *handle_udp_thread(void *arg);

// Fin de la directive de préprocesseur
#endif
