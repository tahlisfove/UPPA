package convertisseur;

import javafx.scene.control.ComboBox;

public class ConvertisseurModele {

    public float performDeviseConversion(float inputValue, ComboBox<String> from, ComboBox<String> to) {
        String fromCurrency = from.getValue();
        String toCurrency = to.getValue();

        if (fromCurrency == null || toCurrency == null) {
            return 0;
        }

        float result;
        if (fromCurrency.equals("Euros") && toCurrency.equals("Dollars")) {
            result = (float) (inputValue * 1.08);
        } else if (fromCurrency.equals("Dollars") && toCurrency.equals("Euros")) {
            result = (float) (inputValue * 0.93);
        } else {
            return 0;
        }

        return result;
    }

    public float performMesureConversion(float inputValue, ComboBox<String> from, ComboBox<String> to) {
        String fromMeasure = from.getValue();
        String toMeasure = to.getValue();

        if (fromMeasure == null || toMeasure == null) {
            return 0;
        }

        float result;
        if (fromMeasure.equals("Mètres") && toMeasure.equals("Verges")) {
            result = (float) (inputValue * 1.094);
        } else if (fromMeasure.equals("Verges") && toMeasure.equals("Mètres")) {
            result = (float) (inputValue * 0.9144);
        } else {
            return 0;
        }

        return result;
    }

    public float performTemperatureConversion(float inputValue, ComboBox<String> from, ComboBox<String> to) {
        String fromUnit = from.getValue();
        String toUnit = to.getValue();

        if (fromUnit == null || toUnit == null) {
            return 0;
        }

        float result;
        if (fromUnit.equals("Celsius") && toUnit.equals("Fahrenheit")) {
            result = (inputValue * 9 / 5) + 32;
        } else if (fromUnit.equals("Fahrenheit") && toUnit.equals("Celsius")) {
            result = (inputValue - 32) * 5 / 9;
        } else {
            return 0;
        }

        return result;
    }
}