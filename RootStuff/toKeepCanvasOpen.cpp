#include "/u/home/adhikari/LinkedFiles/myOwnHeaderFiles.h"
#include "DynamicSlice.h"

using namespace std;

int main(int argc, char **argv){
  TApplication theApp("tapp", &argc, argv);
 
   TH1F *h = new TH1F("h","h",100,-3,3);
   h->FillRandom("gaus",1000);
   TCanvas *c1=new TCanvas("c1");
   h->Draw();
   c1->Update();
 
   theApp.Run();
   
   return 0;
}
