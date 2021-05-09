//https://www.geeksforgeeks.org/virtual-function-cpp/
// CPP program to illustrate
// concept of Virtual Functions
#include<iostream>
using namespace std;

class base
{
public:
  virtual void print ()
  { cout<< "print base class" <<endl; }

  void show ()
  { cout<< "show base class" <<endl; }

  virtual void kpTestVirtual()
  { cout<<"Hello from 'virtual kpTestVirtual()' in base class."<<endl;}

  void kpTest()
  { cout<<"Hello from 'kpTest() in base class."<<endl;}
};

class derived:public base
{
public:
  void print ()
  { cout<< "print derived class" <<endl; }

  void show ()
  { cout<< "show derived class" <<endl; }
};

int main()
{
  base *bptr;
  derived d;
  bptr = &d;

  //virtual function, binded at runtime
  bptr->print();

  // Non-virtual function, binded at compile time
  bptr->show();

  //kp: Since I didn't override or define the same methods
  //    in the derived class, both of the following will
  //    call the methods defined in the base class because
  //    they are both inheritted by the derived class and
  //    therefore, they are members of it as well.
  bptr->kpTestVirtual();

  bptr->kpTest();

}
