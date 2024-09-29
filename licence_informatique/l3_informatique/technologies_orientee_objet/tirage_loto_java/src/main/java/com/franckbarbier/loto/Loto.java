package com.franckbarbier.loto;

public class Loto {

    private final static int _Borne = 48;
    private final int[] _resultat_tirage = new int[_Borne];
    // Générateur de nombres aléatoires :
    private final java.util.Random _random = new java.util.Random((new java.util.Date()).getTime());

    public void afficher() {
        for (int i = 0; i < _Borne; i++) {
            System.out.print("\t" + _resultat_tirage[i]);
        }
    }

    public void tirer() {
        for (int i = 0; i < _Borne; i++) {
            _resultat_tirage[i] = _tirer_en_interne(i);
        }
    }

    /* On cherche à tirer 48 numéros, soit 8 grilles de loto où figurent dans chacune 6 numéros. 
     L'idée est de tirer 48 numéros différents parmi 49 pour maximiser nos chances. */
    private int _tirer_en_interne(final int i) {
        int resultat = _random.nextInt(_Borne) + 1; // Valeur dans l'intervalle [1 - '_Borne']
        boolean deja_tire = false; // On fait l'hypothèse que ce nombre n'a pas encore été tiré...
        for (int j = 0; j < i; j++) { // On regarde le début du tableau pour vérifier ce qui a déjà été tiré...
            if (resultat == _resultat_tirage[j]) { // Si déjà tiré...
                deja_tire = true;
                break; // On arrête brutalement la boucle 'for', inutile d'aller plus loin...
            }
        }
        if (deja_tire) {
            return _tirer_en_interne(i); // On recommence le tirage
        }
        return resultat; // Sinon, c'est bon
    }
}
