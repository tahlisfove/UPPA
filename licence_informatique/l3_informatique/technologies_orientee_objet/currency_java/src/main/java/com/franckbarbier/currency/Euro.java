package com.franckbarbier.currency;

public class Euro extends Currency {

    Euro() {
        super("€", 978, "EUR");
    }

    @Override
    public double to_dollar_rate() {
        return 1.D / 1.03D; // Oct. 17, 2022 exchange rate
    }

    @Override
    public double to_euro_rate() {
        return 1.D;
    }
}
