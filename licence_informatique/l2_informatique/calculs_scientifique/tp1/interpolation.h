#ifndef interpolation
#define interpolation

/*retourne la valeur li(x) où x est le point en lequel on évalue le polynôme et li est le i-ème polynomede Lagrange de degrénassocié aux abscisses X[0], X[1],···X[?].*/
double base_lagrange (double x ,int i ,double * X ,int n);

/*permet d’évaluer le polynôme d’interpolation de Lagrange P en x où P est le polynôme de degré n tel que P(X[i])=Y[i]. Cette fonction contient des appels à la fonction base_lagrange.*/
double eval_p_lagrange (double x ,double * X ,double * Y ,int n);

/*permet de remplir le vecteur N des coefficients des différences divisées où le vecteur X (resp.Y) correspond aux abscisses (resp. aux ordonnées) des points à interpoler et n est le degré du polynôme.*/
void differences_divisees (double * N ,double * X ,double * Y ,int n);

/*permet d’évaluer le polynôme d’interpolation P en x où P est le polynôme de degré n tel que P(X[i])=Y[i].*/
double eval_p_dd (double x ,double * N ,double * X ,int n);

#endif
