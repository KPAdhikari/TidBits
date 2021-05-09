//Compiling with "g++ -std=c++11 cppHelloWorld.cpp" will give us a.out
//  c++11 is the version# of g++
// 5/29/17: https://www.youtube.com/watch?v=Rub-JsjMhWY (One video tutorial,
//     about 1 hour long (actually 1:10:32 long)
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {

  cout << "Hello World" <<  endl;

  int myAge = 40;
  float favNum = 3.141592;
  double otherfavNum = 1.6180339887;
  int largestInt = 2147483647;
  int largestIntPlusOne = 2147483648;

  cout << "Size of int " << sizeof(myAge) << endl;
  cout << "Size of float " << sizeof(favNum) << endl;
  cout << "Size of double " << sizeof(otherfavNum) << endl;

  cout << "Largest int " << largestInt << endl;
  cout << "Largest int + 1: " << largestIntPlusOne << endl;
  cout << "Largest int + 1: " << largestInt + 1 << endl;

  //ternary operator: video time 13:45
  //Syntax:     variable = (condition) ? valueToBeAssignedIfTrue : valueToBeAssignedIffFalse

  int largestNum = (5>2) ? 5 : 2; //Will assign 5 to largestNum

  char myName[5][5] = { {'D', 'e', 'r', 'e', 'k'},
                        {'B', 'a', 'n', 'a', 's'}};
  cout << "2nd letter in 2nd array " << myName[1][1] <<endl;

  //while loop: video time 18:59

  int randNum = (rand() % 100) + 1;

  while(randNum != 100) { //continue random # gen until 100 is generated.

    randNum = (rand() % 100) + 1;

    cout << randNum << ", ";
  }

  cout << endl;

  //String in C and C++: video time 22:44
  //C-string
  char happyArray[6] = {'H', 'a', 'p', 'p', 'y', '\0'};
  //C++ string: C++ provides string objects
  string birthdayString = " Birthday";

  //Concatenation of C and C++ strings
  cout << happyArray + birthdayString << endl;

  string yourName;
  cout << "What is your name? ";
  getline(cin, yourName);
  cout << "hello " << yourName << endl;

  return 0;

}
