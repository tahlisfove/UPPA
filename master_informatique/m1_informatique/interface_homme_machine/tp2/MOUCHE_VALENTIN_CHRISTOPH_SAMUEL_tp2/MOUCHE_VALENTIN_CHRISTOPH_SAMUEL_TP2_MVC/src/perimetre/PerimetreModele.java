package perimetre;

public class PerimetreModele {
    private float longueur;
    private float largeur;

    public float calculPerimetre(float largeur2, float longueur2) {
        float perimetre = 2 * (largeur2 + longueur2);
        return perimetre;
    }

    public float getLongueur() {
        return longueur;
    }

    public void setLongueur(float longueur) {
        this.longueur = longueur;
    }

    public float getLargeur() {
        return largeur;
    }

    public void setLargeur(float largeur) {
        this.largeur = largeur;
    }
}