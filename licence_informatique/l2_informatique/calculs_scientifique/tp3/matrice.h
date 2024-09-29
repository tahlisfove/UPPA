#ifndef MATRICE_H
#define MATRICE_H

/* 
réalise l’affichage d’un vecteur x de taille n sous la forme d’une simple colonne de nombres */
void afficheVec(double *x, int n);

/* 
réalise l’affichage d’une matrice A de taille n × n sous la forme d’un simple tableau de nombres */
void afficheMat(double *A, int n);

/* 
permet de calculer le produit y=Ax de la matrice A par le vecteur x */
void prodMatVec(double *A, double *x, double *y, int n);

/* 
permet de calculer le produit C=AB de la matrice A par une matrice B */
void prodMatMat(double *A, double *B, double *C, int n);

/* 
permet de résoudre un système linéaire triangulaire inférieur Ly=b */
void descente(double *L, double *b, double *y, int n);

/* 
permet de résoudre un système linéaire triangulaire supérieur y=Ux */
void remontee(double *U, double *y, double *x, int n);

/* 
réalise la décomposition LU d’une matrice A */
void decompositionLU(double *A, double *L, double *U, int n);

/* 
résout le système linéaire Ax=b, la fonction utilise les fonctions decomposition LU, descente et remontee */
void resolutionSystLin(double *A, double *b, double *x, int n);

/*
permet de calculer l’inverse B=A(−1) d’une matrice A */
void inverse(double *A, double *B, int n);

/* 
effectue une seule fois la décomposition LU de A pour calculer l’inverse de la matrice A */
void inverse_opt(double *A, double *B, int n);

#endif