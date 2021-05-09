//Generate points distributed with some errors around a circle
//Fit a circle through the points and draw 
//To run the script, do, eg
//   root > .x fitCircle.C   (10000 points by default)
//   root > .x fitCircle.C(100);  (with only 100 points
//   root > .x fitCircle.C(100000);  with ACLIC
//
//Author: Rene Brun
#include <iostream>
#include "Math/Point2D.h"
#include "Math/Point3D.h"
#include "Math/Polar3D.h"
#include "Math/CylindricalEta3D.h"


#include "TCanvas.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TMath.h"
#include "TArc.h"
//#include <TH1.h>
//#include <TH2.h>
#include "TH2.h"
#include "TVirtualFitter.h"
//kp references: 
// https://root.cern.ch/phpBB3/viewtopic.php?t=17266
// 







using namespace std;
using namespace ROOT::Math;
double PI = TMath::Pi(), rad2deg = 180.0/PI;


void testPassAPointClassArray(XYZPoint *point)//(XYZPoint point [])
{
  cout<<"This is the printout from a function to which a PointArray is passed:\n";
  cout<<"Here the following columns must be 2, 3 and 4 times above columns.\n";
  for(int i=0;i<5;i++) cout<<2*point[i].x()<<" "<<3*point[i].y()<<" "<<4*point[i].z()<<" \n";
}


//____________________________________________________________________
void cartesianPoints() {
  ROOT::Math::XYZPoint p( 1,2,3);
  std::cout<<p.x()<<std::endl;
  
  ROOT::Math::XYZPoint         p1;                // create an empty vector (x = 0, y = 0, z = 0) 
  ROOT::Math::XYZPoint         p2( 1,2,3);        // create a vector with x=1, y = 2, z = 3; 
  ROOT::Math::XYZPoint         p3( 1,PI/2,PI);        // create a vector with x=1, y = 2, z = 3; 
  ROOT::Math::Polar3DPoint     p4( 1, PI/2, PI);  // create a vector with r = 1, theta = PI/2 and phi=PI
  ROOT::Math::RhoEtaPhiPoint   p5( 1, 2, PI);      // create a vector with rho= 1, eta = 2, phi = PI
  
  cout<<p1.x()<<"  "<<p2.z()<<"  "<<p3.y()<<"  "<<p4.z()<<"  "<<p5.z()<<endl;

  XYZPoint         p1n;                // create an empty vector (x = 0, y = 0, z = 0) 
  XYZPoint         p2n( 1,2,3);        // create a vector with x=1, y = 2, z = 3; 
  XYZPoint         p3n( 1,PI/2,PI);        // create a vector with x=1, y = 2, z = 3; 
  Polar3DPoint     p4n( 1, PI/2, PI);  // create a vector with r = 1, theta = PI/2 and phi=PI
  RhoEtaPhiPoint   p5n( 1, 2, PI);      // create a vector with rho= 1, eta = 2, phi = PI
  cout<<p1n.x()<<"  "<<p2n.z()<<"  "<<p3n.y()<<"  "<<p4n.z()<<"  "<<p5n.z()<<endl;

  XYZPoint pAr[5]; 
  pAr[0].SetX(2.0+0); pAr[0].SetY(3.0+0); pAr[0].SetZ(4.0+0); 
  pAr[1].SetX(2.0+1); pAr[1].SetY(3.0+1); pAr[1].SetZ(4.0+1); 
  pAr[2].SetX(2.0+2); pAr[2].SetY(3.0+2); pAr[2].SetZ(4.0+2); 
  pAr[3].SetX(2.0+3); pAr[3].SetY(3.0+3); pAr[3].SetZ(4.0+3); 
  pAr[4].SetX(2.0+4); pAr[4].SetY(3.0+4); pAr[4].SetZ(4.0+4); 
  for(int i=0;i<5;i++) cout<<pAr[i].x()<<" "<<pAr[i].y()<<" "<<pAr[i].z()<<" \n";

  testPassAPointClassArray(pAr);
}
