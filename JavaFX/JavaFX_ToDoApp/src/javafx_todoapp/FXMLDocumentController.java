/*
 * references:
* https://www.youtube.com/watch?v=LDVztNtJWOo
* 
* For this to work, we need a sqlite database 'first.db' in the same 
*      project folder as this, which can be done this way
*  Make sure 'sqlite' or 'sqlite3' is installed (sqlite3 comes preinstalled in my Macbook air)
*     Go to the project folder (not deep inside the like into the src folder)
*     Create two two text files to be used to prepare a database 'first.db'
*       File 'maketable.sql' with the following content:
*                  CREATE TABLE Users (USERNAME TEXT PRIMARY KEY    NOT NULL,
*                             PASSWORD       TEXT       NOT NULL );   
*       and the file 'makeuser.sql' with the following content:
*                  INSERT INTO Users (USERNAME,PASSWORD) VALUES ('username','password' );
* 
*   Next go to the sqlite shell by typing 'sqlite3' in the terminal
*   Now create the database 'first.db' with the command '.open first.db'
*         .read maketable.sql
*         .read makeuser.sql
*   Check the content with commands '.show tables;', '.table', 
 */
package javafx_todoapp;

import java.io.IOException;
import java.net.URL;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

/**
 *
 * @author kpadhikari
 */
public class FXMLDocumentController implements Initializable {
    
    @FXML
    private Label welcome_label;
    @FXML
    private TextField username_box;
    @FXML
    private TextField password_box;
    @FXML
    private Label invalid_label;
    
    @FXML
    private void handleButtonAction(ActionEvent event) throws IOException {
        System.out.println("You clicked me!");
        //label.setText("Hello World!");
        Parent home_page_parent = FXMLLoader.load(getClass().getResource("FXMLHomePage.fxml"));
        Scene home_page_scene = new Scene(home_page_parent);
        //Control the styles from the external css file.
        String css = JavaFX_ToDoApp.class.getResource("UglyStyle.css").toExternalForm();
        home_page_scene.getStylesheets().add(css);        
        Stage app_stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
     
        if (isValidCredentials()) {
            //I think without the following line, a totally new stage pops up
            // while with this line, the stage is already opened but stays hidden
            // and when the button is clicked the new stage comes to the front.
            // But for the user or viewer, the difference wont be noticeable.
            //so the following line is skippable/optional but it may have some
            //   subtle performance effect.
            app_stage.hide();

            app_stage.setScene(home_page_scene);
            app_stage.show();
        }
        else {
            username_box.clear();
            password_box.clear();
            invalid_label.setText("Sorry, invalid credentials.");
        }
    } 
    
    private boolean isValidCredentials() {
            boolean let_in = false;
            System.out.println("SELECT * FROM Users WHERE USERNAME= " + "'"  
                + username_box.getText()+ "'" + " AND PASSWORD= "+ "'" 
                + password_box.getText() + "'");
            
            Connection c = null;
            java.sql.Statement stmt = null;
            try {
                c = DriverManager.getConnection("jdbc:sqlite:first.db");
                c.setAutoCommit(false);
                System.out.println("Opened database successfully");
                stmt = c.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM Users WHERE USERNAME= " + "'" 
                + username_box.getText() + "'" + " AND PASSWORD= " + "'" 
                + password_box.getText() + "'");
                while (rs.next()) {
                    if (rs.getString("USERNAME") != null && rs.getString("PASSWORD")  != null ) {
                        String username = rs.getString("USERNAME");
                        System.out.println("USERNAME = " + username);
                        String password = rs.getString("PASSWORD");
                        System.out.println("PASSWORD = " + password);
                        let_in = true;
                    }
                }
                rs.close();
                stmt.close();
                c.close();
            } catch (Exception e) {
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
                System.exit(0);
            }
            System.out.println("Operation done successfully");
            return let_in;
        }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    
    
}

