TFile *fFile;
TTree *fTree;//, *tCf;

double _index_,_x0_, _y0_, _z0_, r_circ, a_circ, b_circ;

void Tree_Init()
{
  //fFile = new TFile("opCircleFitter.root","RECREATE","Circle fitter outputs for RTPC tracks");
  //fTree = new TTree("tCf", "Circle fitter outputs for RTPC track");

  TTree *tCf=fTree;
  tCf->Branch("index",&_index_,"index/I");

  //kp: '_rec" means Kalman Filter results i.e. reconstructed results?
  tCf->Branch("p_rec",&p_rec,"p_rec/D");
  tCf->Branch("pt_rec",&pt_rec,"pt_rec/D");
  tCf->Branch("pz_rec",&pz_rec,"pz_rec/D");
  tCf->Branch("th_rec",&th_rec,"th_rec/D");
  tCf->Branch("ph_rec",&ph_rec,"ph_rec/D");
  tCf->Branch("x_rec",&x_rec,"x_rec/D");
  tCf->Branch("y_rec",&y_rec,"y_rec/D");
  tCf->Branch("z_rec",&z_rec,"z_rec/D");
  tCf->Branch("r_rec",&r_rec,"r_rec/D");
  tCf->Branch("a_rec",&a_rec,"a_rec/D");
  tCf->Branch("b_rec",&b_rec,"b_rec/D");

  tCf->Branch("npt",&npt,"npt/I");
  tCf->Branch("step_x",step_x,"step_x[npt]/D");
  tCf->Branch("step_y",step_y,"step_y[npt]/D");
  tCf->Branch("step_z",step_z,"step_z[npt]/D");
  //tCf->Branch("step_px",step_px,"step_px[npt]/D");
  //tCf->Branch("step_py",step_py,"step_py[npt]/D");
  //tCf->Branch("step_pz",step_pz,"step_pz[npt]/D");
  //tCf->Branch("step_bx",step_bx,"step_bx[npt]/D");
  //tCf->Branch("step_by",step_by,"step_by[npt]/D");
  //tCf->Branch("step_bz",step_bz,"step_bz[npt]/D");
  tCf->Branch("step_status",step_status,"step_status[npt]/I");

  tCf->Branch("step_x_exp",step_x_exp,"step_x_exp[npt]/D");
  tCf->Branch("step_y_exp",step_y_exp,"step_y_exp[npt]/D");
  tCf->Branch("step_z_exp",step_z_exp,"step_z_exp[npt]/D");

  tCf->Branch("step_x_fil",step_x_fil,"step_x_fil[npt]/D");
  tCf->Branch("step_y_fil",step_y_fil,"step_y_fil[npt]/D");
  tCf->Branch("step_z_fil",step_z_fil,"step_z_fil[npt]/D");

  //kp:  Thrown state variables
  tCf->Branch("p0",&p0,"p0/D");
  tCf->Branch("pt0",&pt0,"pt0/D");
  tCf->Branch("pz0",&pz0,"pz0/D");
  tCf->Branch("th0",&th0,"th0/D");
  tCf->Branch("ph0",&ph0,"ph0/D");
  tCf->Branch("x0",&_x0_,"x0/D");
  tCf->Branch("y0",&_y0_,"y0/D");
  tCf->Branch("z0",&_z0_,"z0/D");

  //kp: Circle Fitter results
  //tCf->Branch("p_circ",&p_circ,"p_circ/D");
  //tCf->Branch("pt_circ",&pt_circ,"pt_circ/D");
  //tCf->Branch("pz_circ",&pz_circ,"pz_circ/D");
  //tCf->Branch("th_circ",&th_circ,"th_circ/D");
  //tCf->Branch("ph_circ",&ph_circ,"ph_circ/D");
  //tCf->Branch("x_circ",&x_circ,"x_circ/D");
  //tCf->Branch("y_circ",&y_circ,"y_circ/D");
  //tCf->Branch("z_circ",&z_circ,"z_circ/D");
  tCf->Branch("r_circ",&r_circ,"r_circ/D");
  tCf->Branch("a_circ",&a_circ,"a_circ/D");
  tCf->Branch("b_circ",&b_circ,"b_circ/D");


  //kp: Global Helix Fitter results
  tCf->Branch("p_hel",&p_hel,"p_hel/D");
  tCf->Branch("pt_hel",&pt_hel,"pt_hel/D");
  tCf->Branch("pz_hel",&pz_hel,"pz_hel/D");
  tCf->Branch("th_hel",&th_hel,"th_hel/D");
  tCf->Branch("ph_hel",&ph_hel,"ph_hel/D");
  tCf->Branch("x_hel",&x_hel,"x_hel/D");
  tCf->Branch("y_hel",&y_hel,"y_hel/D");
  tCf->Branch("z_hel",&z_hel,"z_hel/D");
  tCf->Branch("r_hel",&r_hel,"r_hel/D");
  tCf->Branch("a_hel",&a_hel,"a_hel/D");
  tCf->Branch("b_hel",&b_hel,"b_hel/D");
  
  //tCf->Branch("p_3pt",&p_3pt,"p_3pt/D");
  //tCf->Branch("pt_3pt",&pt_3pt,"pt_3pt/D");
  //tCf->Branch("th_3pt",&th_3pt,"th_3pt/D");
  //tCf->Branch("r_3pt",&r_3pt,"r_3pt/D");
  //tCf->Branch("a_3pt",&a_3pt,"a_3pt/D");
  //tCf->Branch("b_3pt",&b_3pt,"b_3pt/D");

  tCf->Branch("ndf",&ndf,"ndf/I");
  tCf->Branch("chi2",&chi2,"chi2/D");
  tCf->Branch("cl",&cl,"cl/D");
}
