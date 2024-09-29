package perimetre;

import java.io.IOException;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class PerimetreApp extends Application {

    @Override
    public void start(Stage primaryStage) throws IOException {

    	Parent root = FXMLLoader.load(getClass().getResource("PerimetreGUI.fxml"));

        Scene scene = new Scene(root, 350, 150);
        primaryStage.setTitle("Calcul Périmètre d’un rectangle");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}