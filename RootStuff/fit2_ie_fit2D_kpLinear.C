// file fit2.C
#include "TF2.h"
#include "TH2.h"
// This tutorial illustrates :
//  - how to create a 2-d function
//  - fill a 2-d histogram randomly from this function
//  - fit the histogram
//  - display the fitted function on top of the histogram (scatter-plot)
//
// This example can be executed via the interpreter or/and the compiler
//   root > .x fit2.C
//   root > .x fit2.C++

double rad2deg = 57.29577951; //180.0/TMath::Pi()

Double_t g2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}  
 
Double_t fun2(Double_t *x, Double_t *par) {
  //Double_t *p1 = &par[0], *p2 = &par[5], *p3 = &par[10];
  //Double_t result = g2(x,p1) + g2(x,p2) + g2(x,p3);
  double cIntercept = -6.0, mSlope = tan(40.0/rad2deg);
  //https://root.cern.ch/doc/master/classTF1.html
  double yUnsmeared = mSlope*x + cIntercept;
  //double xSmearing = par[0]*TMath::Exp(-0.5*pow(((x-par[1])/par[2]),2));//gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) 
  double ySmearing = par[0]*TMath::Exp(-0.5*pow(((yUnsmeared - par[1])/par[2]),2));
  //Double_t result = mSlope*(x + xSmearing) + cIntercept + ySmearing;//y = mx + c ; smearing both x and y with a gaussian
  Double_t result = yUnsmeared;// + ySmearing;
  return result;
}

void fit2() {
  //const Int_t npar = 15;   Double_t f2params[npar] = {100,-3,3,-3,3,160,0,0.8,0,0.9,40,4,0.7,4,0.7};
  const Int_t npar = 3;   Double_t f2params[npar] = {1.0,0.0,0.1};
   TF2 *f2 = new TF2("f2",fun2,-10,10,-10,10, npar);
   f2->SetParameters(f2params);

   //Create an histogram and fill it randomly with f2
   TH2F *h2 = new TH2F("h2","from f2",40,-10,10,40,-10,10);
   Int_t nentries = 100000;
   h2->FillRandom("f2",nentries);
   /*
   //kp: 
   for(int i=0;i<npar-1;i++) cout<<f2params[i]<<","; cout<<f2params[npar-1]<<endl; //kp: 

   //Fit h2 with original function f2
   Float_t ratio = 4*nentries/100000; cout<<"ratio = "<<ratio<<endl;//kp: 
   //kp: multiplying 0th, 5th and 10th elements with ratio, while keeping all others the same.
   f2params[ 0] *= ratio;    f2params[ 5] *= ratio;    f2params[10] *= ratio;
   for(int i=0;i<npar-1;i++) cout<<f2params[i]<<","; cout<<f2params[npar-1]<<endl; //kp: 

   f2->SetParameters(f2params);
   h2->Fit("f2");  f2->Draw("cont1 same");
   */
   h2->Draw(); //kp
}

void fit2_ie_fit2D_kpLinear() //ka: 5/26/16
{
  fit2();
}
