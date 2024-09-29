package simulateur;

import java.time.LocalDate;

import javafx.scene.control.Alert;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;

public class SimulateurModele {

	public boolean SalaireMin(TextField salaire){
        float inputValue = Float.parseFloat(salaire.getText());
		if (inputValue<2000){
			Alert alert = new Alert(Alert.AlertType.WARNING);
	        alert.setTitle("Prêt impossible");
	        alert.setHeaderText(null);
	        alert.setContentText("Salaire inférieur à 2000€ par mois");
	        alert.show();
		return false;
		}else{
			return true;
		}
	}

	public boolean Verif_Age(DatePicker dateP){
		LocalDate date = dateP.getValue();
		Alert alert = new Alert(Alert.AlertType.WARNING);
		if(2023-date.getYear()<18){
	        alert.setTitle("Âge non valable");
	        alert.setHeaderText(null);
	        alert.setContentText("Age inférieur à 18ans");
	        alert.show();
	        return false;
		}else{
			if(2023-date.getYear()>61){
		        alert.setTitle("Âge non valable");
		        alert.setHeaderText(null);
		        alert.setContentText("Age supérieur à 62ans");
		        alert.show();
		        return false;
			}else{
				return true;
			}
		}
	}

	public float d_max(int annee)
	{
		int age = 2023 - annee;
		float dmax;
		dmax = (62 - age) * 12;
		return dmax;
	}

	public double c_max(float dmax,float salaire)
	{
		double cmax = dmax * 0.3 * salaire;
		return cmax;
	}

	public double montant_max(double cmax, float dmax)
	{
		double montantmax = (cmax/dmax);
		return montantmax;
	}
}