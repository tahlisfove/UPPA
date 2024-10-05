// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef CONTROLE_H
#define CONTROLE_H

// Inclusion de bibliothèques standard de C
#include <signal.h>

// Inclusions des fichiers header de différents modules
#include "../main/scheduler/scheduler.h"
#include "cleaning/cleaning.h"
#include "udp/udp.h"

// Déclaration de la fonction principale
int main(int argc, char *argv[]);

// Fin de la directive de préprocesseur
#endif
