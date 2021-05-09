
/*
  https://www.geeksforgeeks.org/type-inference-in-c-auto-and-decltype/

  Type Inference in C++ (auto and decltype)

  Type Inference refers to automatic deduction of the data type of an expression in a programming language. Before C++ 11, each data type needs to be explicitly declared at compile time, limiting the values of an expression at runtime but after the new version of C++, many keywords are included which allows a programmer to leave the type deduction to the compiler itself.
  With type inference capabilities, we can spend less time having to write out things compiler already knows. As all the types are deduced in compiler phase only, the time for compilation increases slightly but it does not affect the run time of the program.

  auto keyword

  The auto keyword specifies that the type of the variable that is being declared will be automatically deducted from its initializer. In case of functions, if their return type is auto then that will be evaluated by return type expression at runtime.


  // C++ program to demonstrate working of auto
  // and type inference
  #include <bits/stdc++.h>
  using namespace std;

  int main()
  {
  auto x = 4;
  auto y = 3.37;
  auto ptr = &x;
  cout << typeid(x).name() << endl
  << typeid(y).name() << endl
  << typeid(ptr).name() << endl;

  return 0;
  }

  Output :

  i
  d
  Pi

  We have used typeid for getting the type of the variables. typeid is an operator which is used where dynamic type of an object need to be known. typeid(x).name() return shorthand name of the data type of x, for example, it return i for integers, d for doubles, Pi for the pointer to integer etc. But actual name returned is mostly compiler dependent. You can read more about typeid here.



  A good use of auto is to avoid long initializations when creating iterators for containers.

  / C++ program to demonstrate that we can use auto to
  // save time when creating iterators
  #include <bits/stdc++.h>
  using namespace std;

  int main()
  {
  // Create a set of strings
  set<string> st;
  st.insert({ "geeks", "for", "geeks", "org" });

  // 'it' evaluates to iterator to set of string
  // type automatically
  for (auto it = st.begin(); it != st.end(); it++)
  cout << *it << " ";

  return 0;
  }


  decltype Keyword

  It inspects the declared type of an entity or the type of an expression. Auto lets you declare a variable with particular type whereas decltype lets you extract the type from the variable so decltype is sort of an operator that evaluates the type of passed expression.
  Explanation of above keyword and their uses is given below.


  // C++ program to demonstrate use of decltype
  #include <bits/stdc++.h>
  using namespace std;

  int fun1() { return 10; }
  char fun2() { return 'g'; }

  int main()
  {
  // Data type of x is same as return type of fun1()
  // and type of y is same as return type of fun2()
  decltype(fun1()) x;
  decltype(fun2()) y;

  cout << typeid(x).name() << endl;
  cout << typeid(y).name() << endl;

  return 0;
  }

  Output:

  i
  c

  Below is one more example to demonstrate the use of decltype.


  // Another C++ program to demonstrate use of decltype
  #include <bits/stdc++.h>
  using namespace std;
  int main()
  {
  int x = 5;

  // j will be of type int : data type of x
  decltype(x) j = x + 5;

  cout << typeid(j).name();

  return 0;
  }

  Output:

  i

  A program that demonstrates use of both auto and decltype.
  Below is a C++ template function min_type() that returns minimum of two numbers. The two numbers can be of any integral type. The return type is determined using type of minimum of two.


  // C++ program to demonstrate use of decltype in functions
  #include <bits/stdc++.h>
  using namespace std;

  // A generic function which finds minimum of two values
  // return type is type of variable which is minimum
  template <class A, class B>
  auto findMin(A a, B b) -> decltype(a < b ? a : b)
  {
  return (a < b) ? a : b;
  }

  // driver function to test various inference
  int main()
  {
  // This call returns 3.44 of doubale type
  cout << findMin(4, 3.44) << endl;

  // This call returns 3 of double type
  cout << findMin(5.4, 3) << endl;

  return 0;
  }

  Output :

  i3.44
  3

  This article is contributed by Utkarsh Trivedi. Please write comments if you find anything incorrect, or you want to share more information about the topic discussed above
*/


// C++ program to demonstrate working of auto
// and type inference
#include <iostream> //kp:

//kp: auto_keyword_test.cpp:19:10: fatal error: 'bits/stdc++.h' file not found

//#include <bits/stdc++.h>
#include <string>
#include <set>
#include <iterator>

using namespace std;

int fun1() { return 10; }
char fun2() { return 'g'; }

/*
// A generic function which finds minimum of two values
// return type is type of variable which is minimum
template <class A, class B>
auto findMin(A a, B b) -> decltype(a < b ? a : b)
{
  return (a < b) ? a : b;
}
*/

int main()
{
  //kp: Got the following compiler warning for each of the auto use below
  //  auto_keyword_test.cpp:24:3: warning: 'auto' type specifier is a C++11 extension [-Wc++11-extensions]

  auto x = 4;
  auto y = 3.37;
  auto ptr = &x;
  auto ptr2 = &y;
  cout << typeid(x).name() << endl
       << typeid(y).name() << endl
       << typeid(ptr).name() << endl
       << typeid(ptr2).name() << endl;

  // Create a set of strings
  set<string> st;
  //st.insert({ "geeks", "for", "geeks", "org" });
  st.insert("geeks");

  // 'it' evaluates to iterator to set of string
  // type automatically
  for (auto it = st.begin(); it != st.end(); it++)
    cout << *it << " ";
  cout<<endl;


  // Data type of x is same as return type of fun1()
  // and type of y is same as return type of fun2()
  decltype(fun1()) xx;
  decltype(fun2()) yy;

  cout << typeid(xx).name() << endl;
  cout << typeid(yy).name() << endl;

  /*
  // This call returns 3.44 of doubale type
  cout << findMin(4, 3.44) << endl;

  // This call returns 3 of double type
  cout << findMin(5.4, 3) << endl;
  */
  return 0;
}
/*
  KPAd's FunPrompt $ ./auto_keyword_test
  i
  d
  Pi
  Pd
  KPAd's FunPrompt $

  Here, Pi and Pd means 'Pointers to int' and 'Pointer to double'
*/
