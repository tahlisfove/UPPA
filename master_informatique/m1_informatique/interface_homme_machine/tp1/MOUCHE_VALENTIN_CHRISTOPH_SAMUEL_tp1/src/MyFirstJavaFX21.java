import javafx.application.Application;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class MyFirstJavaFX21 extends Application {

	public void start(Stage primaryStage) throws Exception {

        Label label1 = new Label("A + B ");
        label1.setPrefWidth(80);
        Label labelA = new Label("A");
        labelA.setPrefWidth(80);
        Label labelB = new Label("B");
        labelB.setPrefWidth(80);

        TextField champtextA = new TextField();
        champtextA.setPrefWidth(80);
        TextField champtextB = new TextField();
        champtextB.setPrefWidth(80);
        TextField champtextR = new TextField();

        champtextR.setPrefWidth(80);
        Button buttonA = new Button("Calculer");

        buttonA.setOnAction( e -> {
        	float A = Float.parseFloat(champtextA.getText());
            float B = Float.parseFloat(champtextB.getText());
            String res = String.valueOf(A+B);
			champtextR.setText(res);
        });

        GridPane gridpane = new GridPane();
        gridpane.add(labelA, 1, 1);
        gridpane.add(champtextA, 1, 2);
        gridpane.add(labelB, 1, 3);
        gridpane.add(champtextB, 1, 4);
        gridpane.add(buttonA, 1, 5);
        gridpane.add(label1, 1, 6);
        gridpane.add(champtextR, 1, 7);

        Scene scene = new Scene(gridpane, 150, 250);
        primaryStage.setTitle("My first java app");
        primaryStage.setScene(scene);
        primaryStage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}