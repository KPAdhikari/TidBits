//https://www.geeksforgeeks.org/cc-preprocessors/
//http://localhost:8888/notebooks/GitProj/KPAdhikari/PythonStuff/C_Cpp_Notebooks/C%20or%20C%2B%2B%20Basics%201%20(Python-3%20Notebook).ipynb#Macros

#include <stdio.h>

void func1();
void func2();

#pragma startup func1
#pragma exit func2

void func1()
{
  printf("Inside func1()\n");
}

void func2()
{
  printf("Inside func2()\n");
}

int main()
{
  void func1();
  void func2();
  printf("Inside main()\n");

  void func1();
  void func2();


  return 0;
}
