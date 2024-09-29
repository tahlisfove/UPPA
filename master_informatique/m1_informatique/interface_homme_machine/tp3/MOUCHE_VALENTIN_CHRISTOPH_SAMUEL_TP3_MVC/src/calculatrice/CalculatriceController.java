package calculatrice;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.text.Text;

public class CalculatriceController {

    @FXML
    private Text displayText;
    private String currentOperator = "";
    private float currentNumber = 0;
    private boolean newCalculation = true;

    @FXML
    private void processNumpad(ActionEvent event) {
        Button clickedButton = (Button) event.getSource();
        String buttonText = clickedButton.getText();

        if (newCalculation) {
            displayText.setText(buttonText);
            newCalculation = false;
        } else {
            displayText.setText(displayText.getText() + buttonText);
        }
    }

    @FXML
    private void processOperator(ActionEvent event) {
        Button clickedButton = (Button) event.getSource();
        String operator = clickedButton.getText();

        if (!operator.equals("=")) {
            currentOperator = operator;
            currentNumber = Float.parseFloat(displayText.getText());
            newCalculation = true;
            displayText.setText("");
        } else {
            float secondNumber = Float.parseFloat(displayText.getText());
            float result = CalculatriceModele.calculate(currentNumber, secondNumber, currentOperator);
            displayText.setText(String.valueOf(result));
            newCalculation = true;
        }
    }
}