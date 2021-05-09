//Generate points distributed with some errors around a circle
//Fit a circle through the points and draw 
//To run the script, do, eg
//   root > .x fitCircle.C   (10000 points by default)
//   root > .x fitCircle.C(100);  (with only 100 points
//   root > .x fitCircle.C(100000);  with ACLIC
//
//Author: Rene Brun

#include "TCanvas.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TMath.h"
#include "TArc.h"
//#include <TH1.h>
//#include <TH2.h>
#include "TH2.h"
#include "TVirtualFitter.h"

TGraph *gr;
double rad2deg = 180.0/TMath::Pi();


Double_t g2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}   
Double_t func(Double_t *v, Double_t *par) {
  Double_t result = par[0] + v[0]*par[1]; //tan(par[1]/rad2deg) ; //st. line eqn:   y = c + mx = par[0] + m*par[1];
   return result;
}

//____________________________________________________________________
void myfcn(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t) {
   //minimisation function computing the sum of squares of residuals
   Int_t np = gr->GetN();
   f = 0;
   Double_t *x = gr->GetX();
   Double_t *y = gr->GetY();
   for (Int_t i=0;i<np;i++) {
      Double_t u = x[i] - par[0];
      Double_t v = y[i] - par[1];
      Double_t dr = par[2] - TMath::Sqrt(u*u+v*v);
      f += dr*dr;
   }
}

//____________________________________________________________________
void fitCircle(Int_t n=10000) {
  double meanR=6.0, sigmaR=0.3, frameXorY = meanR + 3*sigmaR + sigmaR/3; //ka: 5/31/16

  //ka: =============== =============== =============== =============== 
  //ka: First define, fill and draw a graph made of a circularly distributed scatter plot.
  //ka: I am also defining a 2D histogram for the circle to see how it goes. Also, making a 3-pad canvas
  //ka:    also defining a scatter plot around a straight line.
  /*
  TH2F *h2circ = new TH2F("circ","A Circlular/Doughnut scatter plot",100,-5.0,5.0,100,-5.0,5.0);
  TH2F *h2stLine = new TH2F("stLine","A Straight Line scatter plot",100,-5.0,5.0,100,-5.0,5.0);
  TH2F *h2stLine2 = new TH2F("stLine2","A Straight Line scatter plot",100,-5.0,5.0,100,-5.0,5.0);
  */
  TH2F *h2circ = new TH2F("circ","A Circlular/Doughnut scatter plot",100,-frameXorY,frameXorY,100,-frameXorY,frameXorY);
  TH2F *h2stLine = new TH2F("stLine","A Straight Line scatter plot",100,-frameXorY,frameXorY,100,-frameXorY,frameXorY);
  TH2F *h2stLine2 = new TH2F("stLine2","A Straight Line scatter plot",100,-frameXorY,frameXorY,100,-frameXorY,frameXorY);
  h2stLine->SetMarkerColor(2);  h2stLine2->SetMarkerColor(4);
  double mSlope = tan(-30.0/rad2deg), cIntercept = -0.5;
  double mSlope2 = tan(70.0/rad2deg), cIntercept2 = -1.0;

  //generates n points around a circle and fit them
  TCanvas *c1 = new TCanvas("c1","c1",800,800); c1->Divide(2,2,0.0001,0.0001);
  c1->SetGrid(); c1->cd(1);
  gr = new TGraph(n);
  if (n> 999) gr->SetMarkerStyle(1);
  else        gr->SetMarkerStyle(3);
  TRandom3 r;
  Double_t x,y;

  for (Int_t i=0;i<n;i++) {
    //https://root.cern.ch/doc/master/classTRandom3.html : virtual void  Circle (Double_t &x, Double_t &y, Double_t r)
    //Generates random vectors, uniformly distributed over a circle of given radius.
    //Input : r = circle radius Output: x,y a random 2-d vector of length r
    //Definition at line 200 of file TRandom.cxx.
    //ka: First generates a Gaussian distributed radius (with center at 4 and sigma of 0.3)
    //ka:    then using the newly generated radius, it generates a random vector (x,y).
    r.Circle(x,y,r.Gaus(meanR,sigmaR)); //r.Circle(x,y,r.Gaus(4,0.3));
    gr->SetPoint(i,x,y); 
    h2circ->Fill(x,y); //ka: added by myself on 5/29/16 (circle-scatter plot)
      
    //ka: added by myself on 5/29/16 (line-scatter plot)
    //x = r.Uniform(-5.0,5.0); y = mSlope*x + cIntercept + r.Gaus(0.0,0.3); h2stLine->Fill(x,y); 
    //x = r.Uniform(-5.0,5.0); y = mSlope2*x + cIntercept2 + r.Gaus(0.0,0.3); h2stLine2->Fill(x,y); 
    x = r.Uniform(-frameXorY,frameXorY); y = mSlope*x  + cIntercept  + r.Gaus(0.0,sigmaR); h2stLine->Fill(x,y); 
    x = r.Uniform(-frameXorY,frameXorY); y = mSlope2*x + cIntercept2 + r.Gaus(0.0,sigmaR); h2stLine2->Fill(x,y); 
  }
  c1->DrawFrame(-frameXorY,-frameXorY,frameXorY,frameXorY);//c1->DrawFrame(-5,-5,5,5);
  gr->Draw("p");

   
   //Fit a circle to the graph points
   TVirtualFitter::SetDefaultFitter("Minuit");  //default is Minuit
   TVirtualFitter *fitter = TVirtualFitter::Fitter(0, 3);
   fitter->SetFCN(myfcn);

   fitter->SetParameter(0, "x0",   0, 0.1, 0,0);
   fitter->SetParameter(1, "y0",   0, 0.1, 0,0);
   fitter->SetParameter(2, "R",    1, 0.1, 0,0);

   Double_t arglist[1] = {0};
   fitter->ExecuteCommand("MIGRAD", arglist, 0);

   //Draw the circle on top of the points
   TArc *arc = new TArc(fitter->GetParameter(0),
      fitter->GetParameter(1),fitter->GetParameter(2));
   arc->SetLineColor(kRed);   arc->SetLineWidth(4);
   arc->Draw();



   c1->cd(2); h2circ->Draw(); h2stLine->Draw("same"); h2stLine2->Draw("same");//ka: added by myself on 5/29/16


   //use a TProfile to convert the 2-d to 1-d problem
   TProfile *prof1 = h2circ->ProfileX(), *prof2 = h2stLine->ProfileX(), *prof3 = h2stLine2->ProfileX();
   prof3->SetTitle("Profile histograms of 2D histograms");
   c1->cd(3); prof3->Draw(); prof2->Draw("same"); prof1->Draw("same"); 

   c1->cd(4);
   //ka: =============== =============== =============== =============== 
   //ka: Fit a st. line through the two str. line scatter plots. (Here I am not using std. 'pol1' method)
   const Int_t npar = 2;   Double_t f2params[npar] = {50.0,-3.0};
   //TF2 *f2 = new TF2("f2",func,-5,5,-5,5, npar),  *f2n = new TF2("f2n",func,-5,5,-5,5, npar);  //didn't worked
   // TF1 *f2 = new TF1("f2",func,-5.0,5.0, npar),  *f2n = new TF1("f2n",func,-5.0,5.0, npar);  //worked
   TF1 *f2 = new TF1("f2",func,-frameXorY,frameXorY, npar),  *f2n = new TF1("f2n",func,-frameXorY,frameXorY, npar);  //worked
   //TF1 *f2 = new TF1("f2",func,-5,5),  *f2n = new TF1("f2n",func,-5,5);  //worked
   //TF1 *f2 = new TF1("f2","[0]+[1]*x",-5,5),  *f2n = new TF1("f2n","[0]+[1]*x",-5,5);  //worked
   f2->SetLineColor(3); f2->SetParameters(f2params);    //h2stLine->Fit("pol1","0");
   f2n->SetLineColor(6); f2n->SetParameters(f2params);  //h2stLine2->Fit("pol1","0");
   h2stLine->Fit("f2","0"); h2stLine2->Fit("f2n","0");
   h2circ->Draw(); h2stLine->Draw("same"); h2stLine2->Draw("same");//ka: added by myself on 5/29/16
   
   //TF1 *fit1 = h2stLine->GetFunction("pol1"), *fit2 = h2stLine2->GetFunction("pol1");
   TF1 *fit1 = h2stLine->GetFunction("f2"), *fit2 = h2stLine2->GetFunction("f2n");
   //fit1->SetLineColor(3); fit2->SetLineColor(6); fit1->Draw("same"); fit2->Draw("same"); //worked
   f2->SetLineColor(3); f2n->SetLineColor(6); f2->Draw("same"); f2n->Draw("same"); //both this and above line worked
   cout<<"Angle & intercepts of: \n";
   cout<<"\t fit1: "<<atan(fit1->GetParameter(1))*rad2deg<<"  "<<fit1->GetParameter(0)<<endl;
   cout<<"\t fit2: "<<atan(fit2->GetParameter(1))*rad2deg<<"  "<<fit2->GetParameter(0)<<endl;
   //ka: =============== =============== =============== ===============    
   
}
