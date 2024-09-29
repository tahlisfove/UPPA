package convertisseur;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.function.UnaryOperator;
import java.util.regex.Pattern;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.control.ButtonType;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;

public class ConvertisseurController {

    ConvertisseurModele model = new ConvertisseurModele();

    @FXML
    private RadioButton deviseRadioButton, mesureRadioButton, temperatureRadioButton;

    @FXML
    private ComboBox<String> fromComboBox, toComboBox;

    @FXML
    private TextField inputTextField, resultTextField;

    @FXML
    private CheckBox negativeCheckBox;

    @FXML
    private ToggleGroup toggleGroup;

    private List<String> temperaturesList = new ArrayList<String>();
    private List<String> devisesList = new ArrayList<>();
    private List<String> mesuresList = new ArrayList<>();

    {
        devisesList.addAll(FXCollections.observableArrayList("Euros", "Dollars"));
        mesuresList.addAll(FXCollections.observableArrayList("Mètres", "Verges"));
        temperaturesList.addAll(FXCollections.observableArrayList("Celsius", "Fahrenheit"));
    }

    @FXML
    private void initialize() {
        ToggleGroup toggleGroup = new ToggleGroup();
        deviseRadioButton.setToggleGroup(toggleGroup);
        mesureRadioButton.setToggleGroup(toggleGroup);
        temperatureRadioButton.setToggleGroup(toggleGroup);

        updateComboBoxes(deviseRadioButton);

        inputTextField.addEventHandler(KeyEvent.KEY_PRESSED, event -> {
            if (event.getCode() == KeyCode.ENTER) {
                handleConversion();
            }
        });

        toggleGroup.selectedToggleProperty().addListener((ObservableValue<? extends Toggle> observable, Toggle oldValue, Toggle newValue) -> {
            if (newValue != null) {
                RadioButton selectedRadioButton = (RadioButton) newValue.getToggleGroup().getSelectedToggle();
                updateComboBoxes(selectedRadioButton);
                negativeCheckBox.setDisable(!temperatureRadioButton.isSelected());
            }
        });

        UnaryOperator<TextFormatter.Change> filter = change -> {
            String text = change.getText();
            return Pattern.matches("[0-9]*\\.?[0-9]*", text) || text.isEmpty() ? change : null;
        };

        TextFormatter<String> textFormatter = new TextFormatter<>(filter);
        inputTextField.setTextFormatter(textFormatter);

        fromComboBox.valueProperty().addListener((ObservableValue<? extends String> observable, String oldValue, String newValue) -> {
            updateToComboBox();
        });
    }

    @FXML
    private void Checkbox() {
        resultTextField.setStyle("-fx-text-fill: " + (negativeCheckBox.isSelected() ? "red" : "green") + ";");
        inputTextField.setStyle("-fx-text-fill: " + (negativeCheckBox.isSelected() ? "red" : "green") + ";");
    }

    @FXML
    private void handleConversion() {
        String input = inputTextField.getText().trim();
        if (input.isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Avertissement");
            alert.setHeaderText(null);
            alert.setContentText("Erreur saisie");
            alert.show();
            return;
        } else {
            float inputValue = Float.parseFloat(inputTextField.getText());
            if (negativeCheckBox.isSelected()) {
                inputValue = 0 - inputValue;
            }

            float result = 0;
            if (deviseRadioButton.isSelected()) {
                result = model.performDeviseConversion(inputValue, fromComboBox, toComboBox);
            } else if (mesureRadioButton.isSelected()) {
                result = model.performMesureConversion(inputValue, fromComboBox, toComboBox);
            } else if (temperatureRadioButton.isSelected()) {
                result = model.performTemperatureConversion(inputValue, fromComboBox, toComboBox);
            }

            resultTextField.setText(Float.toString(result));
        }
    }

    private void updateComboBoxes(RadioButton radioButton) {
        fromComboBox.getItems().clear();
        toComboBox.getItems().clear();

        inputTextField.clear();
        resultTextField.clear();
        resultTextField.setStyle("-fx-text-fill:black;");
        inputTextField.setStyle("-fx-text-fill:black;");

        if (radioButton == deviseRadioButton) {
            negativeCheckBox.setSelected(false);
            fromComboBox.setItems(FXCollections.observableArrayList(devisesList));
            toComboBox.setItems(FXCollections.observableArrayList(devisesList));
        } else if (radioButton == mesureRadioButton) {
            negativeCheckBox.setSelected(false);
            fromComboBox.setItems(FXCollections.observableArrayList(mesuresList));
            toComboBox.setItems(FXCollections.observableArrayList(mesuresList));
        } else if (radioButton == temperatureRadioButton) {
            resultTextField.setStyle("-fx-text-fill: " + (negativeCheckBox.isSelected() ? "red" : "green") + ";");
            inputTextField.setStyle("-fx-text-fill: " + (negativeCheckBox.isSelected() ? "red" : "green") + ";");
            fromComboBox.setItems(FXCollections.observableArrayList(temperaturesList));
            toComboBox.setItems(FXCollections.observableArrayList(temperaturesList));
        }

        fromComboBox.getSelectionModel().selectFirst();
        toComboBox.getSelectionModel().selectLast();

        updateToComboBox();
    }

    private void updateToComboBox() {
        if (deviseRadioButton.isSelected()) {
            toComboBox.setItems(FXCollections.observableArrayList(devisesList));
        } else if (mesureRadioButton.isSelected()) {
            toComboBox.setItems(FXCollections.observableArrayList(mesuresList));
        } else if (temperatureRadioButton.isSelected()) {
            toComboBox.setItems(FXCollections.observableArrayList(temperaturesList));
        }

        String selectedValue = fromComboBox.getSelectionModel().getSelectedItem();
        if (selectedValue != null) {
            ObservableList<String> filteredItems = toComboBox.getItems().filtered(item -> !item.equalsIgnoreCase(selectedValue));
            toComboBox.setItems(filteredItems);
            toComboBox.getSelectionModel().selectLast();
        }
    }

    @FXML
    private void handleQuitButton(ActionEvent event) {
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setTitle("Avertissement");
        alert.setHeaderText(null);
        alert.setContentText("Voulez-vous vraiment quitter ?");

        ButtonType buttonTypeOK = new ButtonType("OK", ButtonData.OK_DONE);
        ButtonType buttonTypeCancel = new ButtonType("Annuler", ButtonData.CANCEL_CLOSE);

        alert.getButtonTypes().setAll(buttonTypeOK, buttonTypeCancel);

        Optional<ButtonType> result = alert.showAndWait();

        if (result.isPresent() && result.get() == buttonTypeOK) {
            Stage stage = (Stage) ((Button) event.getSource()).getScene().getWindow();
            stage.close();
        }
    }
}
