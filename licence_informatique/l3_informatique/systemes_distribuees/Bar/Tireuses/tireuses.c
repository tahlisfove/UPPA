// Inclusion du fichier header "tireuses.h"
#include "tireuses.h"

int fut_vide[2] = {0,0};

// Fonction servant à remplir un verre d'une quantité spécifiée à partir d'une tireuse donnée
bool servir(int ml, Tireuse *tireuse) {
    // Déterminer le temps total nécessaire pour remplir le verre
    int total = (ml == DEMI) ? TEMPS_SERVIR_DEMI : TEMPS_SERVIR_PINTE;

    // Vérifier si la tireuse contient suffisamment de bière pour servir la quantité demandée
    if (tireuse->quantite >= ml) {
        // Afficher un message indiquant que le service est en cours
        printf("\n");
        printf("   - En train de servir %d ml de %s...\n", ml, tireuse->nom);
        printf("\n");
        
        // Désactiver l'affichage des caractères saisis au clavier
        disable_echo();
        
        // Boucle pour simuler le remplissage du verre en temps réel
        for (int i = total; i >= 0; i--) {
            // Effacer le terminal et afficher le remplissage de la bière
            clear_terminal();
            print_beer_filling(i, total);
            
            // Attendre une seconde avant de passer à l'itération suivante, sauf pour la dernière
            if (i > 0) {
                usleep(1000000);
            } else {
                // Vider le tampon d'entrée standard et afficher un message de confirmation
                tcflush(STDIN_FILENO, TCIFLUSH);
                printf("\n");
                printf("   - %d ml de%s servis!", ml, tireuse->nom);
                printf("\n");
                usleep(1000000);
            }
        }
        // Soustraire la quantité servie de la tireuse 
        tireuse->quantite -= ml;
        return true;
    } else {
        // Afficher un message d'erreur si la tireuse ne contient pas suffisamment de bière
        printf("\n");
        printf("   - Pas assez de%s pour servir %d ml.\n", tireuse->nom, ml);
        printf("\n");
        return false;
    }
}

// Fonction pour initialiser les tireuses
void init_tireuses(Tireuse *tireuses) {
    // Initialiser la première tireuse
    strcpy(tireuses[0].type, "Blonde");
    strcpy(tireuses[0].nom, " Goudale");
    strcpy(tireuses[0].degre, " 10°");
    tireuses[0].quantite = 5000;

    // Initialiser la deuxième tireuse
    strcpy(tireuses[1].type, "Ambrée");
    strcpy(tireuses[1].nom, " Kwak");
    strcpy(tireuses[1].degre, " 5°");
    tireuses[1].quantite = 5000;
}

// Fonction pour afficher le contenu des tireuses
void afficher_tireuses(Tireuse *tireuses) {
    // Afficher un message d'en-tête
    printf("                                                            \n");
    printf("                +------------------------------------------+\n");
    printf("                |           Contenu des tireuses           |\n");
    printf("                +------------------------------------------+\n");

    // Parcourir chaque tireuse et afficher ses propriétés
    for (int i = 0; i < 2; i++) {
        printf("\n");
        printf("                            Tireuse %d - %s\n", i + 1, tireuses[i].type);
        printf("                               Nom :%s\n", tireuses[i].nom);
        printf("                               Degré :%s\n", tireuses[i].degre);
        printf("                               Quantité : %d\n", tireuses[i].quantite);
    }
    printf("                                                           \n");
    printf("                +-----------------------------------------+\n");

    // Réactiver l'affichage des caractères saisis au clavier
    enable_echo();
}

// Fonction pour mettre à jour une tireuse avec de nouvelles propriétés
void update_tireuse(Tireuse *tireuse, const char *type, const char *nom, const char *degre) {
    // Mettre à jour les propriétés de la tireuse
    for (int i=0; i>2; i++) {
        fut_vide[i] = 0;
    }
    afficher_dessin();
    strcpy(tireuse->type, type);
    strcpy(tireuse->nom, nom);
    strcpy(tireuse->degre, degre);
    tireuse->quantite = 5000;
    
}
