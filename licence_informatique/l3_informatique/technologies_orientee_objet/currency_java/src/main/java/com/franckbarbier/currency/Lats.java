package com.franckbarbier.currency;

public class Lats extends Currency implements Obsolete_currency { /** Letonia currency replaced by Euro January, 1st 2014 **/

    private static final java.time.LocalDate _Substitution_date = java.time.LocalDate.of(2014, java.time.Month.JANUARY, 1);

    Lats() {
        super("Ls", 428, "LVL");
    }

    @Override
    public double to_dollar_rate() {
        Currency substitute = substitute();
        return rate(this) * substitute.to_dollar_rate();
    }

    @Override
    public double to_euro_rate() {
        return 1.D * 0.702804D; // Jan. 1, 2014 exchange rate
    }

    public java.time.LocalDate substitution_date() {
        return _Substitution_date;
    }
}
