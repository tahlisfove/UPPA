package calculatrice;

public class CalculatriceModele {

	public static float calculate(float num1, float num2, String operator) {
        switch (operator) {
            case "+":
                return num1 + num2;
            case "-":
                return num1 - num2;
            case "*":
                return num1 * num2;
            case "/":
                if (num2 != 0) {
                    return num1 / num2;
                } else {
                    System.err.println("Error: Division by zero.");
                    return Float.NaN;
                }
            default:
                System.err.println("Error: Invalid operator.");
                return Float.NaN;
        }
	}
}