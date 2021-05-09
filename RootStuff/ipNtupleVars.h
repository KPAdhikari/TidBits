//{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Aug 17 00:59:10 2016 by ROOT version5.34/36)
//   from TTree t/Kalman Filter for RTPC track
//   found on file: h.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
//gROOT->Reset();
/*
  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("h.root");
  if (!f) {
  f = new TFile("h.root");
  }
  f->GetObject("t",tree);
*/
//Declaration of leaves types
int           Index; 
//int           index; // /usr/include/string.h:482: error: previous declaration of 'const char* index(const char*, int)'
double        p_rec;
double        pt_rec;
double        pz_rec;
double        th_rec;
double        ph_rec;
double        x_rec;
double        y_rec;
double        z_rec;
double        r_rec;
double        a_rec;
double        b_rec;
int           npt;
double        step_x[72];//h.root had [35], g4op had [72] i.e. more hit points.
double        step_y[72];
double        step_z[72];
int           step_status[72];
double        step_x_exp[72];
double        step_y_exp[72];
double        step_z_exp[72];
double        step_x_fil[72];
double        step_y_fil[72];
double        step_z_fil[72];
double        p0;
double        pt0;
double        pz0;
double        th0;
double        ph0;
double        x0;
double        y00;
//double        y0;//  /usr/include/bits/mathcalls.h:241: error: previous declaration of 'double y0(double)'
double        z0;
double        p_hel;
double        pt_hel;
double        pz_hel;
double        th_hel;
double        ph_hel;
double        x_hel;
double        y_hel;
double        z_hel;
double        r_hel;
double        a_hel;
double        b_hel;
int           ndf;
double        chi2;
double        cl;

//void SetBranchAddress(TChain *t)
void SetBranchAddress(TTree *tt)
{
  // Set branch addresses.
  tt->SetBranchAddress("index",&Index);//("index",&index); //See errors above
  tt->SetBranchAddress("p_rec",&p_rec);
  tt->SetBranchAddress("pt_rec",&pt_rec);
  tt->SetBranchAddress("pz_rec",&pz_rec);
  tt->SetBranchAddress("th_rec",&th_rec);
  tt->SetBranchAddress("ph_rec",&ph_rec);
  tt->SetBranchAddress("x_rec",&x_rec);
  tt->SetBranchAddress("y_rec",&y_rec);
  tt->SetBranchAddress("z_rec",&z_rec);
  tt->SetBranchAddress("r_rec",&r_rec);
  tt->SetBranchAddress("a_rec",&a_rec);
  tt->SetBranchAddress("b_rec",&b_rec);
  tt->SetBranchAddress("npt",&npt);
  tt->SetBranchAddress("step_x",step_x);
  tt->SetBranchAddress("step_y",step_y);
  tt->SetBranchAddress("step_z",step_z);
  tt->SetBranchAddress("step_status",step_status);
  tt->SetBranchAddress("step_x_exp",step_x_exp);
  tt->SetBranchAddress("step_y_exp",step_y_exp);
  tt->SetBranchAddress("step_z_exp",step_z_exp);
  tt->SetBranchAddress("step_x_fil",step_x_fil);
  tt->SetBranchAddress("step_y_fil",step_y_fil);
  tt->SetBranchAddress("step_z_fil",step_z_fil);
  tt->SetBranchAddress("p0",&p0);
  tt->SetBranchAddress("pt0",&pt0);
  tt->SetBranchAddress("pz0",&pz0);
  tt->SetBranchAddress("th0",&th0);
  tt->SetBranchAddress("ph0",&ph0);
  tt->SetBranchAddress("x0",&x0);
  tt->SetBranchAddress("y0",&y00);//("y0",&y0); //See errors above
  tt->SetBranchAddress("z0",&z0);
  tt->SetBranchAddress("p_hel",&p_hel);
  tt->SetBranchAddress("pt_hel",&pt_hel);
  tt->SetBranchAddress("pz_hel",&pz_hel);
  tt->SetBranchAddress("th_hel",&th_hel);
  tt->SetBranchAddress("ph_hel",&ph_hel);
  tt->SetBranchAddress("x_hel",&x_hel);
  tt->SetBranchAddress("y_hel",&y_hel);
  tt->SetBranchAddress("z_hel",&z_hel);
  tt->SetBranchAddress("r_hel",&r_hel);
  tt->SetBranchAddress("a_hel",&a_hel);
  tt->SetBranchAddress("b_hel",&b_hel);
  tt->SetBranchAddress("ndf",&ndf);
  tt->SetBranchAddress("chi2",&chi2);
  tt->SetBranchAddress("cl",&cl);
}
//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// tt->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

//////////////////Long64_t nentries = tt->GetEntries();

//////////////Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += tt->GetEntry(i);
//   }
//}
