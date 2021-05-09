#include <iostream>
#include <iomanip>
//
//kp: This code is to see if I can simply declare a class
//    or a method (of a defined class) undefined and still
//    have the code work and it seems it does. Unless we
//    decide to use, we don't have to define a declared
//    class or a method. For example there was a line as
//    follows:
//         class HadrontherapyAnalysisManager;
//    in hadrontherapy/include/HadrontherapyRunAction.hh
//    which I saw it no where defined.
//    Similarly, I saw the following undefined method
//      void Fill(G4int i, G4int j, G4int k, G4double DE, G4double DX);
//    in hadrontherapy/include/HadrontherapyLet.hh
//    which prompted me to do this test (on 10/30-31/2019)
//

using namespace std;

class A1; //Declared but not defined because it's not used

class C1
{
public:
  //Need 'this' pointer because of ambibguity in two
  // different variables having the same name 'a' or 'b'
  C1(int a, int b) {
    this->a = a;
    this->b = b;
  }

  // No need for 'this' pointer here, because of no ambiguity
  int Sum() { return a+b; }
  int Prod() { return a*b; }
  int Div(); //Left undeclared to see if it works

private:
  int a, b;
};

int main() {
  C1 *c1 = new C1(3,4);
  cout<<c1->Sum()<<", "<<c1->Prod()<<endl;

  return 0;
}
