// Directive de préprocesseur qui permet de s'assurer que ce fichier n'est inclus qu'une seule fois
#ifndef TIREUSES_H
#define TIREUSES_H

// Inclusion de la bibliothèque string.h pour la manipulation de chaînes de caractères
#include <string.h>
#include <stdbool.h>

// Inclusions du fichier header d'un autre module
#include "../Barman/controle/utils/utils.h"

// Définition de constantes pour la quantité de bière servie
#define DEMI 250
#define PINTE 500

// Définition de constantes pour le temps de service pour chaque quantité de bière
#define TEMPS_SERVIR_DEMI 2
#define TEMPS_SERVIR_PINTE 4

// Définition d'une structure pour représenter une tireuse
typedef struct
{
    char type[20];
    char nom[20];
    char degre[5];
    int quantite;
} Tireuse;

// Déclaration d'une variable externe définie dans un autre fichier
extern int fut_vide[];

// Déclaration des fonctions pour gérer les tireuses
extern bool servir(int ml, Tireuse *tireuse);
extern void init_tireuses(Tireuse *tireuses);
extern void afficher_tireuses(Tireuse *tireuses);
extern void update_tireuse(Tireuse *tireuse, const char *type, const char *nom, const char *degre);

// Fin de la directive de préprocesseur
#endif
