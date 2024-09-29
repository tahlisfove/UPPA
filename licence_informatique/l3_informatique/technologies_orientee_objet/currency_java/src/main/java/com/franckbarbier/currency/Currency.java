package com.franckbarbier.currency;

interface Obsolete_currency {

    Currency Default_substitute = new Euro();

    default Currency substitute() {
        return Default_substitute;
    }

    default boolean still_active_() {
        return false;
    }

    java.time.LocalDate substitution_date();
}

abstract public class Currency {

    protected final String _common_symbol; // $
    protected final int _iso_code; // 840
    protected final String _iso_symbol; // USD

    protected Currency(String common_symbol, int iso_code, String iso_symbol) {
        _common_symbol = common_symbol;
        _iso_code = iso_code;
        _iso_symbol = iso_symbol;
    }

    public double rate(Currency currency) {
        return 1.D / currency.to_euro_rate();
    }

    abstract public double to_dollar_rate();

    public double convert_to_dollar(final double amount) {
        return amount * to_dollar_rate();
    }

    abstract public double to_euro_rate();

    public double convert_to_euro(final double amount) {
        return amount * to_euro_rate();
    }

}
