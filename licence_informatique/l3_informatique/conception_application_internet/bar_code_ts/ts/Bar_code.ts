enum Result {
    Correct = "Correct",
    Incorrect = "Incorrect",
    Invalid_format = "Invalid format"
}

export default class Bar_code {
    private readonly _bar_code: Array<number> = new Array;
    private readonly _correct: Result = Result.Invalid_format; // Default value...
    get correct(): Result {
        return this._correct;
    }

    public constructor(bar_code: string) {
        bar_code.split("").forEach((s: string) => { // 'bar_code' est découpé en éléments...
            const element: number = parseInt(s); // Conversion en entier pour les calculs...
            if (isNaN(element)) throw new Error(Result.Invalid_format);
            else this._bar_code.push(element);
        });
        this._correct = this._check_sum() ? Result.Correct : Result.Incorrect;
    }

    private _check_sum(): boolean {
        // https://barcode-coder.com/fr/specification-ean-13-102.html
        // Example: 2 1 0 9 8 7 6 5 4 3 2 1 0
        // Step 1: ajouter les chiffres de rang impair en partant de la droite (ne pas compter le dernier chiffre de contrôle, i.e., '0')
        // Step 2: ajouter au résultat trois fois la somme des chiffres de rang pair toujours en partant de la droite
        // Check sum: (10 - [ (3 * "impairs" + "pairs") modulo 10 ]) modulo 10
        return true; // A remplacer
    }

    private _alternative_check_sum_(): boolean { // Autre méthode de calcul
        // Autre méthode : https://fr.wikipedia.org/wiki/EAN_13
        return true; // A remplacer
    }

    public toString(): string {
        return ""; // A remplacer
    }
}
