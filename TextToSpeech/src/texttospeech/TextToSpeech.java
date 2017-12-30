/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package texttospeech;

/**
 *
 * @author kpadhikari
 * @date 12/27/17
 */
public class TextToSpeech {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //new MainJFrame().setVisible(true); //Not working - uses MBROLA voices.
        new MainJFrame2().setVisible(true); //Working (doesn't use MBROLA voices
    }
    
}
