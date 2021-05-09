#include "/u/home/adhikari/LinkedFiles/myOwnHeaderFiles.h"
#include "DynamicSlice.h"

using namespace std;

int main(int argc, char **argv)
{
  //https://root.cern.ch/phpBB3/viewtopic.php?t=9808
  // https://root.cern.ch/phpBB3/viewtopic.php?t=8535
  TApplication theApp("tapp", &argc, argv);
  //kpa: I needed to add TApplication objects to be able to keep Canvas open. 
  //    I could run DynamicSlice.C from the ROOT prompt (CINT) with the mouseover functionality
  //    However, so far I am not able to do so.
  //Without TApplication, I couldn't even keep the TCanvas open. Now I can but, mousever is still
  //   not working.

  DynamicSlice();
  // h->Draw();
  //c1->Update();
 
  theApp.Run();  
   return 0;
}
