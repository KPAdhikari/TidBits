/*
  https://www.geeksforgeeks.org/templates-cpp/

  Can there be more than one arguments to templates?
  Yes, like normal parameters, we can pass more than one data types as arguments to templates. The following example demonstrates the same.
 */

#include<iostream>
using namespace std;

template<class T, class U>
class A  {
  T x;
  U y;
public:
  A() {    cout<<"Constructor A() Called"<<endl;   }
  A(T a, U b) { x = a; y = b; cout<<"Constructor A(T a, U b) Called"<<endl;}
  T GetSquare() { return x*x; }
  U GetHalf() { return y/2; }

};

int main()  {
  A<char, char> a;
  A<int, double> b;
  A<int, float> c(3, 5.0);
  cout<<"half: "<<c.GetHalf()<<endl;
  cout<<"square: "<<c.GetSquare()<<endl;
  return 0;
}
