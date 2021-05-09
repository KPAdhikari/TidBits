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
//#include "/home/adhikari/LinkedFiles/rootHeaderFiles.h"
#include "/home/adhikari/LinkedFiles/minMaxAndSortingOfArray.h"
//kp references: 
// https://root.cern.ch/phpBB3/viewtopic.php?t=17266
// 


using namespace std;
using namespace ROOT::Math;
//char iDir[200]="/lustre/expphy/volatile/clas/claseg4/adhikari/CLAS12/NewCJ/coatjava-2.0.032516/TxtOp";
char oDir[200]="/u/site/www/html/Hall-B/secure/eg4/adhikari/PDWK/BoNus12/Plots/KalRTPC/CircleFit";


double PI = TMath::Pi(), rad2deg = 180.0/PI;
double xCenter=0.0, yCenter=0.0, rHat=0.0;
double J = 0, dJdx = 0, dJdy = 0;
void initialize(int arrSize, XYPoint *points);//(XYPoint point [])
void updateRadius(int arrSize, XYPoint *points);
//XYPoint circumcenter(XYPoint p1, XYPoint p2); //This may have memory loss issues (not sure for now)
XYPoint circumcenter(XYPoint pI, XYPoint pJ, XYPoint pK, bool &Collinearity); //This may have memory loss issues (not sure for now)
int minimize(int iterMax, double innerThreshold, double outerThreshold, int arrSize, XYPoint *points);
double getRadius() { return rHat; }
void drawPlots(int arrSize, XYPoint *points, double xCentre, double yCentre, double Radius);
TGraph *grIniCent, *grFinCent;  //Drawing the initial estimate of the Center as a single-point graph
TH1F *h1xIniCent = new TH1F("xIniCent","X of initial center",60,-6.0,6.0);
TH1F *h1yIniCent = new TH1F("yIniCent","Y of initial center",60,-6.0,6.0);
TH1F *h1rIniCent = new TH1F("rIniCent","Radius 'r' of initial circle",60,0.0,6.0);

void testPassAPointClassArray(XYZPoint *point)//(XYZPoint point [])
{
  cout<<"This is the printout from a function to which a PointArray is passed:\n";
  cout<<"Here the following columns must be 2, 3 and 4 times above columns.\n";
  for(int i=0;i<5;i++) cout<<2*point[i].x()<<" "<<3*point[i].y()<<" "<<4*point[i].z()<<" \n";
}

void myTLatex(double txtSize=0.03, int txtColor=2, double xx=0.152, double yy=0.82, const char txt[]="whatever")
//void myTLatex(double txtSize=0.03, int txtColor=2, double xx=0.152, double yy=0.82, char txt[])
{
  TLatex *t = new TLatex(); t->SetNDC(); t->SetTextFont(62); t->SetTextSize(txtSize); t->SetTextAlign(12); 
  t->SetTextColor(txtColor); t->DrawLatex(xx,yy,txt); 
}


//____________________________________________________________________
void circleFitter() {
  ROOT::Math::XYZPoint p( 1,2,3);
  std::cout<<p.x()<<std::endl;
  
  ROOT::Math::XYZPoint         p1;                // create an empty vector (x = 0, y = 0, z = 0) 
  ROOT::Math::XYZPoint         p3( 1,PI/2,PI);    // create a vector with x=1, y = 2, z = 3; 
  ROOT::Math::Polar3DPoint     p4( 1, PI/2, PI);  // create a vector with r = 1, theta = PI/2 and phi=PI
  ROOT::Math::RhoEtaPhiPoint   p5( 1, 2, PI);     // create a vector with rho= 1, eta = 2, phi = PI
  
  cout<<p1.x()<<"  "<<p3.y()<<"  "<<p4.z()<<"  "<<p5.z()<<endl;

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
  const int nPoints=21;//20; //5;
  XYPoint p2DAr[nPoints]; 
  /*
  p2DAr[0].SetX(30.0);  p2DAr[0].SetY(68);
  p2DAr[1].SetX(50.0);  p2DAr[1].SetY(-6);
  p2DAr[2].SetX(110.0); p2DAr[2].SetY(-20);
  p2DAr[3].SetX(35.0);  p2DAr[3].SetY(15);
  p2DAr[4].SetX(45.0);  p2DAr[4].SetY(97);
  */

  //double xArr[nPoints] = {30,50,110,35,45}, yArr[nPoints] = {68,-6,-20,15,97};
  //This g4 track couldn't be fit due to some aligned-triplet issues, I believe.
  /*
  double xArr[nPoints] = {0, 3.08605,3.08605, 3.24969, 3.42514, 3.42514, 3.73965,3.73965, 3.88916, 3.88591, 4.16638, 4.29198,4.38684, 4.4879, 4.54081, 4.61908,  4.56732,4.6318, 4.56794, 4.56794, 4.49848};
  double yArr[nPoints] = {0, 0.577633,0.577633, 0.544073, 0.392224, 0.392224, 0.194075,0.194075, 0.0249459, 0.161023, -0.181341, -0.357498,-0.689466, -0.872082, -1.21412, -1.39841, -1.55919,-1.74398, -1.90499, -1.90499, -2.06367}; 
  */
   
     //This g4 track could be fitted even before I properly managed aligned-triplets that crashed fit on above track.
  double xArr[nPoints] = {0, 0.566571, 1.03486, 1.30482, 1.35623, 1.48295, 1.60786, 1.63137, 1.74832, 1.86313, 1.96621, 2.07043, 1.84176, 1.94262, 2.04109, 1.90568, 1.90197, 1.98822, 2.07203, -2.01642, -2.0994};
  double yArr[nPoints] = {0, 3.84776, 3.89603, 3.81411, 3.64512, 3.59543, 3.54133,  3.37065, 3.3115, 3.24829, 3.01258, 2.94193, 2.91433, 2.8481, 2.77838, 2.68792, 2.49797,  2.42989, 2.35883, 2.40654, 2.3345}; 
   
  for(int i=0;i<nPoints;i++) { p2DAr[i].SetX(xArr[i]);  p2DAr[i].SetY(yArr[i]);};
  //cout<<"p2DAr.Size() = "<<p2DAr.GetSize()<<endl;

  initialize(nPoints, p2DAr);
  XYPoint circumCenter; bool Collinearity = false;
  //for(int i=0;i<5;i++)
    {
      //circumCenter = circumcenter(p2DAr[0],p2DAr[1],p2DAr[2]);
      circumCenter = circumcenter(p2DAr[0],p2DAr[1],p2DAr[2],Collinearity);
      cout<<"Collinearity: "<<Collinearity<<", "
	  <<"circumcenter = ("<<circumCenter.x()<<","<<circumCenter.y()<<")\n";
    }
    
    int iter = minimize(100, 0.1, 1.0e-12, nPoints, p2DAr);
    cout<<"Converged after "<<iter<<" iterations."<<endl;
    if(xCenter==xCenter && yCenter==yCenter)
      cout<<"Final circle: Center("<<xCenter<<","<<yCenter<<") & Radius="<<getRadius()<<endl;

    //drawPlots(nPoints, p2DAr, xCenter, yCenter,getRadius());
    drawPlots(nPoints, xArr, yArr, xCenter, yCenter,getRadius());
}


void initialize(int arrSize, XYPoint *points)//(XYPoint point [])
{
  cout<<"This is the printout from initialize(..) function\n";
  bool Collinearity = false;
  double kpRadius=0.0, kpX=0.0, kpY=0.0, kpP1X=0.0, kpP1Y=0.0;

  XYPoint p1, p2, p3, circumCenter;
  int nTriplets = 0; //Number of non-aligned triplets
  xCenter=0.0, yCenter=0.0;
  //for(int i=0;i<5;i++) cout<<2*point[i].x()<<" "<<3*point[i].y()<<" "<<4*point[i].z()<<" \n";
  for (int i = 0; i < (arrSize - 2); ++i) {
    p1 = points[i];
    for (int j = i + 1; j < (arrSize - 1); ++j) {
        p2 = points[j];
        for (int k = j + 1; k < arrSize; ++k) {
	  p3 = points[k];
	  /*
	  circumCenter = circumcenter(p1,p2,p3);
	  if(circumCenter.x()>0.9e10) continue; //artificially given large value for circumcenter of aligned triplets
	  */
	  circumCenter = circumcenter(p1,p2,p3,Collinearity); //6/16/16
	  if(Collinearity==true) continue; //artificially given large value for circumcenter of aligned triplets
	  kpX = circumCenter.x(); kpY = circumCenter.y(); kpP1X = p1.x(); kpP1Y = p1.y();
	  kpRadius = sqrt( pow(kpX-kpP1X,2) + pow(kpY-kpP1Y,2));
	  h1xIniCent->Fill(kpX); h1yIniCent->Fill(kpY); h1rIniCent->Fill(kpRadius); 
	  cout<<"circumcenter = ("<<kpX<<","<<kpY<<")\n";
	  if(fabs(kpX) > 100.0 || fabs(kpY) > 100.0 || fabs(kpRadius) >100) continue;

	  nTriplets++;
	  xCenter += circumCenter.x();
	  yCenter += circumCenter.y();
	}
    }
  }
  cout<<"kp: nTriplets = "<<nTriplets<<endl;
  if(nTriplets>0)
    {
      xCenter /= nTriplets;
      yCenter /= nTriplets;
    }
  updateRadius(arrSize, points);
  cout<<"Initial estimate of the circle fit: Radius="<<rHat
      <<",  & Center at ("<<xCenter<<","<<yCenter<<")\n";
  double xCent[1]={xCenter}, yCent[1]={yCenter}; grIniCent = new TGraph(1,xCent,yCent);
  grIniCent->SetMarkerStyle(25); grIniCent->SetMarkerSize(2); grIniCent->SetMarkerColor(6); 
}

XYPoint circumcenter(XYPoint pI, XYPoint pJ, XYPoint pK, bool &Collinearity) //This may have memory loss issues (not sure for now)
{
  Collinearity = false; 
  // some temporary variables
  XYPoint dIJ(pJ.x() - pI.x(), pJ.y() - pI.y());
  XYPoint dJK(pK.x() - pJ.x(), pK.y() - pJ.y());
  XYPoint dKI(pI.x() - pK.x(), pI.y() - pK.y());
  double sqI = pI.x() * pI.x() + pI.y() * pI.y();
  double sqJ = pJ.x() * pJ.x() + pJ.y() * pJ.y();
  double sqK = pK.x() * pK.x() + pK.y() * pK.y();

  // determinant of the linear system: 0 for aligned points
  double det = dJK.x() * dIJ.y() - dIJ.x() * dJK.y();
  XYPoint circumCenter;
  if(det==0) { //For aligned points, give an unphysically large number for x and y
    Collinearity = true; 
    circumCenter.SetX( 1.0e10 ); circumCenter.SetY(  1.0e10 ); 
    return circumCenter;
  }
  else Collinearity = false; 

  double x_center = (sqI * dJK.y() + sqJ * dKI.y() + sqK * dIJ.y()) / (2 * det);
  double y_center = -(sqI * dJK.x() + sqJ * dKI.x() + sqK * dIJ.x()) / (2 * det);
  //cout<<"det xCent yCent: "<<det<<" "<<x_center<<" "<<y_center<<endl;

  // XYPoint circumCenter( x_center, y_center); //Works
  circumCenter.SetX( x_center ); circumCenter.SetY( y_center);
  return circumCenter;
}

XYPoint circumcenterOld(XYPoint pI, XYPoint pJ, XYPoint pK) //This may have memory loss issues (not sure for now)
{
  // some temporary variables
  XYPoint dIJ(pJ.x() - pI.x(), pJ.y() - pI.y());
  XYPoint dJK(pK.x() - pJ.x(), pK.y() - pJ.y());
  XYPoint dKI(pI.x() - pK.x(), pI.y() - pK.y());
  double sqI = pI.x() * pI.x() + pI.y() * pI.y();
  double sqJ = pJ.x() * pJ.x() + pJ.y() * pJ.y();
  double sqK = pK.x() * pK.x() + pK.y() * pK.y();

  // determinant of the linear system: 0 for aligned points
  double det = dJK.x() * dIJ.y() - dIJ.x() * dJK.y();
  XYPoint circumCenter;
  if(det==0) { //For aligned points, give an unphysically large number for x and y
    circumCenter.SetX( 1.0e10 ); circumCenter.SetY(  1.0e10 ); 
    return circumCenter;
  }

  double x_center = (sqI * dJK.y() + sqJ * dKI.y() + sqK * dIJ.y()) / (2 * det);
  double y_center = -(sqI * dJK.x() + sqJ * dKI.x() + sqK * dIJ.x()) / (2 * det);
  //cout<<"det xCent yCent: "<<det<<" "<<x_center<<" "<<y_center<<endl;

  // XYPoint circumCenter( x_center, y_center); //Works
  circumCenter.SetX( x_center ); circumCenter.SetY( y_center);
  return circumCenter;
}

void updateRadius(int arrSize, XYPoint *points)
{
    rHat = 0;
    for (int i = 0; i < arrSize; ++i) {
      double dx = points[i].x() - xCenter;
      double dy = points[i].y() - yCenter;
      rHat += sqrt(dx * dx + dy * dy);
    }
    rHat /= arrSize; //kp: average of all likely radii (dist. betn.points and the initial center)
}



/** Minimize the distance residuals between the points and the circle.
 * <p>We use a non-linear conjugate gradient method with the Polak and
 * Ribiere coefficient for the computation of the search direction. The
 * inner minimization along the search direction is performed using a
 * few Newton steps. It is worthless to spend too much time on this inner
 * minimization, so the convergence threshold can be rather large.</p>
 * @param maxIter maximal iterations number on the inner loop (cumulated
 * across outer loop iterations)
 * @param innerThreshold inner loop threshold, as a relative difference on
 * the cost function value between the two last iterations
 * @param outerThreshold outer loop threshold, as a relative difference on
 * the cost function value between the two last iterations
 * @return number of inner loop iterations performed (cumulated
 * across outer loop iterations)
 * @exception LocalException if we come accross a singularity or if
 * we exceed the maximal number of iterations
 */
void computeCost(int arrSize, XYPoint *points);
double newtonStep(double u, double v, int arrSize, XYPoint *points);
int minimize(int iterMax, double innerThreshold, double outerThreshold,
	     int arrSize, XYPoint *points)
{
  cout<<"Now in minimze(..) function !!!"<<endl;
  computeCost(arrSize, points);
  if ((J < 1.0e-10) || (sqrt(dJdx * dJdx + dJdy * dJdy) < 1.0e-10)) {
    // we consider we are already at a local minimum
    cout<<"kp: We're already at a local minimum. So no further minimization ...\n";
    return 0;
  }
  double previousJ = J; cout<<"PreviousJ = "<<previousJ<<endl;
  double previousU = 0.0, previousV = 0.0;
  double previousDJdx = 0.0, previousDJdy = 0.0;
  for (int iterations = 0; iterations < iterMax;) {

    // search direction
    double u = -dJdx;
    double v = -dJdy;
    if (iterations != 0) {
      // Polak-Ribiere coefficient
      double beta =
	(dJdx * (dJdx - previousDJdx) + dJdy * (dJdy - previousDJdy))
        / (previousDJdx * previousDJdx + previousDJdy * previousDJdy);
      u += beta * previousU;
      v += beta * previousV;
    }
    previousDJdx = dJdx;
    previousDJdy = dJdy;
    previousU    = u;
    previousV    = v;

      // rough minimization along the search direction
      double innerJ;
      do {
        innerJ = J;
        double lambda = newtonStep(u, v, arrSize, points);
        //center.x += lambda * u;   center.y += lambda * v;
	xCenter += lambda * u;  yCenter += lambda * v;

        updateRadius(arrSize, points);
        computeCost(arrSize, points);
      } while ((++iterations < iterMax)
               && ((fabs(J - innerJ) / J) > innerThreshold));

      // global convergence test
      if ((fabs(J - previousJ) / J) < outerThreshold) {
        return iterations;
      }
      previousJ = J;

    }
    /*
    throw new LocalException("unable to converge after "
                             + iterMax + " iterations");
    */
}

  /** Compute the cost function and its gradient.
   * <p>The results are stored as instance attributes.</p>
   */
//void computeCost() {
void computeCost(int arrSize, XYPoint *points) {
    J    = 0;    dJdx = 0;    dJdy = 0;
    for (int i = 0; i < arrSize; ++i) {
      double dx = points[i].x() - xCenter;
      double dy = points[i].y() - yCenter;
      double di = sqrt(dx * dx + dy * dy);
      /*
      if (di < 1.0e-10) {
        throw new LocalException("cost singularity:"
                                 + " point at the circle center");
      }
      */
      double dr    = di - rHat;
      double ratio = dr / di;
      J    += dr * (di + rHat);
      dJdx += dx * ratio;
      dJdy += dy * ratio;
    }
    dJdx *= 2.0;
    dJdy *= 2.0;
}


  /** Compute the length of the Newton step in the search direction.
   * @param u abscissa of the search direction
   * @param v ordinate of the search direction
   * @return value of the step along the search direction
   */
//double newtonStep(double u, double v) {
double newtonStep(double u, double v, int arrSize, XYPoint *points) {

  // compute the first and second derivatives of the cost
  // along the specified search direction
  double sum1 = 0, sum2 = 0, sumFac = 0, sumFac2R = 0;
  for (int i = 0; i < arrSize; ++i) {
    double dx     = xCenter - points[i].x();
    double dy     = yCenter - points[i].y();
    double di     = sqrt(dx * dx + dy * dy);
    double coeff1 = (dx * u + dy * v) /  di;
    double coeff2 = di - rHat;
    sum1         += coeff1 * coeff2;
    sum2         += coeff2 / di;
    sumFac       += coeff1;
    sumFac2R     += coeff1 * coeff1 / di;
  }

  // step length attempting to nullify the first derivative
  return -sum1 / ((u * u + v * v) * sum2
		  - sumFac * sumFac / arrSize
		  + rHat * sumFac2R);
}


//void drawPlots(int nPoints, XYPoint *points, double xCentre, double yCentre, double Radius)
void drawPlots(int nPoints, double *xPoints, double *yPoints, double xCentre, double yCentre, double Radius)
{
  cout<<"Inside drawPlots() ... Center is ("<<xCenter<<","<<yCenter<<") & R="<<Radius<<endl;

  double xCent[1]={xCenter}, yCent[1]={yCenter}; grFinCent = new TGraph(1,xCent,yCent);
  grFinCent->SetMarkerStyle(24); grFinCent->SetMarkerSize(2); grFinCent->SetMarkerColor(2); 


  double xMin = ArMin(xPoints,nPoints), xMax = ArMax(xPoints,nPoints), xD = xMax - xMin;
  double yMin = ArMin(yPoints,nPoints), yMax = ArMax(yPoints,nPoints), yD = yMax - yMin;
  const int NN=8;//4
  //double arrMinMax[NN]={xMin,yMin,xMax,yMax};
  double arrMinMax[NN]={xMin,yMin,xMax,yMax, xCenter-Radius, xCenter+Radius, , yCenter-Radius, yCenter+Radius};
  double gMin = ArMin(arrMinMax,NN), gMax = ArMax(arrMinMax,NN), gD = gMax - gMin;

  TGraph *gr = new TGraph(nPoints);
  for (Int_t i=0;i<nPoints;i++) {
    //gr->SetPoint(i,points[i].x(),points[i].y()); 
    gr->SetPoint(i,xPoints[i],yPoints[i]); 
  }
  gr->SetMarkerStyle(3);
  
  cout<<"Dbg 1 \n";
  //double phiMin=90.0, phiMax=288.0;
  double phiMin=0.0, phiMax=360.0;
  //TArc *arc = new TArc(xCentre, yCentre, Radius);//worked (but draws full circle going outside pad)
  TArc *arc = new TArc(xCentre, yCentre, Radius,phiMin,phiMax);//worked
  //TEllipse *arc= new TEllipse(xCentre, yCentre, Radius, Radius,phiMin,phiMax);     //worked
  //TEllipse *arc= new TEllipse(xCentre, yCentre, Radius, Radius);//,phiMin,phiMax); //worked
  arc->SetLineColor(kRed);   arc->SetLineWidth(1); //arc->IsTransparent();
  arc->SetFillStyle(4000); 
  //arc->SetFillStyle(3001);
  cout<<"Dbg 2 \n";
  char fNm[400];
  TCanvas *c1 = new TCanvas("c1","c1",600,600); //c1->Divide(2,2,0.0001,0.0001);
  c1->SetGrid(); c1->cd();   
  //c1->DrawFrame(-30.0,-30.0,120.0,120.0);//c1->DrawFrame(-5,-5,5,5);
  c1->DrawFrame(gMin-0.1*gD,gMin-0.1*gD,gMax+0.1*gD,gMax+0.1*gD,"Y vs X");//Using global min/max for real looking circles
  //c1->DrawFrame(gMin-0.1*gD,gMin-0.1*gD,gMax+0.1*gD,gMax+0.1*gD,"Y vs X", "X", "Y");
  //gr->GetXaxis()->SetTitle("X"); gr->GetYaxis()->SetTitle("Y");
  //c1->GetXaxis()->SetTitle("X"); c1->GetYaxis()->SetTitle("Y");
  //c1->SetXTitle("X"); c1->SetYTitle("Y");
  gr->Draw("P"); grIniCent->Draw("P"); grFinCent->Draw("P"); arc->Draw("same");
  cout<<"Dbg 3 \n";
  //arc->Draw("same"); gr->Draw("P"); 
  //TEllipse el1(0.,0.,100.,100.); el1.Draw();
  myTLatex(0.035,6,0.12,0.92,"Initial Estimate of Center");
  myTLatex(0.035,2,0.12,0.88,"Final Estimate of Center");
  //idea from https://root.cern.ch/root/roottalk/roottalk03/5140.html
  cout<<"Dbg 4 \n";
   c1->Update();
   gr->GetHistogram()->GetXaxis()->SetTitle("X");
   gr->GetHistogram()->GetYaxis()->SetTitle("Y");
   c1->Modified();
  cout<<"Dbg 5 \n";
  sprintf(fNm,"%s/algo_conjugate_gradient_M_Isonobe.gif",oDir); cout<<"Dbg 6 \n";
  c1->SaveAs(fNm);

  cout<<"Dbg 7 \n";

  TCanvas *c2 = new TCanvas("c2","c2",1200,400); c2->Divide(3,1,0.0001,0.0001);
  c2->cd(1); h1xIniCent->Draw(); c2->cd(2); h1yIniCent->Draw(); c2->cd(3); h1rIniCent->Draw();
  sprintf(fNm,"%s/algo_conjugate_gradient_M_Isonobe_xyR.gif",oDir); c2->SaveAs(fNm);
}
