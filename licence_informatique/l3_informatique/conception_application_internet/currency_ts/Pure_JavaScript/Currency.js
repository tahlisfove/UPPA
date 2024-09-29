class Obsolete_currency {

    static Default_substitute() {
        return new Euro();
    }

    substitute() {
        return Obsolete_currency.Default_substitute();
    }

    still_active_() {
        return false;
    }

    substitution_date() {
        throw new TypeError("abstract");
    }
}

class Currency {
    constructor(common_symbol, iso_code, iso_symbol) {
// Exemple du dollar américain :
        this._common_symbol = common_symbol; // $
        this._iso_code = iso_code; // 840
        this._iso_symbol = iso_symbol; // USD
    }

    rate(currency) {
        return 1. / currency.to_euro_rate();
    }

    to_dollar_rate() {
        throw new TypeError("abstract");
    }

    convert_to_dollar(amount) {
        return amount * this.to_dollar_rate();
    }

    to_euro_rate() {
        throw new TypeError("abstract");
    }

    convert_to_euro(amount) {
        return amount * this.to_euro_rate();
    }
}

class Euro extends Currency {

    constructor() {
        super("€", 978, "EUR");
    }

    to_dollar_rate() {
        return 1.1; // Taux pris le 17 sept. 2019
    }

    to_euro_rate() {
        return 1.;
    }
}

class Lats extends Currency { // Monnaie de la Lettonie remplacée par l'Euro le 1er janvier 2014 

    static Substitution_date() {
        return Date.parse('01 Jan 2014 00:00:00 GMT');
    }

    constructor(obsolete_currency = new Obsolete_currency) { // There is *NO* multiple class/interface inheritance/implementation in JavaScript!
        super("Ls", 428, "LVL");
        this._obsolete_currency = obsolete_currency;
    }

    to_dollar_rate() {
        const substitute = this._obsolete_currency.substitute();
        return this.rate(substitute) * substitute.to_dollar_rate();
    }

    to_euro_rate() {
        return 1. / 0.702804; // Taux pris le 1er janvier 2014
    }

    substitution_date() {
        return Lats.Substitution_date().toString();
    }
}

const lats = new Lats();
console.log(lats.convert_to_euro(100));
console.log(lats.convert_to_dollar(100));
