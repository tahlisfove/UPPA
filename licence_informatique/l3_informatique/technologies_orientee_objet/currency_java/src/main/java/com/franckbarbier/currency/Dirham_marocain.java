package com.franckbarbier.currency;

public class Dirham_marocain extends Currency {

    Dirham_marocain() {
        super("درهم", 504, "MAD");
    }

    @Override
    public double to_dollar_rate() {
        return 1.D * 0.091D; // Oct. 17, 2022 exchange rate
    }

    @Override
    public double to_euro_rate() {
        return to_dollar_rate() * 1 / (new Euro()).to_dollar_rate();
    }
}
