package perimetre;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.text.Font;

public class PerimetreController {

	private PerimetreModele modele;

	@FXML
	private TextField textLargeur;

	@FXML
	private TextField textLongueur;

	@FXML
	private Label valResultat;

    @FXML
    private Font FONT;

	public PerimetreController() {
		this.modele = new PerimetreModele();
	}

    @FXML
    private void buttonCalculer(ActionEvent event) {
   	 	if (!textLargeur.getText().isEmpty() && !textLongueur.getText().isEmpty() && textLargeur.getText().matches("\\d*") && textLongueur.getText().matches("\\d*")) {
	        float largeur = Float.parseFloat(textLargeur.getText());
	        float longueur = Float.parseFloat(textLongueur.getText());
	        float resultat = modele.calculPerimetre(largeur, longueur);

	        valResultat.setText(String.valueOf(resultat));
   	 	} else {
   	 		valResultat.setText("entrée fausse");
        }
    }

    @FXML
    private void buttonNettoyer(ActionEvent event) {
    	textLargeur.setText("");
    	textLongueur.setText("");
    	valResultat.setText("0.0");
    }
}