package simulateur;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class SimulateurApp extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("SimulateurGUI.fxml"));

        primaryStage.setTitle("Simulateur de prêt");
        primaryStage.setScene(new Scene(root, 550, 385));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}