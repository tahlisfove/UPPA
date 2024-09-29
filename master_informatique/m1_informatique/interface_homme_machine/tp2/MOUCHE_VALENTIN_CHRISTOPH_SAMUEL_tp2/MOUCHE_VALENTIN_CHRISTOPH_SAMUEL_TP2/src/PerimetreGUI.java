import javafx.application.Application;
import javafx.geometry.HPos;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;

public class PerimetreGUI extends Application {

	@Override
	public void start(Stage primaryStage) {

		GridPane gridPane = new GridPane();

        Label label1 = new Label("Longueur:");
        Label label2 = new Label("Largeur:");
        Label label3 = new Label("Résultat:");
        Button button1 = new Button("Calculer");

        TextField textField1 = new TextField("");
        TextField textField2 = new TextField("");
        Label label4 = new Label("0.0");
        Button button2 = new Button("Nettoyer");

        label1.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        label2.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        label3.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        label4.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        button1.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        button2.setFont(Font.font("Arial", FontWeight.BOLD, 15));

        gridPane.add(label1, 0, 0);
        gridPane.add(label2, 0, 1);
        gridPane.add(label3, 0, 2);
        gridPane.add(button1, 0, 3);

        gridPane.add(textField1, 1, 0);
        gridPane.add(textField2, 1, 1);
        gridPane.add(label4, 1, 2);
        gridPane.add(button2, 1, 3);

        gridPane.setAlignment(javafx.geometry.Pos.CENTER);
        gridPane.setHgap(5);
        gridPane.setVgap(5);

        GridPane.setHalignment(label1, HPos.CENTER);
        GridPane.setHalignment(label2, HPos.CENTER);
        GridPane.setHalignment(label3, HPos.CENTER);
        GridPane.setHalignment(label4, HPos.CENTER);
        GridPane.setHalignment(textField1, HPos.CENTER);
        GridPane.setHalignment(textField2, HPos.CENTER);
        GridPane.setHalignment(button1, HPos.CENTER);
        GridPane.setHalignment(button2, HPos.CENTER);

        button1.setOnAction( e -> {
        	 if (!textField1.getText().isEmpty() && !textField2.getText().isEmpty() && textField1.getText().matches("\\d*") && textField2.getText().matches("\\d*")) {

                 float longueur = Float.parseFloat(textField1.getText());
                 float largeur = Float.parseFloat(textField2.getText());
                 String perimetre = String.valueOf(2 * (longueur + largeur));
                 label4.setText(perimetre);
             } else {
                 label4.setText("entrée fausse");
             }
         });

        button2.setOnAction( e -> {
        	textField1.setText("");
        	textField2.setText("");
            label4.setText("0.0");
        });

        Scene scene = new Scene(gridPane, 350, 150);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Calcul Périmètre d’un rectangle");
        primaryStage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}