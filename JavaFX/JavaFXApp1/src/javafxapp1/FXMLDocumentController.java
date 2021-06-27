/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxapp1;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

/**
 *
 * @author kpadhikari
 */
public class FXMLDocumentController implements Initializable {

    @FXML
    private Button HelloButton;
    @FXML
    private Label ourLabel;
    @FXML
    private void printHello(ActionEvent e) {
        System.out.println("Hello World from KP!");
        ourLabel.setText("Hello World!!!!");
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    
    
}
