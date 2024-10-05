/**
 * 
 * Implémentation de la classe Biere
 */
public class Biere implements java.io.Serializable {

    /**
     * Nom de la bière
     */
    protected String nom;

    /**
     * Couleur de la bière
     */
    protected int couleur;

    /**
     * Degré de la bière
     */
    protected int degre;

    /**
     * Définition des couleurs AMBREE
     */
    public static int AMBREE = 1;

    /**
     * Définition des couleurs BLONDE
     */
    public static int BLONDE = 2;

    /**
     * Renvoie le nom de la bière
     * 
     * @return String Le nom de la bière
     */
    public String getNom() {
        return nom;
    }

    /**
     * Renvoie la couleur de la bière
     * 
     * @return int La couleur de la bière
     */
    public int getCouleur() {
        return couleur;
    }

    /**
     * Renvoie le degré de la bière
     * 
     * @return int Le degré de la bière
     */
    public int getDegre() {
        return degre;
    }

    /**
     * Définition d'une bière
     * 
     * @param nom     Le nom de la bière
     * @param couleur La couleur de la bière
     * @param degre   Le degré de la bière
     */
    public Biere(String nom, int couleur, int degre) {
        this.nom = nom;
        this.couleur = couleur;
        this.degre = degre;
    }

    /**
     * Convertit la couleur de la bière en une chaîne de caractères
     * 
     * @return String La représentation en chaîne de caractères de la bière
     */
    public String toString() {
        String coul = "couleur inconnue";
        if (couleur == Biere.AMBREE)
            coul = "ambree";
        if (couleur == Biere.BLONDE)
            coul = "blonde";
        return nom + ", " + coul + ", " + degre + "°";
    }
}