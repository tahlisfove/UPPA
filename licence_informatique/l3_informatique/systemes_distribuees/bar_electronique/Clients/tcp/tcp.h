// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef TCP_H
#define TCP_H

// Définition de la constante de taille d'une chaîne de caractères
#define BUF 256

// Inclusion de bibliothèques standard de C
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// Déclaration des fonctions pour gérer les clients et le menu
int creerSocketTCP(char *adresseIP, int port);

// Fin de la directive de préprocesseur
#endif
