package com.FranckBarbier.Java._N_INSEE;

public class Application {

    public static void main(String[] args) {
        N_INSEE n_insee = new N_INSEE("1630125388055");
        System.out.println("Clef de 1630125388055 est égale à " + n_insee.clef()); // '29' est affiché
    }
}
