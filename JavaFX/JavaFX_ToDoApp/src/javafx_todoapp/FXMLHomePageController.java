/*
 * Refs:
*   https://www.youtube.com/watch?v=ZtemWZ5IQeM 
*        JavaFX tutorial #6: More features for our ToDoapp - Tasks DB
*  Corresponding code is at:
*     https://github.com/PHJohnson/JavaFXTutorial6
 */
package javafx_todoapp;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author kpadhikari
 */
public class FXMLHomePageController implements Initializable {
    
    @FXML
    private Button insert_button;
    @FXML
    private Button view_button;
    @FXML
    private Label task_label;
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    
    
    @FXML
    private void insertButtonAction(ActionEvent event) throws IOException {
        System.out.println("insertbuttonaction");
        Parent insert_page_parent = FXMLLoader.load(getClass().getResource("FXMLInsertPage.fxml"));
        Scene insert_page_scene = new Scene(insert_page_parent);
        Stage app_stage = (Stage)((Node) event.getSource()).getScene().getWindow();
        app_stage.hide(); //optional
        app_stage.setScene(insert_page_scene);
        app_stage.show();
    }
    
    //This was missing in the corresponding file at the authors github repo:
    //   i.e. at https://github.com/PHJohnson/JavaFXTutorial6/tree/master/src/todoapp
    @FXML
    private void viewButtonAction(ActionEvent event) throws IOException {
        System.out.println("viewbuttonaction");
        Parent view_page_parent = FXMLLoader.load(getClass().getResource("FXMLViewPage.fxml"));
        Scene view_page_scene = new Scene(view_page_parent);
        Stage app_stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        app_stage.hide(); //optional
        app_stage.setScene(view_page_scene);
        app_stage.show();        
    }
}
