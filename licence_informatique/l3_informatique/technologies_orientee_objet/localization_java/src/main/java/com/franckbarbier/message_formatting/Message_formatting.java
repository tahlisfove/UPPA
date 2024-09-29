package com.franckbarbier.message_formatting;

public class Message_formatting {

    public static void main(String[] args) {
        // 'resources/texte_fr.properties' is in the 'classpath':
        java.util.ResourceBundle bundle = java.util.ResourceBundle.getBundle("texte", java.util.Locale.FRANCE);
        // Set project encoding to 'UTF-16' to get French accents:
        System.out.println(bundle.getString("texte"));
        // 'Ce tutoriel traite des problèmes d'internationalisation en Java.'

        java.util.Currency EURO = java.util.Currency.getInstance(java.util.Locale.FRANCE);
        java.util.Currency US_DOLLAR = java.util.Currency.getInstance(java.util.Locale.US);
        System.out.println(String.format(java.util.Locale.US, "On %s, change from %s to %s is %f.", java.time.LocalDate.now(), EURO, US_DOLLAR, 0.986));
        // 'On 2022-10-06, change from EUR to USD is 0.986000.'

        System.out.println(java.util.Currency.getInstance(java.util.Locale.US).getSymbol(java.util.Locale.FRANCE));
        // '$US'

        java.text.MessageFormat message_format = new java.text.MessageFormat("On {0}, change from {1} to {2} is {3,number,percent}.", java.util.Locale.US);
        System.out.println(message_format.format(new Object[]{java.time.LocalDate.now(), EURO, java.util.Currency.getInstance(java.util.Locale.US).getSymbol(java.util.Locale.FRANCE), 0.986}));
        // 'On 2022-10-06, change from EUR to $US is 99%.'
    }
}
