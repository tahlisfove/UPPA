package com.franckbarbier.currency;

public class Bitcoin extends Crypto_currency {

    public Bitcoin() {
        super("BTC", -1, "XBT");
    }

    @Override
    public double to_dollar_rate() {
        // Le calcul est faux car, en réalité, on ne passe pas par le taux de change intermédiaire :
        return to_euro_rate() * (new Euro()).to_dollar_rate();
    }

    @Override
    public double to_euro_rate() {
        return 19993.23D; // Oct. 17, 2022 exchange rate
    }
}
