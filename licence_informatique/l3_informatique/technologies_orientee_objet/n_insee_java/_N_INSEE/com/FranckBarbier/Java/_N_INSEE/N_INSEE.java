package com.FranckBarbier.Java._N_INSEE;

public class N_INSEE {

    private static final java.util.regex.Pattern _Pattern = java.util.regex.Pattern.compile("^\\d{13}$"); // "^[1-2]\\d{12}$"
    private long _valeur = 0L;

    public N_INSEE(String valeur) {
//        _controle(valeur); // Contrôle "classique"
        _controle_(valeur);
        // Conversion from 'String' to 'long'
        _valeur = Long.decode(valeur);
    }

    public long clef() {
        return 97L - _valeur % 97L;
    }

    private void _controle(String valeur) {
        if (valeur.length() != 13) {
            throw new RuntimeException("N°INSEE non défini sur 13 chiffres");
        }
        if (!valeur.startsWith("1") && !valeur.startsWith("2")) {
            throw new RuntimeException("N°INSEE doit débuter par '1' ou '2'");
        }
// Etc.
    }

    private void _controle_(String valeur) {
        if (!_Pattern.matcher(valeur).matches()) {
            throw new RuntimeException("N°INSEE ne respecte pas le format : " + _Pattern);
        }
    }
}
