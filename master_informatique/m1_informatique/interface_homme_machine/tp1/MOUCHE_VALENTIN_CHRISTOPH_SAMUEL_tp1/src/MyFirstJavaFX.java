import javafx.application.Application;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class MyFirstJavaFX extends Application {

	public void start(Stage primaryStage) throws Exception {

        HBox hbox = new HBox();

        Label label1 = new Label("Message:");

        TextField champtext = new TextField();
        champtext.resize(60, 10);

        Button buttonA = new Button("Afficher");

        buttonA.setOnAction( e -> {
			champtext.setText("Hello World!");
        });

        hbox.getChildren().addAll(label1, champtext, buttonA);
        Scene scene = new Scene(hbox, 350, 150);

        primaryStage.setTitle("My first java app");
        primaryStage.setScene(scene);
        primaryStage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}