//This script is to plot the trajectory of RTPC events
//
// kp: Files copied from Jixie's code for KalRTPC that we worked on together.
// How to run:
//    It needs a root file with events such as h.root
//    To execute, do first root -l h.root
//    Then do '.x DisplayEvent.C' to display the first event (will open 2 canvases)
//    To display 'Nth" event, do 'x DisplayEvent.C(N)' (will update the canvases)
//
//   If we do go(N), it will show N events one by one as a slide-show, starting from 1st (0th) event
//      The go function declaration actually is like "void go(int n=1,int second=2, int istart=0)"
//      So, it can take 3 arguments - # of events to look at, # of seconds to sleep after each 
//           event display and event # to start from. 
//      So, if we want to see 14th event with 2 sec, sleep time, we can do as follows:
//               go(1,2,14)
//      If we do go(3,2,14), then we'll see 3 events - 14th, 15th and 16th events and so on
//
// Uses Form(const char *fmt,...)  
//          for Formats a string using a printf style format descriptor.  
//          https://root.cern.ch/doc/master/classTString.html
//
#include <iostream>
using namespace std;

#include <TQObject.h>
#include "TROOT.h"
#include <TStyle.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TTree.h>
#include <TFile.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TProfile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TVirtualFitter.h>
#include <TMinuit.h>
#include <TMath.h>

#include "TLegend.h"
#include "TString.h"
#include "TCut.h"
#include "TCutG.h"
#include "TPaveText.h"
#include "TText.h"
#include "TSystem.h"
#include "TMultiGraph.h"
#include "TLorentzVector.h"
#include <TChain.h>
#include "TLine.h"
#include "circleFitter4DisplayEvent.h"
#include "ipNtupleVars.h"
#include "opNtupleVars.h"
// http://stackoverflow.com/questions/11310898/how-do-i-get-the-type-of-a-variable
#include <typeinfo> //To use for "cout << typeid(variable).name() << endl;"


TH2F *h2yxframe = 0;
TH2F *h2xzframe = 0;
TH2F *h2yzframe = 0;
TH2F *h2rzframe = 0;
TCanvas *c3;//, *c1,*c2;
int  thisevent = 0;



//This routine only opens two canvases and defines the histograms to 
//     draw geometric volumes upon which the tracks are drawn later.
//    Nothing is drawn in this step.
void Init()
{
  TObject *obj=0;  if(obj=gROOT->FindObject("c3")) delete obj;
  //c1 = new TCanvas("c1","RTPC track display",0,20,800,800);
  //c2 = new TCanvas("c2","RTPC track display",900,20,600,600);
  //c3 = new TCanvas("c3","RTPC track display",1500,500); //c3->Divide(3,1,0.0001,0.0001);  
  c3 = new TCanvas("c3","RTPC track display",1000,500); //c3->Divide(3,1,0.0001,0.0001);  
  gStyle->SetOptStat(0);
  if(obj=gROOT->FindObject("yxframe")) delete obj;
  h2yxframe=new TH2F("yxframe","y-x", 200,-10,10,200,-10,10);
  h2yxframe->SetXTitle("X (mm)  ");  h2yxframe->SetYTitle("Y (mm)  ");
  h2yxframe->SetMarkerStyle(1);      h2yxframe->SetMarkerColor(3);
  
  //kp: Defining (to draw later) (as a single 2D histogram) the 4 green concentric 
  //    circles by defining different edges of the detector
  for(int i=0;i<3600;i++)
    {
      double phi = i*2*3.14159/3600;
      h2yxframe->Fill(2*cos(phi),2*sin(phi)); //kp:circle of radius 2 cm
      h2yxframe->Fill(3*cos(phi),3*sin(phi)); //kp:circle of radius 3 cm
      h2yxframe->Fill(7*cos(phi),7*sin(phi)); //kp:circle of radius 7 cm
      h2yxframe->Fill(8*cos(phi),8*sin(phi)); //kp:circle of radius 8 cm
    }

  /*
 fFile = new TFile("opCircleFitter.root","RECREATE","Circle fitter outputs for RTPC tracks");
 fTree = new TTree("tCf", "Circle fitter outputs for RTPC track");
 Tree_Init();
  */
}


//kp: Looks like it returns the 'mean' of a variable over 
//    all the events in the root file
double GetVariable(const char *var,TCut cut)
{
  TTree *t=(TTree*) gROOT->FindObject("t");
  //SetBranchAddress(t);

  TH1F *htemp = (TH1F*) gROOT->FindObject("htemp");
  if(htemp) delete htemp; //kp: If there is htemp in memory already, delete it, we want to make a new one
  t->Draw(Form("%s>>htemp",var),cut); //kp: Form is for format (see top comments)
  htemp = (TH1F*) gROOT->FindObject("htemp");
  return double(htemp->GetMean());
}


//kp: Returns the # of entries of a variable in the input root file
int GetEntries(const char *var,TCut cut)
{
  TTree *t=(TTree*) gROOT->FindObject("t");
  //SetBranchAddress(t);
  TH1F *htemp = (TH1F*) gROOT->FindObject("htemp");//kp: clear the memory of htemp if it was created earlier
  if(htemp) delete htemp;
  t->Draw(Form("%s>>htemp",var),cut); //kp: Form is for format (see top comments)
  htemp = (TH1F*) gROOT->FindObject("htemp");
  //cout<<"Number of entries = "<<htemp->GetEntries()<<endl;
  return htemp->GetEntries();
}


//display the trajectory of an event
//if entry>0, display the specified event
//otherwise, display the current event
int  DisplayEvent_circleFitter( int entry=0, TCut extracut="")
{
  if(thisevent<=0) cout<<"Start of the program ... \n";
  cout<<"entry, thisevent: "<<entry<<"  "<<thisevent<<endl;
  //if(thisevent<=0) {Tree_Init(); } //kp: 8/18/16
  if(thisevent<=0) Init();
  //if(thisevent<=0) {Init();  Tree_Init(); } //kp: 8/18/16


  TTree *t=(TTree*) gROOT->FindObject("t");
  if(thisevent<=0) SetBranchAddress(t);

  /*
  if(thisevent<=0)
    {
      fFile = new TFile("opCircleFitter.root","RECREATE","Circle fitter outputs for RTPC tracks");
      fTree = new TTree("tCf", "Circle fitter outputs for RTPC track");
      //Tree_Init();
    }
  */

  t->SetAlias("step_s","sqrt(step_x*step_x+step_y*step_y)");
  t->SetAlias("step_s_exp","sqrt(step_x_exp*step_x_exp+step_y_exp*step_y_exp)");
  t->SetAlias("step_s_fil","sqrt(step_x_fil*step_x_fil+step_y_fil*step_y_fil)");


  int iEvent = (entry>0) ? entry : thisevent++;
  if(iEvent>=t->GetEntries()) {
    cout<<"Reach the end of root file ...\n";
    return -1;
  }
  
  //kp: index is the ntuple variable that indicates the eventNum, so, following strings
  //    containing condition on 'index' are used to select hits from a single track/event.
  char strcut[255]; sprintf(strcut,"index==%d",iEvent);
  char strAcccut[255]; sprintf(strAcccut,"index==%d && step_status==1",iEvent);
  char strDiscut[255]; sprintf(strDiscut,"index==%d && step_status==0",iEvent);

  TCut cut = strcut;
  TCut Acccut = strAcccut;
  TCut Discardcut = strDiscut;
  //cout<<"Three TCut values: "<<cut<<", "<<Acccut<<", "<<Discardcut<<endl;
  cout<<"Dumping contents of the three TCut objects ..\n";
  cut->Dump(); Acccut->Dump(); Discardcut->Dump();

  cut += extracut;
  Acccut += extracut;
  Discardcut += extracut;
  char txt[300]; 
  //sprintf(txt,"From sprintf, TCaut values: %s, %s, %s \n",cut,Acccut,Discardcut); cout<<txt;
  //cout<<"Three TCut values: "<<cut<<", "<<Acccut<<", "<<Discardcut<<endl;
  cout<<"Again dumping contents of the three TCut objects ..\n";
  cut.Dump(); Acccut.Dump(); Discardcut.Dump();
  sprintf(txt,"Three TCut values: %s, %s, %s \n",cut.GetTitle(),
	  Acccut.GetTitle(),Discardcut.GetTitle()); cout<<txt;

  //The following steps must be done in canvases/pads because it dependes on the 'draw(..)' method
  c3->Clear();  c3->Divide(2,3);
  c3->cd(1);  double Pt = GetVariable("pt0",cut);
  c3->cd(2);  double Theta0 = GetVariable("th0*57.3",cut); 
  c3->cd(3);  double Phi0 = GetVariable("ph0*57.3",cut);
  c3->cd(4);  int NHits = GetVariable("npt",cut);
  c3->cd(5);  double Z0 = GetVariable("z0",cut);

  c3->Clear();  c3->Divide(2,3);
  c3->cd(1);  double Pt_rec = GetVariable("pt_rec",cut);
  c3->cd(2);  double Theta_rec = GetVariable("th_rec*57.3",cut); 
  c3->cd(3);  double Phi_rec = GetVariable("ph_rec*57.3",cut);
  c3->cd(4);  double Z_rec = GetVariable("z_rec",cut);

  if(NHits<1) return 0;

  TPaveText *pTP = new TPaveText(0.65,0.65,1-gStyle->GetPadRightMargin(),0.89,"brNDC");
  pTP->SetFillColor(0);  if(gROOT->IsBatch()) pTP->SetFillStyle(4000);
  pTP->SetBorderSize(0); //pTP->AddText(Form("Event %d", iEvent));
  pTP->AddText(Form("Pt_{0}=%.4f",Pt));
  pTP->AddText(Form("#theta_{0}=%.1f^{o}",Theta0));
  pTP->AddText(Form("#phi_{0}=%.1f^{o}",Phi0));
  pTP->AddText(Form("Z_{0}=%.2f",Z0));
  //pTP->AddText(Form("NHits=%d",NHits));

  TPaveText *paveText_rec = new TPaveText(0.65,0.65,1-gStyle->GetPadRightMargin(),0.89,"brNDC");
  paveText_rec->SetFillColor(0);  if(gROOT->IsBatch()) paveText_rec->SetFillStyle(4000);
  paveText_rec->SetBorderSize(0); //paveText_rec->AddText(Form("Event %d", iEvent));
  paveText_rec->AddText(Form("Pt_{rec}=%.4f",Pt_rec));
  paveText_rec->AddText(Form("#theta_{rec}=%.1f^{o}",Theta_rec));
  paveText_rec->AddText(Form("#phi_{rec}=%.1f^{o}",Phi_rec));
  paveText_rec->AddText(Form("Z_{rec}=%.2f",Z_rec));

  h2yxframe->SetTitle(Form("Event %d: y-x, %d Hits", iEvent,NHits));

  TObject *obj=0;
  if(obj=gROOT->FindObject("gryx")) delete obj;
  //if(obj=gROOT->FindObject("gryz")) delete obj;
  //if(obj=gROOT->FindObject("grxz")) delete obj;
  //if(obj=gROOT->FindObject("grrz")) delete obj;


  //kp: Following 3 Drawings are temporary, but they must be done (else doesn't work)
  //    
  c3->Clear();
  //Get the TGraph object, in one canvas there can be only one 
  c3->cd(); h2yxframe->Draw();  if(!gROOT->IsBatch()) h2yxframe->Draw("same");
  t->Draw("step_y:step_x",Acccut,"same");//kp: This creates a graph object in memory (made of hits from an event)
  TGraph *gryx=(TGraph*)(gROOT->FindObject("Graph")->Clone("gryx"));
  gryx->SetName("gryx");  gryx->SetMarkerColor(4); gryx->SetMarkerStyle(4);


  c3->Clear();  c3->cd(); h2yxframe->Draw();  t->Draw("step_y_exp:step_x_exp",Acccut,"same");
  TGraph *gryx_exp=(TGraph*)(gROOT->FindObject("Graph")->Clone("gryx_exp"));
  gryx_exp->SetName("gryx_exp");  gryx_exp->SetMarkerColor(6);gryx_exp->SetMarkerStyle(20);


  c3->Clear();  c3->cd(); h2yxframe->Draw();  t->Draw("step_y:step_x",Discardcut,"same");
  TGraph *gryx_discard=0;
  if(gROOT->FindObject("Graph")) {
    TGraph *gryx_discard=(TGraph*)(gROOT->FindObject("Graph")->Clone("gryx_discard"));
    gryx_discard->SetName("gryx_discard");
    gryx_discard->SetMarkerColor(2);gryx_discard->SetMarkerStyle(2);
  }

   //kp: Upto this point whole canvas was being used (except in one case) perhaps 
  //  drawing only one plot a time on the whole area, perhaps to test each
  //  geometry drawing one by one. Individual pads are used only after this.





  //////////////plot zoom in figure////////////
  //c3->Clear(); c3->Divide(3,1,0.0001,0.0001);  c3->cd(1); h2yxframe->Draw(); pt->Draw();
  c3->Clear(); c3->Divide(2,1,0.0001,0.0001);  
  TVirtualPad *pad = (TVirtualPad*)c3->cd(1); pad->SetGrid();  
  h2yxframe->Draw(); pTP->Draw();
  if(!gROOT->IsBatch()) h2yxframe->Draw("same");
  gryx->Draw("same p"); if(gryx_discard) gryx_discard->Draw("same p");
  t->Draw("step_y_fil:step_x_fil>>h2yx_fil",Acccut,"same*");


  c3->cd(2);
  gryx->SetTitle(Form("Event %d: Raw(Blue),Expected(Purple), Filtered(Black)",iEvent));
  gryx->Draw("AP");  gryx_exp->Draw("samep");  if(gryx_discard) gryx_discard->Draw("samep");
  t->Draw("step_y_fil:step_x_fil",Acccut,"same*");
  c3->Update();
  //c3->SaveAs(Form("Movie/RTPC_Event_Zoom_%03d.png",iEvent));//(Form("Movie/RTPC_Event_Zoom_%03d.png",iEvent));
  

  t->Scan("p0:pt0:th0*57.3:ph0*57.3:z0:npt:pt_rec:th_rec*57.3:ph_rec*57.3:z_rec",cut);


  int debug = 2;//-1; //If 1, many debug messages are printed out


  //kp: Added by myself  https://root.cern.ch/phpBB3/viewtopic.php?t=6594
  //    https://root.cern.ch/doc/master/classTGraph.html
  int nPoints = gryx->GetN(), validity=0; cout<<"# of points in this track is: "<<nPoints<<endl;
  double xTmp=0.0, yTmp=0.0, *arX = new double [nPoints], *arY = new double [nPoints];
  arX = gryx->GetX(); arY = gryx->GetY(); //worked
  if(debug==2) cout<<"Point#    x-coordinate    y-coordinate  (Using GetPoint(i,x,y) method)"<<endl;
  for(int i=0;i<nPoints;i++)
    {
      validity = gryx->GetPoint(i,xTmp,yTmp);  //worked
      if(debug==2) cout<<i<<"  "<<xTmp<<"  "<<yTmp<<endl;   //worked
    }
  if(debug==2) cout<<"Point#    x-coordinate    y-coordinate  (Using GetX() & GetY() methods)\n";
  if(debug==2) for(int i=0;i<nPoints;i++) cout<<i<<"  "<<arX[i]<<"  "<<arY[i]<<endl; //worked






  //=============================== Starting circle fit --------------
  //with nFitPoints = 15+1, 7th and many other events were not fit well, but with 10+1, 7 and some others were nicely fit
  //     but it didn't fix all, there were still events such as 19, 26, 29 etc which didn't fit well.
  //

  //Now doing circle fit, as hits arrays are ready
  //int k=0, nFitPoints = 10+1;//15+1//int(nPoints/2)+1; //nPoints+1; //+1 for the origin.
  //int k=0, nFitPoints = 13+1;//10+1//15+1//int(nPoints/2)+1; //nPoints+1; //+1 for the origin.
  int k=0, nFitPoints = 18+1;//10+1//15+1//int(nPoints/2)+1; //nPoints+1; //+1 for the origin.
  //if(2*nFitPoints > nPoints) nFitPoints = nFitPoints/2 + 1;
  if(nFitPoints-1 > nPoints) nFitPoints = nPoints+1;
  //if(nPoints<15) nFitPoints = nPoints+1;
  XYPoint p2DAr[nFitPoints]; 
  p2DAr[0].SetX(0);  p2DAr[0].SetY(0);//Including the origin (0,0) too as a first point
  //for(int i=0;i<nFitPoints;i++) { p2DAr[i].SetX(arX[i]);  p2DAr[i].SetY(arY[i]);};
  //for(int i=1;i<nFitPoints;i++) { k = i-1; p2DAr[i].SetX(arX[k]);  p2DAr[i].SetY(arY[k]);};
  //It seems hit points in the hits array are recorded in the order starting from the outermost to innermost
  //      i.e the hits generated last commmmes first in the array and so on.
  for(int i=0;i<nFitPoints-1;i++) { k = nPoints-i; p2DAr[i+1].SetX(arX[k]);  p2DAr[i+1].SetY(arY[k]);};
  //for(int i=1;i<nFitPoints;i++) { k = nPoints-2*i + 1; p2DAr[i].SetX(arX[k]);  p2DAr[i].SetY(arY[k]);};//Skipping data points with even index 'i'
  //for(int i=1;i<int(nPoints/2)+1;i++) { k = i-1; p2DAr[i].SetX(arX[k]);  p2DAr[i].SetY(arY[k]);};



  /*
  //Points only for initial estimate
  int nPoints4Init = 25 + 1;
  if(nPoints4Init-1 > nPoints) nPoints4Init = nPoints+1;
  XYPoint p2DAr4Init[nPoints4Init]; 
  p2DAr4Init[0].SetX(0);  p2DAr4Init[0].SetY(0);//Including the origin (0,0) too as a first point
  for(int i=0;i<nPoints4Init-1;i++) { k = nPoints-i; p2DAr[i+1].SetX(arX[k]);  p2DAr[i+1].SetY(arY[k]);};


  initialize(nPoints4Init, p2DAr4Init);
  */

  if(debug==2)
    {
      cout<<"i, X & Y  - Elements stored in 2D point array p2DAr: "<<endl;
      for(int i=0; i<nFitPoints; i++)
	{
	  cout<<i<<"  "<<p2DAr[i].x()<<"  "<<p2DAr[i].y()<<"  \n";
	}
    }


  

  initialize(debug, nFitPoints, p2DAr);

  XYPoint circumCenter; bool Collinearity = false;
  circumCenter = circumcenter(debug, p2DAr[0],p2DAr[1],p2DAr[2],Collinearity);
  cout<<"Collinearity: "<<Collinearity<<", "
      <<"circumcenter = ("<<circumCenter.x()<<","<<circumCenter.y()<<")\n";

  int iter = minimize(debug, 100, 0.1, 1.0e-12, nFitPoints, p2DAr);

  cout<<"Converged after "<<iter<<" iterations."<<endl;
  double radiusCirc = getRadius();
  if(xCenter==xCenter && yCenter==yCenter)
    cout<<"Final circle: Center("<<xCenter<<","<<yCenter<<") & Radius="<<radiusCirc<<endl;


  t->GetEntry(iEvent); 
  double qB = pt_hel/r_hel; //From equality of centripetal and mag force: mv^2/r = qvB, pt=mv
  double pt_circ = qB*radiusCirc;
  
  cout <<"Type of 'pt_rec': "<< typeid(pt_rec).name() << endl;
  cout <<"Type of 'p_rec': "<< typeid(p_rec).name() << endl;
  cout <<"Type of 'npt': "<< typeid(npt).name() << endl;
  cout<<"\n\n";
  cout<<"              Circ     Hel     Rec "<<endl;
  cout<<"xCenter or a: "<<xCenter<<", "<<a_hel<<", "<<a_rec<<endl;
  cout<<"yCenter or b: "<<yCenter<<", "<<b_hel<<", "<<b_rec<<endl;       
  cout<<"Radius        "<<radiusCirc<<", "<<r_hel<<", "<<r_rec<<endl;  
  cout<<"pt:           "<<pt_circ<<", "<<pt_hel<<", "<<pt_rec<<endl;  
  cout<<"\n\n";
  //========================== End of Circle fit


  _index_ = Index; _x0_=x0; _y0_=y00; _z0_=z0;
  r_circ = radiusCirc;  a_circ = xCenter;  b_circ = yCenter;
  //fTree->Fill();
  //fCf->Fill();

  //=================== Beginning of drawing circle fit program ==============
  //We're passing all hits/points (even those not used in minimization) to show all in the graphs
  drawPlots4DisplayEvent(nPoints, arX, arY, xCenter, yCenter, radiusCirc);

  return NHits;
}


//slice show n events, each last for specified second
//if istart<=0, start from current events, otherwise from specified event
void go(int n=1,int second=2, int istart=0)
{ 
  if(istart>0)  thisevent=istart;
  for(int i=0;i<n;i++)
    {
      int nHits = 0;
      while (nHits==0) 
	{
	  nHits = DisplayEvent_circleFitter(thisevent++);
	  if(nHits == -1) break;
	}
      c3->Update(); 
      if(nHits == -1) break;
      //gSystem->Sleep(second*1000);
      gSystem->Sleep(second*100);//kp: 7/19/16
    }
}


void DisplayMyEvent(TCut cut="")
{ 
  int nHits = 0;
  while (nHits==0) 
    {
      nHits = DisplayEvent_circleFitter(0,cut);
      if(nHits == -1) break;
    }
  c3->Update();
}

/*  //kp: this routine found not to be used. So, I disabled it on 7/1/16

//slice show n events, each last for specified second
//if istart<=0, start from current events, otherwise from specified event
void SliceShowMyEvent(int n=1, int second=2, int istart=0, 
		      TCut cut="")
{ 
  if(istart>0)  thisevent=istart;
  for(int i=0;i<n;i++)
    {
      int nHits = 0;
      while (nHits==0) 
	{
	  nHits = DisplayEvent_circleFitter(thisevent++,cut);
	  if(nHits == -1) break;
	}
      c3->Update();
      if(nHits == -1) break;
      gSystem->Sleep(second*1000);

    }
}

*/
