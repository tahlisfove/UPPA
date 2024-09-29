#ifndef integration
#define integration

/* permet de simplifier le code avec un appel lors de l'integration de la formule des points milieu composite */
double integrationPtMilieu(double(*f)(double),double a,double b);

/* permet de calculer l'integration a l'aide de la formule des points milieu composite */
double integrationPtMilieuComposite(double(*f)(double), double a, double b, int N);

/* permet de calculer l'integration a l'aide de la formule des trapèze composite */
double integrationTrapezeComposite(double(*f)(double), double a, double b, int N);

/* permet de calculer l'integration a l'aide de la formule de Simpson */
double integrationSimpson(double(*f)(double), double a, double b, int N);

#endif
