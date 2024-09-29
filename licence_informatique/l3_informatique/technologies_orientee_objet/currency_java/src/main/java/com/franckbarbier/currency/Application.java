package com.franckbarbier.currency;

public class Application {

    public static void main(String[] args) {
//        Obsolete_currency lats = new Obsolete_currency() {
//            public java.time.LocalDate substitution_date() {
//                return java.time.LocalDate.of(2014, java.time.Month.JANUARY, 1);
//            }
//        };
        Euro euro = (Euro) Lats.Default_substitute;
        Lats lats = new Lats();
        System.out.println("100" + euro._common_symbol + " -> " + lats.convert_to_euro(100) + lats._common_symbol);
        System.out.println("100" + euro._common_symbol + " -> " + euro.convert_to_dollar(100) + "$");
        System.out.println("100" + lats._common_symbol + " -> " + lats.convert_to_dollar(100) + "$");

        Dirham_marocain dirham_marocain = new Dirham_marocain();
        System.out.println("1000" + dirham_marocain._common_symbol + " -> " + dirham_marocain.convert_to_dollar(1000) + "$");
        System.out.println("1000" + dirham_marocain._common_symbol + " -> " + dirham_marocain.convert_to_euro(1000) + euro._common_symbol);

        System.out.println("(new Bitcoin()).to_dollar_rate(): " + (new Bitcoin()).to_dollar_rate());
        System.out.println("(new Bitcoin()).to_euro_rate(): " + (new Bitcoin()).to_euro_rate());
    }
}
