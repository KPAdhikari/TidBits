{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Sun Jul 29 15:55:52 2018 by ROOT version5.34/36)
//   from TTree h10/All_out
//   found on file: root_51570_pass2.a06.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root_51570_pass2.a06.root");
   if (!f) {
      f = new TFile("root_51570_pass2.a06.root");
   }
    f->GetObject("h10",tree);

//Declaration of leaves types
   UShort_t        run_num;
   UInt_t          evntid;
   Char_t          evstat;
   UShort_t        evntype;
   Short_t         evntclas;
   UShort_t        l1bit;
   Float_t         q_l;
   Float_t         t_l;
   Float_t         tr_time;
   Float_t         rf_time;
   UInt_t          hlsc;
   Int_t           intt;
   UChar_t         helicity;
   UChar_t         sync;
   UChar_t         mps;
   UChar_t         qrt;
   Float_t         hel_flag;
   Char_t          hel_ofl;
   Char_t          hel_onl;
   Char_t          hel_r26;
   Int_t           clock_u;
   Int_t           fcup_u;
   Int_t           slm_u;
   Int_t           clock_g;
   Int_t           fcup_g;
   Int_t           slm_g;
   UShort_t        raster_x;
   UShort_t        raster_y;
   UChar_t         npart;
   Int_t           gpart;
   Short_t         id[20];
   Char_t          stat[20];
   UChar_t         dc[20];
   UChar_t         cc[20];
   UChar_t         sc[20];
   UChar_t         ec[20];
   Float_t         p[20];
   Float_t         m[20];
   Char_t          q[20];
   Float_t         b[20];
   Float_t         cx[20];
   Float_t         cy[20];
   Float_t         cz[20];
   Float_t         vx[20];
   Float_t         vy[20];
   Float_t         vz[20];
   Int_t           dc_part;
   UChar_t         dc_sect[20];
   UChar_t         dc_trk[20];
   Char_t          dc_stat[20];
   UInt_t          tb_st[20];
   Float_t         dc_xsc[20];
   Float_t         dc_ysc[20];
   Float_t         dc_zsc[20];
   Float_t         dc_cxsc[20];
   Float_t         dc_cysc[20];
   Float_t         dc_czsc[20];
   Float_t         dc_vx[20];
   Float_t         dc_vy[20];
   Float_t         dc_vz[20];
   Float_t         dc_vr[20];
   Float_t         tl1_cx[20];
   Float_t         tl1_cy[20];
   Float_t         tl1_cz[20];
   Float_t         tl1_x[20];
   Float_t         tl1_y[20];
   Float_t         tl1_z[20];
   Float_t         tl1_r[20];
   Float_t         dc_c2[20];
   Float_t         dc_ccth[20];
   Float_t         dc_ccph[20];
   Int_t           ec_part;
   UShort_t        ec_stat[20];
   UChar_t         ec_sect[20];
   UChar_t         ec_whol[20];
   UInt_t          ec_inst[20];
   UInt_t          ec_oust[20];
   Float_t         etot[20];
   Float_t         ec_ei[20];
   Float_t         ec_eo[20];
   Float_t         ec_t[20];
   Float_t         ec_r[20];
   Float_t         ech_x[20];
   Float_t         ech_y[20];
   Float_t         ech_z[20];
   Float_t         ec_m2[20];
   Float_t         ec_m3[20];
   Float_t         ec_m4[20];
   Float_t         ec_c2[20];
   Int_t           sc_part;
   UChar_t         sc_sect[20];
   UChar_t         sc_hit[20];
   UChar_t         sc_pd[20];
   UChar_t         sc_stat[20];
   Float_t         edep[20];
   Float_t         sc_t[20];
   Float_t         sc_r[20];
   Float_t         sc_c2[20];
   Int_t           cc_part;
   UChar_t         cc_sect[20];
   UChar_t         cc_hit[20];
   UShort_t        cc_segm[20];
   UShort_t        nphe[20];
   Float_t         cc_t[20];
   Float_t         cc_r[20];
   Float_t         cc_c2[20];

   // Set branch addresses.
   h10->SetBranchAddress("run_num",&run_num);
   h10->SetBranchAddress("evntid",&evntid);
   h10->SetBranchAddress("evstat",&evstat);
   h10->SetBranchAddress("evntype",&evntype);
   h10->SetBranchAddress("evntclas",&evntclas);
   h10->SetBranchAddress("l1bit",&l1bit);
   h10->SetBranchAddress("q_l",&q_l);
   h10->SetBranchAddress("t_l",&t_l);
   h10->SetBranchAddress("tr_time",&tr_time);
   h10->SetBranchAddress("rf_time",&rf_time);
   h10->SetBranchAddress("hlsc",&hlsc);
   h10->SetBranchAddress("intt",&intt);
   h10->SetBranchAddress("helicity",&helicity);
   h10->SetBranchAddress("sync",&sync);
   h10->SetBranchAddress("mps",&mps);
   h10->SetBranchAddress("qrt",&qrt);
   h10->SetBranchAddress("hel_flag",&hel_flag);
   h10->SetBranchAddress("hel_ofl",&hel_ofl);
   h10->SetBranchAddress("hel_onl",&hel_onl);
   h10->SetBranchAddress("hel_r26",&hel_r26);
   h10->SetBranchAddress("clock_u",&clock_u);
   h10->SetBranchAddress("fcup_u",&fcup_u);
   h10->SetBranchAddress("slm_u",&slm_u);
   h10->SetBranchAddress("clock_g",&clock_g);
   h10->SetBranchAddress("fcup_g",&fcup_g);
   h10->SetBranchAddress("slm_g",&slm_g);
   h10->SetBranchAddress("raster_x",&raster_x);
   h10->SetBranchAddress("raster_y",&raster_y);
   h10->SetBranchAddress("npart",&npart);
   h10->SetBranchAddress("gpart",&gpart);
   h10->SetBranchAddress("id",id);
   h10->SetBranchAddress("stat",stat);
   h10->SetBranchAddress("dc",dc);
   h10->SetBranchAddress("cc",cc);
   h10->SetBranchAddress("sc",sc);
   h10->SetBranchAddress("ec",ec);
   h10->SetBranchAddress("p",p);
   h10->SetBranchAddress("m",m);
   h10->SetBranchAddress("q",q);
   h10->SetBranchAddress("b",b);
   h10->SetBranchAddress("cx",cx);
   h10->SetBranchAddress("cy",cy);
   h10->SetBranchAddress("cz",cz);
   h10->SetBranchAddress("vx",vx);
   h10->SetBranchAddress("vy",vy);
   h10->SetBranchAddress("vz",vz);
   h10->SetBranchAddress("dc_part",&dc_part);
   h10->SetBranchAddress("dc_sect",dc_sect);
   h10->SetBranchAddress("dc_trk",dc_trk);
   h10->SetBranchAddress("dc_stat",dc_stat);
   h10->SetBranchAddress("tb_st",tb_st);
   h10->SetBranchAddress("dc_xsc",dc_xsc);
   h10->SetBranchAddress("dc_ysc",dc_ysc);
   h10->SetBranchAddress("dc_zsc",dc_zsc);
   h10->SetBranchAddress("dc_cxsc",dc_cxsc);
   h10->SetBranchAddress("dc_cysc",dc_cysc);
   h10->SetBranchAddress("dc_czsc",dc_czsc);
   h10->SetBranchAddress("dc_vx",dc_vx);
   h10->SetBranchAddress("dc_vy",dc_vy);
   h10->SetBranchAddress("dc_vz",dc_vz);
   h10->SetBranchAddress("dc_vr",dc_vr);
   h10->SetBranchAddress("tl1_cx",tl1_cx);
   h10->SetBranchAddress("tl1_cy",tl1_cy);
   h10->SetBranchAddress("tl1_cz",tl1_cz);
   h10->SetBranchAddress("tl1_x",tl1_x);
   h10->SetBranchAddress("tl1_y",tl1_y);
   h10->SetBranchAddress("tl1_z",tl1_z);
   h10->SetBranchAddress("tl1_r",tl1_r);
   h10->SetBranchAddress("dc_c2",dc_c2);
   h10->SetBranchAddress("dc_ccth",dc_ccth);
   h10->SetBranchAddress("dc_ccph",dc_ccph);
   h10->SetBranchAddress("ec_part",&ec_part);
   h10->SetBranchAddress("ec_stat",ec_stat);
   h10->SetBranchAddress("ec_sect",ec_sect);
   h10->SetBranchAddress("ec_whol",ec_whol);
   h10->SetBranchAddress("ec_inst",ec_inst);
   h10->SetBranchAddress("ec_oust",ec_oust);
   h10->SetBranchAddress("etot",etot);
   h10->SetBranchAddress("ec_ei",ec_ei);
   h10->SetBranchAddress("ec_eo",ec_eo);
   h10->SetBranchAddress("ec_t",ec_t);
   h10->SetBranchAddress("ec_r",ec_r);
   h10->SetBranchAddress("ech_x",ech_x);
   h10->SetBranchAddress("ech_y",ech_y);
   h10->SetBranchAddress("ech_z",ech_z);
   h10->SetBranchAddress("ec_m2",ec_m2);
   h10->SetBranchAddress("ec_m3",ec_m3);
   h10->SetBranchAddress("ec_m4",ec_m4);
   h10->SetBranchAddress("ec_c2",ec_c2);
   h10->SetBranchAddress("sc_part",&sc_part);
   h10->SetBranchAddress("sc_sect",sc_sect);
   h10->SetBranchAddress("sc_hit",sc_hit);
   h10->SetBranchAddress("sc_pd",sc_pd);
   h10->SetBranchAddress("sc_stat",sc_stat);
   h10->SetBranchAddress("edep",edep);
   h10->SetBranchAddress("sc_t",sc_t);
   h10->SetBranchAddress("sc_r",sc_r);
   h10->SetBranchAddress("sc_c2",sc_c2);
   h10->SetBranchAddress("cc_part",&cc_part);
   h10->SetBranchAddress("cc_sect",cc_sect);
   h10->SetBranchAddress("cc_hit",cc_hit);
   h10->SetBranchAddress("cc_segm",cc_segm);
   h10->SetBranchAddress("nphe",nphe);
   h10->SetBranchAddress("cc_t",cc_t);
   h10->SetBranchAddress("cc_r",cc_r);
   h10->SetBranchAddress("cc_c2",cc_c2);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// h10->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = h10->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += h10->GetEntry(i);
//   }
}
