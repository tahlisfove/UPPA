// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef UTILS_H
#define UTILS_H

// Inclusion des bibliothèques standard de C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

// Déclaration des fonctions
void print_beer_filling(int left, int total);
void clear_terminal();
void afficher_dessin();
void disable_echo();
void enable_echo();
void flush_stdin();

// Fin de la directive de préprocesseur
#endif