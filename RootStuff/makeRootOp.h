//Copied from src/EXKalRTPC.cxx
void EXKalRTPC::Tree_Init()
{
  fFile = new TFile("h.root","RECREATE","Kalman Filter for RTPC track");
  fTree = new TTree("t", "Kalman Filter for RTPC track");

  TTree *t=fTree;
  t->Branch("index",&_index_,"index/I");

  //kp: '_rec" means Kalman Filter results i.e. reconstructed results?
  t->Branch("p_rec",&p_rec,"p_rec/D");
  t->Branch("pt_rec",&pt_rec,"pt_rec/D");
  t->Branch("pz_rec",&pz_rec,"pz_rec/D");
  t->Branch("th_rec",&th_rec,"th_rec/D");
  t->Branch("ph_rec",&ph_rec,"ph_rec/D");
  t->Branch("x_rec",&x_rec,"x_rec/D");
  t->Branch("y_rec",&y_rec,"y_rec/D");
  t->Branch("z_rec",&z_rec,"z_rec/D");
  t->Branch("r_rec",&r_rec,"r_rec/D");
  t->Branch("a_rec",&a_rec,"a_rec/D");
  t->Branch("b_rec",&b_rec,"b_rec/D");

  t->Branch("npt",&npt,"npt/I");
  t->Branch("step_x",step_x,"step_x[npt]/D");
  t->Branch("step_y",step_y,"step_y[npt]/D");
  t->Branch("step_z",step_z,"step_z[npt]/D");
  //t->Branch("step_px",step_px,"step_px[npt]/D");
  //t->Branch("step_py",step_py,"step_py[npt]/D");
  //t->Branch("step_pz",step_pz,"step_pz[npt]/D");
  //t->Branch("step_bx",step_bx,"step_bx[npt]/D");
  //t->Branch("step_by",step_by,"step_by[npt]/D");
  //t->Branch("step_bz",step_bz,"step_bz[npt]/D");
  t->Branch("step_status",step_status,"step_status[npt]/I");

  t->Branch("step_x_exp",step_x_exp,"step_x_exp[npt]/D");
  t->Branch("step_y_exp",step_y_exp,"step_y_exp[npt]/D");
  t->Branch("step_z_exp",step_z_exp,"step_z_exp[npt]/D");

  t->Branch("step_x_fil",step_x_fil,"step_x_fil[npt]/D");
  t->Branch("step_y_fil",step_y_fil,"step_y_fil[npt]/D");
  t->Branch("step_z_fil",step_z_fil,"step_z_fil[npt]/D");

  //kp:  Thrown state variables
  t->Branch("p0",&p0,"p0/D");
  t->Branch("pt0",&pt0,"pt0/D");
  t->Branch("pz0",&pz0,"pz0/D");
  t->Branch("th0",&th0,"th0/D");
  t->Branch("ph0",&ph0,"ph0/D");
  t->Branch("x0",&_x0_,"x0/D");
  t->Branch("y0",&_y0_,"y0/D");
  t->Branch("z0",&_z0_,"z0/D");

  //kp: Global Helix Fitter results
  t->Branch("p_hel",&p_hel,"p_hel/D");
  t->Branch("pt_hel",&pt_hel,"pt_hel/D");
  t->Branch("pz_hel",&pz_hel,"pz_hel/D");
  t->Branch("th_hel",&th_hel,"th_hel/D");
  t->Branch("ph_hel",&ph_hel,"ph_hel/D");
  t->Branch("x_hel",&x_hel,"x_hel/D");
  t->Branch("y_hel",&y_hel,"y_hel/D");
  t->Branch("z_hel",&z_hel,"z_hel/D");
  t->Branch("r_hel",&r_hel,"r_hel/D");
  t->Branch("a_hel",&a_hel,"a_hel/D");
  t->Branch("b_hel",&b_hel,"b_hel/D");
  
  t->Branch("p_3pt",&p_3pt,"p_3pt/D");
  t->Branch("pt_3pt",&pt_3pt,"pt_3pt/D");
  t->Branch("th_3pt",&th_3pt,"th_3pt/D");
  t->Branch("r_3pt",&r_3pt,"r_3pt/D");
  t->Branch("a_3pt",&a_3pt,"a_3pt/D");
  t->Branch("b_3pt",&b_3pt,"b_3pt/D");

  t->Branch("ndf",&ndf,"ndf/I");
  t->Branch("chi2",&chi2,"chi2/D");
  t->Branch("cl",&cl,"cl/D");

}


//I separate filling the tree into an individual subroutine since 
//filling the tree will not be necessary when provided to CLAS12 software
void EXKalRTPC::Tree_Fill(TKalTrack &kaltrack)
{
  //most of these are coming from  EXEventGen::NtReader, which is in mm

  TIter next(fKalHits, kDir);   
  //Note that the first site of kaltrack is a dummy site
  //do not include it into the output root tree
  int npt=0, iSite=1;  //site 0 is dummy site, start from 1
  EXHit *hitp = dynamic_cast<EXHit *>(next());  
  while (hitp) {     // loop over hits    
    //fill the global variables for root tree
    TVector3 xraw = hitp->GetRawXv();
    step_x[npt]=xraw.X();step_y[npt]=xraw.Y();step_z[npt]=xraw.Z();

    //filtered state vector exist only if it is not removed
    if(step_status[npt]) {
      TKalTrackSite *site = (TKalTrackSite *)kaltrack.At(iSite++); // load the site

      TVKalState *state_exp = (TVKalState*) &(site->GetState(TVKalSite::kPredicted));
      THelicalTrack hel_exp = (dynamic_cast<TKalTrackState *>(state_exp))->GetHelix();
      TVector3 x_exp=hel_exp.CalcXAt(0.0);
      step_x_exp[npt]=x_exp.X();step_y_exp[npt]=x_exp.Y();step_z_exp[npt]=x_exp.Z();

      //TVKalState *state_fil = (TVKalState*) &(site->GetCurState());
      TVKalState *state_fil = (TVKalState*) &(site->GetState(TVKalSite::kFiltered));
      THelicalTrack hel_fil = (dynamic_cast<TKalTrackState *>(state_fil))->GetHelix();
      TVector3 x_fil=hel_fil.CalcXAt(0.0);
      step_x_fil[npt]=x_fil.X();step_y_fil[npt]=x_fil.Y();step_z_fil[npt]=x_fil.Z();
      //cout<<"good hit "<<npt<<endl;
    }
    else {
      step_x_fil[npt]=0;step_y_fil[npt]=0;step_z_fil[npt]=0;
      //cout<<"*bad* hit "<<npt<<endl;
    }
    hitp = dynamic_cast<EXHit *>(next());
    npt++;
  }


  p0=fEventGen->P0_p;
  th0=fEventGen->Theta0_p;
  ph0=fEventGen->Phi0_p; 
  if(ph0> kPi) ph0-=2*kPi;
  if(ph0<-kPi) ph0+=2*kPi;
  pt0=p0*sin(th0);
  pz0=p0*cos(th0);
  _x0_=fEventGen->X0/10.;
  _y0_=fEventGen->Y0/10.;
  _z0_=fEventGen->Z0/10.;

  p_hel=fEventGen->P0_rec_p;
  th_hel=fEventGen->Theta0_rec_p;
  ph_hel=fEventGen->Phi0_rec_p; 
  pt_hel=p_hel*sin(th_hel);
  pz_hel=p0*cos(th_hel);
  x_hel=fEventGen->X0_rec_p/10.;
  y_hel=fEventGen->Y0_rec_p/10.;
  z_hel=fEventGen->Z0_rec_p/10.;

  r_hel=fEventGen->R_rec/10.;
  a_hel=fEventGen->A_rec/10.;
  b_hel=fEventGen->B_rec/10.;

  p_3pt=fEventGen->P_3pt;
  th_3pt=fEventGen->Theta_3pt;
  pt_3pt=fEventGen->Pt_3pt;
  r_3pt=fEventGen->R_3pt;
  a_3pt=fEventGen->A_3pt;
  b_3pt=fEventGen->B_3pt;

  fTree->Fill();
  _index_++;
}
