//Code copied from https://root-forum.cern.ch/t/multiple-tgraph2d-in-a-single-plot/7409/10
//When executed from the root prompt, it popped out a canvas with a 3D representation of the drawn object that had 6 data points
// I could even rotate it in different directions with the mouse/track-pad to get
//  the real 3D feeling.
//
// https://root.cern.ch/doc/master/classTPolyMarker3D.html
//
{
  gStyle->SetOptStat(0);

  TH3F *frame3d = new TH3F("frame3d","frame3d",10,-1,1,10,-1,1,10,-1,1);

  frame3d->Draw();

  TPolyMarker3D *pm3d1 = new TPolyMarker3D(3);
  pm3d1->SetPoint(0,1,0,0);
  pm3d1->SetPoint(1,0,1,0);
  pm3d1->SetPoint(2,0,0,1);

  pm3d1->SetMarkerSize(2);
  pm3d1->SetMarkerColor(kBlue);
  pm3d1->SetMarkerStyle(20);

  pm3d1->Draw();

  TPolyMarker3D *pm3d2 = new TPolyMarker3D(3);
  pm3d2->SetPoint(0,-1,0,0);
  pm3d2->SetPoint(1,0,-1,0);
  pm3d2->SetPoint(2,0,0,-1);

  pm3d2->SetMarkerSize(2);
  pm3d2->SetMarkerColor(kRed);
  pm3d2->SetMarkerStyle(20);

  pm3d2->Draw();
}
