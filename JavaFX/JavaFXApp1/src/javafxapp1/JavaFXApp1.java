
package javafxapp1;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 *
 * @author kpadhikari
 */

/*
*  References: https://www.youtube.com/watch?v=Phog21DF4xk
*      JavaFX Tutorial 1: Installation and Hello World with Scene Builder
*    (One issue with this video  was that the sound and the actions were
*      not syncrhonous and it was hard to follow for me. Checked the comments
*      and there was no one mentioning that. So, I thought may be it is just me
*      with the youtube app in my browser or machine working wierdly today 
*      because I have lots of youtube videos open in different tabs of my 
*      firefox browser. I will find that out later (some ohter time if that
*      was the case or whether this is inherent in the original video).
*
*  What I did:
* 1) Downloaded the DMG installer for the scene builder from
*     http://gluonhq.com/products/scene-builder/thanks/?dl=/download/scene-builder-9-kit/
*     and installed it.
* 2) Instead of Tools->Options (not available in Netbeans8.2), go to NetBeans->Preferences
*    to open the same window for Options. Then Go to the Java tab and the JavaFX subtab.
*    After that add /Applications/SceneBuilder.app/ to the Scene Builder Home (or browse
*      the location wherever it is installed at). Finally click "Apply" and "OK" or just "OK"
*    (https://docs.oracle.com/javafx/scenebuilder/1/use_java_ides/sb-with-nb.htm)
*    
* 3) Until we set the scene builder properly, the 'Open' option wont show up in the 
*    menu when we right click on the fmxl file.
* 
*/
public class JavaFXApp1 extends Application {
    
    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));
        
        Scene scene = new Scene(root);
        
        stage.setScene(scene);
        stage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
