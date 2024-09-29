package com.franckbarbier.bar_code;

enum Result {
    Correct,
    Incorrect,
    Invalid_format
}

public class Bar_code {

    private final java.util.ArrayList<Integer> _bar_code = new java.util.ArrayList<>();
    public final Result correct;

    Bar_code(final String bar_code) throws NumberFormatException {
        for (String s : bar_code.split("")) { // 'bar_code' est découpé en éléments...
            try {
                int element = Integer.valueOf(s); // Conversion en entier pour les calculs...
                _bar_code.add(element);
            } catch (NumberFormatException nfe) {
                correct = Result.Invalid_format;
                throw nfe;
            }
        }
        correct = _check_sum() ? Result.Correct : Result.Incorrect;
    }

    private boolean _check_sum() { // Méthode de calcul du "check sum" :
        // https://barcode-coder.com/fr/specification-ean-13-102.html
        // Example: 2 1 0 9 8 7 6 5 4 3 2 1 0
        // Step 1: ajouter les chiffres de rang impair en partant de la droite (ne pas compter le dernier chiffre de contrôle, i.e., '0')
        // Step 2: ajouter au résultat trois fois la somme des chiffres de rang pair toujours en partant de la droite
        // Check sum: (10 - [ (3 * "impairs" + "pairs") modulo 10 ]) modulo 10
        return true; // A remplacer
    }

    private boolean _alternative_check_sum() { // Autre méthode de calcul du "check sum" :
        // Autre méthode : https://fr.wikipedia.org/wiki/EAN_13
        return true; // A remplacer
    }

    @Override
    public String toString() {
        return ""; // A remplacer
    }
}
