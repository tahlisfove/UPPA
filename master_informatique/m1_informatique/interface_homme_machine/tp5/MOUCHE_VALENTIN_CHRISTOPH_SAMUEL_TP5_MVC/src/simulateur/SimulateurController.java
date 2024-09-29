package simulateur;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.function.UnaryOperator;
import java.util.regex.Pattern;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import simulateur.SimulateurModele;

public class SimulateurController {
    SimulateurModele model = new SimulateurModele();

    @FXML
    private Label label_duree;

    @FXML
    private Label label_mensualite;

    @FXML
    private Label label_pret;

    @FXML
    private Slider slider1, slider2;

    @FXML
    private VBox VboxVisible;

    @FXML
    private HBox hb1;

    @FXML
    private StackPane Vboxid;

    @FXML
    private Button button_calculer;

    @FXML
    private Button btn_retour;

    @FXML
    private Button button_deposer;

    @FXML
    private TextField TextField_nom;

    @FXML
    private TextField TextField_code;

    @FXML
    private ChoiceBox<String> ChoiceBox_ville;

    @FXML
    private TextField TextField_prenom;

    @FXML
    private DatePicker DatePicker_age;

    @FXML
    private TextField TextField_salaire;

    private List<String> villes = new ArrayList<>();

    {
        villes.addAll(FXCollections.observableArrayList("Billère", "Idron", "Jurançon", "Lescar", "Lons", "Pau"));
    }

    @FXML
    private void initialize() {
        VboxVisible.setDisable(true);
        btn_retour.setDisable(true);

        TextField_salaire.addEventHandler(KeyEvent.KEY_PRESSED, event -> {
            if (event.getCode() == KeyCode.ENTER) {
                Calculer();
            }
        });

        button_deposer.addEventHandler(KeyEvent.KEY_PRESSED, event -> {
            if (event.getCode() == KeyCode.ENTER) {
                demanderConfirmationDepotProjet();
            }
        });

        UnaryOperator<TextFormatter.Change> filter09 = change -> {
            String newText = change.getControlNewText();
            if (newText.matches("\\d{0,5}")) {
                return change;
            }
            return null;
        };

        TextFormatter<String> textFormatter09 = new TextFormatter<>(filter09);

        TextField_code.setTextFormatter(textFormatter09);
        ChoiceBox_ville.setItems(FXCollections.observableArrayList(villes));

        UnaryOperator<TextFormatter.Change> filter = change -> {
            String text = change.getText();
            return Pattern.matches("[0-9]*\\.?[0-9]*", text) || text.isEmpty() ? change : null;
        };

        TextFormatter<String> textFormatter08 = new TextFormatter<>(filter);
        TextField_salaire.setTextFormatter(textFormatter08);

        UnaryOperator<TextFormatter.Change> filterAZ = change -> {
            String text = change.getText();
            return (text.matches("[a-zA-Z]*") || text.isEmpty()) ? change : null;
        };

        TextFormatter<String> textFormatterAZ = new TextFormatter<>(filterAZ);
        TextFormatter<String> textFormatterAY = new TextFormatter<>(filterAZ);
        TextField_nom.setTextFormatter(textFormatterAZ);
        TextField_prenom.setTextFormatter(textFormatterAY);

        button_deposer.setOnAction(event -> {
            demanderConfirmationDepotProjet();
        });
    }

    @FXML
    public void Calculer() {
        if (saisieValide()) {
            if (model.Verif_Age(DatePicker_age) && model.SalaireMin(TextField_salaire)) {
                setSlider();
                VboxVisible.setDisable(false);
                hb1.setDisable(true);

                updateDureeAndLabelPret();
                updateMensualiteAndLabelPret();
                updateLabelPret();
                btn_retour.setDisable(false);
                button_calculer.setDisable(true);
            }
        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erreur");
            alert.setHeaderText(null);
            alert.setContentText("Veuillez remplir tous les champs.");
            alert.show();
        }
    }

    @FXML
    public void btn_retour() {
        setSlider();
        button_calculer.setDisable(false);
        btn_retour.setDisable(true);
        label_mensualite.setText("");
        label_duree.setText("");
        label_pret.setText("");
        hb1.setDisable(false);
        VboxVisible.setDisable(true);
    }

    private void updateDureeAndLabelPret() {
        float dmax = model.d_max(DatePicker_age.getValue().getYear());
        double cmax = model.c_max(dmax, Float.parseFloat(TextField_salaire.getText()));
        double montant_max = model.montant_max(cmax, dmax);

        int duree = (int) slider1.getValue();
        double mensualite = slider2.getValue();

        label_duree.setText(duree + " mois");
        montant_max = duree * mensualite;
        label_pret.setText(String.format("%.2f", montant_max) + " €");
    }

    private void setSlider() {

        float dmax = model.d_max(DatePicker_age.getValue().getYear());
        double cmax = model.c_max(dmax, Float.parseFloat(TextField_salaire.getText()));
        double montant_max = model.montant_max(cmax, dmax);

        slider1.setMin(1);
        slider1.setMax(model.d_max(DatePicker_age.getValue().getYear()));
        slider1.setValue(model.d_max(DatePicker_age.getValue().getYear()));
        slider1.valueProperty().addListener((observable, oldValue, newValue) -> {
            updateDureeAndLabelPret();
        });

        slider2.setMin(1);
        slider2.setMax(montant_max);
        slider2.setValue(montant_max);
        slider2.valueProperty().addListener((observable, oldValue, newValue) -> {
            updateMensualiteAndLabelPret();
        });
    }

    private void updateMensualiteAndLabelPret() {
        double mensualite = slider2.getValue();
        label_mensualite.setText(String.format("%.2f", mensualite) + " €");
        updateLabelPret();
    }

    private void updateLabelPret() {
        float dmax = model.d_max(DatePicker_age.getValue().getYear());
        double cmax = model.c_max(dmax, Float.parseFloat(TextField_salaire.getText()));
        double montant_max = model.montant_max(cmax, dmax);

        int duree = (int) slider1.getValue();
        double mensualite = slider2.getValue();
        montant_max = duree * mensualite;

        label_pret.setText(String.format("%.2f", montant_max) + " €");
    }

    private void demanderConfirmationDepotProjet() {
        Alert confirmation = new Alert(Alert.AlertType.CONFIRMATION);
        confirmation.setTitle("Confirmation");
        confirmation.setHeaderText(null);
        confirmation.setContentText("Voulez-vous vraiment déposer votre demande de prêt ?");

        ButtonType buttonTypeOui = new ButtonType("Oui");
        ButtonType buttonTypeNon = new ButtonType("Non");
        confirmation.getButtonTypes().setAll(buttonTypeOui, buttonTypeNon);

        confirmation.showAndWait().ifPresent(buttonType -> {
            if (buttonType == buttonTypeOui) {
                setSlider();
                hb1.setDisable(false);
                VboxVisible.setDisable(true);
                TextField_nom.clear();
                TextField_prenom.clear();
                DatePicker_age.setValue(null);
                TextField_code.clear();
                ChoiceBox_ville.setValue(null);
                TextField_salaire.clear();
                label_mensualite.setText("");
                label_duree.setText("");
                label_pret.setText("");
                btn_retour.setDisable(true);
                button_calculer.setDisable(false);
            }
        });
    }

    private boolean saisieValide() {
        String nom = TextField_nom.getText();
        String prenom = TextField_prenom.getText();
        LocalDate age = DatePicker_age.getValue();
        String codePostal = TextField_code.getText();
        String salaire = TextField_salaire.getText();
        String ville = ChoiceBox_ville.getValue();

        return !nom.isEmpty() && !prenom.isEmpty() && age != null && !codePostal.isEmpty() && !salaire.isEmpty()
                && ville != null;
    }
}