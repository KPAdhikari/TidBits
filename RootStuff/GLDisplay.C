#include <iostream>
#include "string.h"
#include "math.h"

#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TColor.h"
#include "TStyle.h"
#include "TGeoManager.h"
#include "TGeoTube.h"
#include "TGeoMaterial.h"
#include "TGeoVolume.h"
#include "TGeoMedium.h"
#include "TPolyLine3D.h"

using namespace std;
TGeoVolume *gWorld=0; 

int thisevent=0;

void set_color_env(){   
  //******************************************************************
  //code to improve the color palette
  //from the root web page and color codes from:
  //http://ultrahigh.org/2007/08/20/making-pretty-root-color-palettes/
  //******************************************************************
  
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  
}

void Construct()
{
  gSystem->Load("libGeom");
  TGeoManager *geom = new TGeoManager("simple1", "Simple geometry");

  //--- define some materials
  //###ka: TGeoMaterial TGeoMaterial(const char* name, Double_t a, Double_t z, Double_t rho, Double_t radlen = 0, Double_t intlen = 0)
  TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0,0,0);
  TGeoMaterial *matAl = new TGeoMaterial("Al", 26.98,13,2.7);

  //   //--- define some media
  //###ka: TGeoMedium TGeoMedium(const char* name, Int_t numed, const TGeoMaterial* mat, Double_t* params = 0)
  TGeoMedium *Vacuum = new TGeoMedium("Vacuum",1, matVacuum);
  TGeoMedium *Al = new TGeoMedium("Root Material",2, matAl);

  //--- make the top container volume
  //###ka: TGeoVolume* MakeBox(const char* name, TGeoMedium* medium, Double_t dx, Double_t dy, Double_t dz)
  TGeoVolume *top = geom->MakeBox("TOP", Vacuum, 100., 100., 100.);
  geom->SetTopVolume(top);  //###ka: void SetTopVolume(TGeoVolume* vol)



  /*
    ka: https://root.cern.ch/doc/master/classTGeoManager.html
TGeoManager - the manager class for the geometry package.

TGeoManager class is embedding all the API needed for building and tracking a geometry. It defines a global pointer (gGeoManager) in order to be fully accessible from external code. The mechanism of handling multiple geometries at the same time will be soon implemented.

TGeoManager is the owner of all geometry objects defined in a session, therefore users must not try to control their deletion. It contains lists of media, materials, transformations, shapes and volumes. Logical nodes (positioned volumes) are created and destroyed by the TGeoVolume class. Physical nodes and their global transformations are subjected to a caching mechanism due to the sometimes very large memory requirements of logical graph expansion. The caching mechanism is triggered by the total number of physical instances of volumes and the cache manager is a client of TGeoManager. The manager class also controls the painter client. This is linked with ROOT graphical libraries loaded on demand in order to control visualization actions.
Rules for building a valid geometry

A given geometry can be built in various ways, but there are mandatory steps that have to be followed in order to be validated by the modeler. There are general rules : volumes needs media and shapes in order to be created, both container an containee volumes must be created before linking them together, and the relative transformation matrix must be provided. All branches must have an upper link point otherwise they will not be considered as part of the geometry. Visibility or tracking properties of volumes can be provided both at build time or after geometry is closed, but global visualization settings (see TGeoPainter class) should not be provided at build time, otherwise the drawing package will be loaded. There is also a list of specific rules : positioned daughters should not extrude their mother or intersect with sisters unless this is specified (see TGeoVolume::AddNodeOverlap()), the top volume (containing all geometry tree) must be specified before closing the geometry and must not be positioned - it represents the global reference frame. After building the full geometry tree, the geometry must be closed (see TGeoManager::CloseGeometry()). Voxelization can be redone per volume after this process.
  */
  //###ka: https://root.cern.ch/doc/master/classTStyle.html
  //###ka: TStyle objects may be created to define special styles.
  //###ka: By default ROOT creates a default style that can be accessed via the gStyle pointer.

  //###ka: Just like the default global pointer 'gStyle' for TStyle objects, I think 
  //###ka:     gGeoManager is the default global pointer for TGeoManager objects.
  //###ka: TGeoVolume* GetVolume(const char* name) const
  //###ka: TGeoVolume* GetVolume(Int_t uid) const
  gGeoManager->GetVolume("TOP")->InvisibleAll();

  //Measurements (in cm)
   
  Double_t target_rad = 0.3;
  Double_t target_len = 48.58;

  Double_t RTPC_len = 41.;
   
  Double_t foil1_R1 = 2.;
  Double_t foil1_R2 = 2.0000018;

  //ka: Now I remember Jixie saying 3.0 cm and 7 cm being inner and outer radius in the RTPC
  //     between which we usually have our tracks and we do the fits and Kalman filtering.
  Double_t foil2_R1 = 3.;
  Double_t foil2_R2 = 3.0000018;

  Double_t GEM1_R1 = 7.;
  Double_t GEM1_R2 = 7.0005;

  Double_t GEM2_R1 = 7.3;
  Double_t GEM2_R2 = 7.3005;

  Double_t GEM3_R1 = 7.6;
  Double_t GEM3_R2 = 7.6005;

  Double_t Z_offset = 0;

  Int_t trans_lvl = 70;
   
  TGeoTube *target = new TGeoTube("target_tube",0, target_rad, target_len/2);
   
  TGeoVolume *target_vol = new TGeoVolume("target_vol",target, Al); //(*)

  top->AddNode(target_vol,1,new TGeoTranslation(0,0, Z_offset));
  gGeoManager->GetVolume("target_vol")->SetTransparency(0);   

  TGeoTube *foil1 = new TGeoTube("foil1_tube", foil1_R1, foil1_R2, RTPC_len/2);
   
  TGeoVolume *foil1_vol = new TGeoVolume("foil1_vol", foil1, Al); //(*)

  top->AddNode(foil1_vol,1,new TGeoTranslation(0,0, Z_offset));


  TGeoTube *foil2 = new TGeoTube("foil2_tube", foil2_R1, foil2_R2, RTPC_len/2);
   
  TGeoVolume *foil2_vol = new TGeoVolume("foil2_vol", foil2, Al); //(*)

  top->AddNode(foil2_vol,1,new TGeoTranslation(0,0, Z_offset));


  TGeoTube *gem1 = new TGeoTube("gem1_tube", GEM1_R1, GEM1_R2, RTPC_len/2);
  TGeoVolume *gem1_vol = new TGeoVolume("gem1_vol", gem1, Al); //(*)
  gem1_vol->SetLineColor(kOrange);
  top->AddNode(gem1_vol,1,new TGeoTranslation(0,0, Z_offset));

  TGeoTube *gem2 = new TGeoTube("gem2_tube", GEM2_R1, GEM2_R2, RTPC_len/2);
  TGeoVolume *gem2_vol = new TGeoVolume("gem2_vol", gem2, Al); //(*)
  gem2_vol->SetLineColor(kGreen);
  top->AddNode(gem2_vol,1,new TGeoTranslation(0,0, Z_offset));

  TGeoTube *gem3 = new TGeoTube("gem3_tube", GEM3_R1, GEM3_R2, RTPC_len/2);
  TGeoVolume *gem3_vol = new TGeoVolume("gem3_vol", gem3, Al); //(*)
  top->AddNode(gem3_vol,1,new TGeoTranslation(0,0, Z_offset));
  gem3_vol->SetLineColor(kRed);
  gGeoManager->GetVolume("gem3_vol")->SetTransparency(trans_lvl);   

   
  //--- draw the ROOT box.
  // by default the picture will appear in the standard ROOT TPad.
  //if you have activated the following line in system.rootrc,
  //it will appear in the GL viewer
  //#Viewer3D.DefaultDrawOption:   ogl
   
  geom->CloseGeometry();
   
  geom->SetVisLevel(4);
  
  //   top->SetVisibility(kFALSE);
  top->Draw("ogl");
  gWorld = top;
}

int  GLDisplay(int ievent=0)
{
  set_color_env();
  // gStyle->SetOptFit(1111);
  // gStyle->SetPalette(55);
  gStyle->SetCanvasPreferGL(kTRUE);
  
  Bool_t VERBOSE = 0;
  
  gStyle->SetOptStat(0);
  
  const int NumTracksPerEvent = 1;
  
  Int_t    steps;
  Int_t    rsteps;
  Int_t    steps_temp;//I need this variable 
  Int_t    index;
  Int_t    npt;

  Int_t    step_status[500];
  Double_t step_x[500],step_y[500],step_z[500];
  Double_t step_x_exp[500],step_y_exp[500],step_z_exp[500];
  Double_t step_x_fil[500],step_y_fil[500],step_z_fil[500];

  int npt_rec;
  Double_t x_exp[500],y_exp[500],z_exp[500];
  Double_t x_fil[500],y_fil[500],z_fil[500];

  //   TFile *infile=new TFile("nt_out_nowire.root");

  //TFile *infile=new TFile("infile.root");
  //TTree *t=(TTree*)infile->Get("ep");
  TTree *t=(TTree*)gROOT->FindObject("t");
  
  Int_t Entries = t->GetEntries();
  cout<<"Entries: "<<Entries<<"  thisevent["
      <<NumTracksPerEvent*ievent<<", "
      <<NumTracksPerEvent*(ievent+1)-1<<"]"<<endl;
  if(ievent>=int(Entries/NumTracksPerEvent)) return -1;
  
  t ->SetBranchAddress("index", &index);
  t ->SetBranchAddress("npt", &npt);

  t ->SetBranchAddress("step_status", step_status);
  t ->SetBranchAddress("step_x", step_x);
  t ->SetBranchAddress("step_y", step_y);
  t ->SetBranchAddress("step_z", step_z);

  t ->SetBranchAddress("step_x_exp", step_x_exp);
  t ->SetBranchAddress("step_y_exp", step_y_exp);
  t ->SetBranchAddress("step_z_exp", step_z_exp);

  t ->SetBranchAddress("step_x_fil", step_x_fil);
  t ->SetBranchAddress("step_y_fil", step_y_fil);
  t ->SetBranchAddress("step_z_fil", step_z_fil);
    
  //Call the 3D geometry
  if(!gWorld)  Construct();
  else gWorld->Draw("ogl");
  

  Int_t p = NumTracksPerEvent*ievent;

  //NumTracksPerEvent is set to 25;
  for(Int_t i = 0; i < NumTracksPerEvent; i++)
    {
      if(p+i>=Entries) return -1;
      t->GetEntry(p+i);
      
      cout<<"RootFileTrack = "<< p+i<<",  NumHits = "<<npt<<endl;
      if(npt<5) continue;

      
      npt_rec = 0;
      for (Int_t k=0;k<npt;k++)
	{
	  //remove discard hits
	  if (step_status[k]>=0) 
	    {	      
	      x_exp[npt_rec] = step_x_exp[k];
	      y_exp[npt_rec] = step_y_exp[k];
	      z_exp[npt_rec] = step_z_exp[k];

	      x_fil[npt_rec] = step_x_fil[k];
	      y_fil[npt_rec] = step_y_fil[k];
	      z_fil[npt_rec] = step_z_fil[k];

	      npt_rec++;
	    }
	  else
	    {
	      cout<<"***discraed site "<<k
		  <<",  xyz("<<step_x[k]<<", "<<step_y[k]
		  <<", "<<step_z[k]<<")\n";
	    }
	  
	}


      TPolyLine3D *track3D = new TPolyLine3D(npt,step_x,step_y,step_z);
      TPolyLine3D *track3D_exp = new TPolyLine3D(npt_rec,x_exp,y_exp,z_exp);
      TPolyLine3D *track3D_fil = new TPolyLine3D(npt_rec,x_fil,y_fil,z_fil);
   
      track3D->SetLineWidth(2);
      track3D->SetLineColor(1);
      //track3D->Draw("same");

      track3D_fil->SetLineWidth(2);
      track3D_fil->SetLineColor(kRed);
      track3D_fil->Draw("same");

      track3D_exp->SetLineWidth(2);
      track3D_exp->SetLineColor(4);
      //track3D_exp->Draw("same");

	  
      TPolyMarker3D *pm3d = new TPolyMarker3D(npt);
      for (Int_t k=0;k<npt;k++)
	{
	  pm3d->SetPoint(k, step_x[k], step_y[k], step_z[k]);
	}  
      pm3d->SetMarkerSize(0.3);
      pm3d->SetMarkerColor(4);
      pm3d->SetMarkerStyle(4);
      pm3d->Draw("same");

	  
      TPolyMarker3D *pm3d_fil = new TPolyMarker3D(npt_rec);
      for (Int_t k=0;k<npt_rec;k++)
	{
	  pm3d_fil->SetPoint(k, x_fil[k], y_fil[k], z_fil[k]);
	}
      pm3d_fil->SetMarkerSize(1);
      pm3d_fil->SetMarkerColor(2);
      pm3d_fil->SetMarkerStyle(2);
      pm3d_fil->Draw("same");

    }

  gPad->Update();
  gPad->SaveAs(Form("Movie/GLEvent_%03d.png",ievent));


  return 0;
}


void go(int n=1, int s=1, int istart=0)
{
  if(istart>0) thisevent=istart;
  for(int i=0;i<n;i++)
    {
      int ret=GLDisplay(thisevent++);
      if(ret==-1) break;
      gSystem->Sleep(s*1000);

    }
  
}
void save()
{
      gPad->Update();
      gPad->SaveAs(Form("Movie/GLEvent_%03d.png",thisevent-1));
      gPad->SaveAs(Form("Movie/GLEvent_%03d.gif",thisevent-1));
}
   
