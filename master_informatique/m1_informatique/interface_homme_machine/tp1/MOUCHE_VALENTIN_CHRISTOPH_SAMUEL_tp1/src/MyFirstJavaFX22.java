import javafx.application.Application;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class MyFirstJavaFX22 extends Application {

	public void start(Stage primaryStage) throws Exception {

        int nbColonne = 4;

        VBox vbox = new VBox();

        GridPane gridpaneA = new GridPane();
        GridPane gridpaneB = new GridPane();
        GridPane gridpaneR = new GridPane();

        for (int i=0; i<nbColonne; i++) {
            gridpaneA.add(new TextField("0"), i, 2); // Vector A
            gridpaneB.add(new TextField("0"), i, 4); // Vector B
            gridpaneR.add(new TextField("0"), i, 7); // Result
        }

        Label labelA = new Label("Vector A");
        labelA.setPrefWidth(80);
        Label labelB = new Label("Vector B");
        labelB.setPrefWidth(80);
        Label labelAB = new Label("A+B");
        Button buttonA = new Button("Calculer");

        buttonA.setOnAction( e -> {
        	for (int i=0; i<nbColonne; i++) {
        		TextField vectorA = (TextField) gridpaneA.getChildren().get(i);
                TextField vectorB = (TextField) gridpaneB.getChildren().get(i);
                TextField resultField = (TextField) gridpaneR.getChildren().get(i);

                float resA, resB;
                resA = Float.parseFloat(vectorA.getText());
                resB = Float.parseFloat(vectorB.getText());

                float sum = resA + resB;
                resultField.setText(String.valueOf(sum));
        	}
        });

        vbox.getChildren().addAll(labelA, gridpaneA, labelB, gridpaneB, buttonA, labelAB, gridpaneR);
        Scene scene = new Scene(vbox, 350, 250);

        primaryStage.setTitle("My first java app");
        primaryStage.setScene(scene);
        primaryStage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}