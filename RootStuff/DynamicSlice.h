//kpa: 6/11/16: Copied from example in $ROOTSYS/tutorials/hist/DynamicSlice.C 
// New about it from https://root.cern.ch/phpBB3/viewtopic.php?t=8535

void DynamicExec();
// Show the slice of a TH2 following the mouse position
void DynamicSlice()
{
   // Create a new canvas.
   TCanvas *c1 = new TCanvas("c1","Dynamic Slice Example",10,10,700,500);
   c1->SetFillColor(42);
   c1->SetFrameFillColor(33);
  
   //create a 2-d histogram, fill and draw it
   TH2F *hpxpy  = new TH2F("hpxpy","py vs px",40,-4,4,40,-4,4);
   hpxpy->SetStats(0);
   Double_t px,py;
   for (Int_t i = 0; i < 50000; i++) {
     //ka: https://root.cern.ch/doc/master/classTRandom.html
     //ka: Rannor (Float_t &a, Float_t &b): Return 2 numbers distributed following a gaussian with mean=0 and sigma=1
      gRandom->Rannor(px,py);
      hpxpy->Fill(px,py);
   }
   hpxpy->Draw("col");
   
   /*
     https://root.cern.ch/doc/master/classTPad.html
     AddExec (const char *name, const char *command): Add a new TExec object to the list of Execs.
    */
   //Add a TExec object to the canvas
   c1->AddExec("dynamic","DynamicExec()");
}

void DynamicExec()
{
   // Example of function called when a mouse event occurs in a pad.
   // When moving the mouse in the canvas, a second canvas shows the
   // projection along X of the bin corresponding to the Y position
   // of the mouse. The resulting histogram is fitted with a gaussian.
   // A "dynamic" line shows the current bin position in Y.
   // This more elaborated example can be used as a starting point
   // to develop more powerful interactive applications exploiting CINT
   // as a development engine.
   //
   // Author:  Rene Brun
   
   TObject *select = gPad->GetSelected();
   if(!select) return;
   if (!select->InheritsFrom(TH2::Class())) {gPad->SetUniqueID(0); return;}
   TH2 *h = (TH2*)select;
   gPad->GetCanvas()->FeedbackMode(kTRUE);

   //erase old position and draw a line at current position
   int pyold = gPad->GetUniqueID();
   int px = gPad->GetEventX();
   int py = gPad->GetEventY();
   float uxmin = gPad->GetUxmin();
   float uxmax = gPad->GetUxmax();
   int pxmin = gPad->XtoAbsPixel(uxmin);
   int pxmax = gPad->XtoAbsPixel(uxmax);
   if(pyold) gVirtualX->DrawLine(pxmin,pyold,pxmax,pyold);
   gVirtualX->DrawLine(pxmin,py,pxmax,py);
   gPad->SetUniqueID(py);
   Float_t upy = gPad->AbsPixeltoY(py);
   Float_t y = gPad->PadtoY(upy);

   //create or set the new canvas c2
   TVirtualPad *padsav = gPad;
   TCanvas *c2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2");
   if(c2) delete c2->GetPrimitive("Projection");
   else   c2 = new TCanvas("c2","Projection Canvas",710,10,700,500);
   c2->SetGrid();
   c2->cd();

   //draw slice corresponding to mouse position
   Int_t biny = h->GetYaxis()->FindBin(y);
   TH1D *hp = h->ProjectionX("",biny,biny);
   hp->SetFillColor(38);
   char title[80];
   sprintf(title,"Projection of biny=%d",biny);
   hp->SetName("Projection");
   hp->SetTitle(title);
   hp->Fit("gaus","ql");
   hp->GetFunction("gaus")->SetLineColor(kRed);
   hp->GetFunction("gaus")->SetLineWidth(6);
   c2->Update();
   padsav->cd();
}
