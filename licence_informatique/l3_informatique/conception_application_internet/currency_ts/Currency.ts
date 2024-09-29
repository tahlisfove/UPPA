import Currency_ISO_symbols, {Currency_conversion} from "./Currency_conversion";

interface Obsolete_currency {
    still_active_(): boolean;

    substitute(): Currency;

    substitution_date(): string;
}

abstract class Currency {
    public readonly iso_symbol: Currency_ISO_symbols;

    public constructor(private readonly _common_symbol: string, private readonly _iso_code: number, readonly iso_symbol_: Currency_ISO_symbols) {
        // Exemple du dollar américain : $, 840, USD
        this.iso_symbol = iso_symbol_;
    }

    public rate(currency: Currency): number {
        return 1. / currency.to_euro_rate();
    }

    public abstract to_dollar_rate(): Promise<number>;

    // public convert_to_dollar(amount: number): number {
    //     return amount * this.to_dollar_rate();
    // }

    public abstract to_euro_rate(): number;

    public convert_to_euro(amount: number): number {
        return amount * this.to_euro_rate();
    }
}

class Euro extends Currency {

    constructor() {
        super("€", 978, Currency_ISO_symbols.Euro);
    }

    async to_dollar_rate(): Promise<number> {
        /**
         * Get rate at https://fixer.io or https://openexchangerates.org
         * instead of frozen value...
         */
        return await Currency_conversion.Convert(this.iso_symbol);
    }

    to_euro_rate(): number {
        return 1.;
    }
}

class Lats extends Currency implements Obsolete_currency { // Monnaie de la Lettonie remplacée par l'Euro le 1er janvier 2014
    public still_active_(): boolean {
        return false;
    }

    private static _Substitute: Currency = new Euro();
    private static _Substitution_date: number = Date.parse('01 Jan 2014 00:00:00 GMT');

    public substitute(): Currency {
        return Lats._Substitute;
    }

    public substitution_date(): string {
        return Lats._Substitution_date.toString();
    }

    constructor() {
        super("Ls", 428, Currency_ISO_symbols.Lats);
    }

    async to_dollar_rate(): Promise<number> {
        /**
         * Get rate at https://fixer.io or https://openexchangerates.org
         * instead of frozen value...
         */
        const rate = await Currency_conversion.Convert(this.substitute().iso_symbol);
        return rate * this.to_euro_rate();
    }

    to_euro_rate(): number {
        return 1. / 0.702804; // Fixed rate from Jan. 1, 2014
    }
}

window.document.onreadystatechange = function () {
    if (window.document.readyState !== "loading") {
        (new Lats).to_dollar_rate().then(rate => window.alert(Currency_ISO_symbols.Lats + ": " + rate + Currency_ISO_symbols.Dollar));
        (new Euro).to_dollar_rate().then(rate => window.alert(Currency_ISO_symbols.Euro + ": " + rate + Currency_ISO_symbols.Dollar));
    }
};


