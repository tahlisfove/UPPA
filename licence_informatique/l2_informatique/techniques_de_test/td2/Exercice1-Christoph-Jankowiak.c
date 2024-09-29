/*
 * Ent-tête nécessaire à la programmation.
 */
#include <stdio.h>
#include <stdlib.h>
/*
 * Définition des éléments de type booléen.
 */
typedef int bool;
#define FALSE 0
#define TRUE 1
/*
 * Fonction qui permet de remplir un tableau.
 */
void remplirTableau(int tableau[], int taille)
{
    for (int i = 0 ; i < taille ; i++)
    {
        printf("Entrez l'element %d : ", i + 1);
        scanf("%d", &tableau[i]);
    }
}
 /*
 * Fonction qui permet d'affficher un tableau.
 */
void afficheTableau(int tableau[], int taille)
{
    printf("Le tableau est le suivant: ");
    for (int i = 0 ; i < taille; i++)
    {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}
/*
 * Fonction de recherche dichotomique d'un élément dans un tableau trié.
 */
int look(int cle, int *tab, int taille, int trouve, int A)
{
    int droit, gauche;
    trouve = FALSE;
    droit = taille;
    gauche = 0;

    while(gauche <= droit && trouve == FALSE)
    {
        A = ((droit+gauche)/2);
        if (tab[A] == cle)
        {
            trouve = TRUE;
        }
        else
        {
            if(tab[A] > cle)
            {
                gauche = A+1;
            }
            else
            {
                droit = A-1;
            } 
        }
    }
    return trouve;
}
/*
 * Programme principal.
 */
int main(int argc, char *argv[])
{   
    int cle, taille, A;
    bool trouve;
    int tableau[taille];
    /*
     * On donne la taille du tableau.
     */
    printf("\nIndiquez la taille du tableau : ");
    scanf("%d", &taille);
    /*
     * Appel des fonctions pour remplir et afficher le tableau.
     */
    printf("\n");
    remplirTableau(tableau, taille);
    printf("\n");
    afficheTableau(tableau, taille);
    printf("\n");
    /*
     * On renseigne l'élément recherché et on appelle la fonction de recherche.
     */
    printf("Donner l'élément recherché : ");
    scanf("%d", &cle);
    if(look(cle, tableau, taille, trouve, A))
    {
        printf("\nL'élément est présent à l'indice %d dans la liste.\n\n", A);
    }   
    else
    {
        printf("\nL'élément n'est pas présent dans la liste.\n\n");
    } 
    return 0;
}
