/*
  https://www.geeksforgeeks.org/templates-cpp/

  Templates in C++

  A template is a simple and yet very powerful tool in C++. The simple idea is to pass data type as a parameter so that we don’t need to write the same code for different data types. For example, a software company may need sort() for different data types. Rather than writing and maintaining the multiple codes, we can write one sort() and pass data type as a parameter.

  C++ adds two new keywords to support templates: ‘template’ and ‘typename’. The second keyword can always be replaced by keyword ‘class’.

  How templates work?
  Templates are expanded at compiler time. This is like macros. The difference is, compiler does type checking before template expansion. The idea is simple, source code contains only function/class, but compiled code may contain multiple copies of same function/class.

  Function Templates We write a generic function that can be used for different data types. Examples of function templates are sort(), max(), min(), printArray().
  Know more on Generics in C++ (https://www.geeksforgeeks.org/generics-in-c/)
 */

#include <iostream>
using namespace std;

// One function works for all data types.  This would work
// even for user defined types if operator '>' is overloaded

//template <typename T> //kp: works
template <class T>
T myMax(T x, T y)
{
  return (x > y)? x: y;
}

//Below is the program to implement Bubble Sort using templates in C++:
// http://www.geeksforgeeks.org/bubble-sort/ (Bubble Sort)
// A template function to implement bubble sort.
// We can use this for any data type that supports
// comparison operator < and swap works for it.
template <class T>
void bubbleSort(T a[], int n) {
  for (int i = 0; i < n - 1; i++)
    for (int j = n - 1; i < j; j--)
      if (a[j] < a[j - 1])
        swap(a[j], a[j - 1]);
}

int main()
{
  cout << myMax<int>(3, 7) << endl;  // Call myMax for int
  cout << myMax<double>(3.0, 7.0) << endl; // call myMax for double
  cout << myMax<char>('g', 'e') << endl;   // call myMax for char


  int a[5] = {10, 50, 30, 40, 20};
  cout<<"sizeof(a)="<<sizeof(a)<<" sizeof(a[0]) = "<<sizeof(a[0])<<endl;
  int n = sizeof(a) / sizeof(a[0]);

  // calls template function
  bubbleSort(a, 5);

  cout << " Sorted array : ";
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << endl;
  return 0;
}
