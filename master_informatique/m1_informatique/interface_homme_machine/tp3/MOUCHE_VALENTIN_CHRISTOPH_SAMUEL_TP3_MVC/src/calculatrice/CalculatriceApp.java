package calculatrice;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class CalculatriceApp extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("CalculatriceGUI.fxml"));

        primaryStage.setTitle("Calculatrice");
        primaryStage.setScene(new Scene(root, 300, 300));
        primaryStage.show();
    }

	public static void main(String[] args) {
		launch(args);
	}
}