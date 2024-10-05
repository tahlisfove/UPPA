// Inclusion du fichier header "utils.h"
#include "utils.h"

// Fonction pour afficher la barre de remplissage de la bière
void print_beer_filling(int left, int total) {
    // Calcul du pourcentage de remplissage
    int progress = total - left;
    int bar_width = 50; // Largeur de la barre de progression
    float ratio = (float)progress / (float)total;
    int filled = (int)(ratio * bar_width);

    // Affichage du texte de remplissage
    printf("\n  +---------------------------------------------------------------------+");
    printf("\n  |                 Remplissage de la bière en cours...                 |");
    printf("\n  +---------------------------------------------------------------------+");
    printf("\n\n");

    // Affichage de la barre de progression
    printf("         |");
    for (int i = 0; i < filled; i++) {
        printf("█");
    }

    for (int i = 0; i < (bar_width - filled); i++) {
        printf("░");
    }
    printf("| ");

    // Affichage du pourcentage de remplissage
    printf(" %3.1f%%", ratio * 100);

    // Affichage du temps restant avant que la bière ne soit complètement remplie
    printf("\n");
    printf("\n  +---------------------------------------------------------------------+");
    printf("\n                        Temps restant: %d secondes", left);
    printf("\n  +---------------------------------------------------------------------+");
    printf("\n");
}

// Fonction pour effacer la console
void clear_terminal() {
    // Efface la console en appelant la commande système "clear"
    system("clear");
}

void afficher_dessin() {
		printf("                                  \n\n");
	    printf("                                    /\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                                     |\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                                  .-/',;\\-.\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                                  |'\\\\;;;\\'\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                                  |:| \\;'\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                                  |'|\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                                  |:|\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                      ____________|'|______\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |'.           |:|      '.\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |  '. ___________________'.\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |.-------------------.._\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    ||       |'|         || `--._\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    || _..--'|:|'--.._   ||      `-._\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |||'--..____..--'|   |[]        ||\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |||              |   ||         ||\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |||              |   ||         ||\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    ||]'--..____..--'[   ||         ||\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |||              |   ||         ||\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |L|              |   ||         ||\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |||              |   ||         J|\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    ||]'--..____..--'[   ||         ||\n");
	    usleep(30000);  // attendre 0,1 seconde
	    printf("                    |    |||              |   ||         ||\n");
	    usleep(30000);  // attendre 0,1 seconde
		printf("                    |    |||              |.  |[]        ||\n");
		usleep(30000);  // attendre 0,1 seconde
		printf("                    |    ||'--..______..--' '.||         ||\n");
		usleep(30000);  // attendre 0,1 seconde
		printf("                    |    |'-------------------'|         ||\n");
		usleep(30000);  // attendre 0,1 seconde
		printf("                     '.  | Beer Box ||..___..||`--._     ||\n");
		usleep(30000);  // attendre 0,1 seconde
		printf("                       '.|____________________|     `--._||\n\n");
		usleep(30000);  // attendre 0,1 seconde
}


// Fonction pour désactiver l'affichage des caractères saisis et du mode canonique
void disable_echo() {
    // Déclaration d'une structure pour les attributs de la console
    struct termios tty_attr;
    // Récupération des attributs de la console
    tcgetattr(STDIN_FILENO, &tty_attr);
    // Désactivation de l'affichage des caractères saisis et du mode canonique
    tty_attr.c_lflag &= ~(ECHO | ICANON);
    // Réglage des attributs de la console
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_attr);
}

// Fonction pour activer l'affichage des caractères saisis et du mode canonique
void enable_echo() {
    // Déclaration d'une structure pour les attributs de la console
    struct termios tty_attr;
    // Récupération des attributs de la console
    tcgetattr(STDIN_FILENO, &tty_attr);
    // Activation de l'affichage des caractères saisis et du mode canonique
    tty_attr.c_lflag |= (ECHO | ICANON);
    // Réglage des attributs de la console
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_attr);
}

// Fonction pour vider le buffer d'entrée standard
void flush_stdin() {
    int c;
    // Boucle pour vider le buffer d'entrée standard jusqu'à ce qu'il soit vide
    while (((c = getchar()) != '\n' && c != EOF));
}
