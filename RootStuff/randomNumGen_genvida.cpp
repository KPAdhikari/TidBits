//Copied from http://fakephysicist.com/wp-content/uploads/2017/04/genvidata.txt
// which is linked to http://fakephysicist.com/tutorials/cern-root-tutorials/random-number-in-root/
// And, I added the histogram to see how the generated data looks like
/*

FakePhysicist.com
admin@fakephysicist.com
14 April 2017

Compile with:
g++ genvidata.cpp -o genvidata `root-config --cflags --libs`

*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstring>

/****** Include the required ROOT Classes *****/
#include "TRandom.h"
#include "TH1F.h"
#include "TCanvas.h"

using namespace std;

int main() {

  int points = 11;		// No of voltage readings
  int sets = 100;		// Total no of measurement sets
  double maxV = 5.;		// Max Voltage
  double minV = 0.;		// Min Voltage
  double res = 1000.;		// Resistance Value
  double noise = 0.00005;	// Gaussian Noise of 0.05mA

  ofstream outfile("vidata.txt");

  TH1F *h1randNum = new TH1F("randNum", "Gaussian Random Number", 100, -0.0005, 0.006); 
  double gNum = 100000000.0;
  for(int jk=0;jk<sets;jk++) {
    for(int ij=0;ij<points;ij++) {
      double volt = minV + ij*(maxV - minV)/(points - 1);
      // volt ==  0.,0.5,1.0,1.5,.....,5.0
      gNum = gRandom->Gaus(volt/res,noise);       h1randNum->Fill(gNum);
      outfile << volt << "\t"
	      << gNum  //gRandom->Gaus(volt/res,noise);
	// including Gaussian noise with mean at true position and sigma 0.05mA into the current measurement
	      << endl;
    }

  }

  TCanvas *c1 = new TCanvas("c1","c1",800,800); //c1->Divide(2,2,0.0001,0.0001);
  c1->cd(); h1randNum->Draw();
  int ii = 0;
  char imgNm[100]=""; sprintf(imgNm,"gaussianRandomNumber%02d.png",ii);
  c1->SaveAs(imgNm);

  return 0;
}
