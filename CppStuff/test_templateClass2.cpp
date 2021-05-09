//https://www.geeksforgeeks.org/templates-cpp/
/*
Class Templates Like function templates, class templates are useful when a class defines something that is independent of the data type. Can be useful for classes like LinkedList, BinaryTree, Stack, Queue, Array, etc.

  Following is a simple example of template Array class.

*/


#include <iostream>
using namespace std;

//template <typename T>  //kp: works, tested
template <class T>       //kp: note 'typename' keyword can be replaced with 'class' keyworkd in these template definiton/declarations. So, the 'class' inside the angle brackets doesn't mean the same thing as the 'class' infront of 'Array' below.
class Array {
private:
  T *ptr;  //kp: ptr is a pointer to an object of generic type T (which could be int, float, any array of int, an array of float, or any class type such as circle, dog etc)
  int size;
public:
  Array(T arr[], int s);
  void print();
};

//kp: http://www.cplusplus.com/doc/tutorial/arrays/
//  Below, the array with empty brackets is passed means, we can pass
//  arrays of any size. This is possible because behind the scenes, we
//  only pass the pointer of an array (copy of any array isn't passed
//  for historical reasons. See below) whose size is already known to
//  the program because it's declared first (see the main() before
//  the function call during the run time). Otherwise, we would have
//  segmentation fault issues.
//  See more below about passing an array with empty brackets.
template <typename T>
Array<T>::Array(T arr[], int s) {
  ptr = new T[s];
  size = s;
  for(int i = 0; i < size; i++)
    ptr[i] = arr[i];
}

template <typename T>
void Array<T>::print() {
  for (int i = 0; i < size; i++)
    cout<<" "<<*(ptr + i);
  cout<<endl;
}

int main() {
  int arr[5] = {1, 2, 3, 4, 5};
  float fArr[4] = {1.0, 3, 2, 5};
  string sArr[3] = {"bp", "kp", "sbp"};
  Array<int> a(arr, 5);
  Array<float> ff(fArr, 4);
  Array<string> ss(sArr,3);
  a.print();
  ff.print();
  ss.print();
  return 0;
}

//kp: http://www.cplusplus.com/doc/tutorial/arrays/
/*
// arrays as parameters
#include <iostream>
using namespace std;

void printarray (int arg[], int length) {
for (int n=0; n<length; ++n)
cout << arg[n] << ' ';
cout << '\n';
}

int main ()
{
int firstarray[] = {5, 10, 15};
int secondarray[] = {2, 4, 6, 8, 10};
printarray (firstarray,3);
printarray (secondarray,5);
}

In the code above, the first parameter (int arg[]) accepts any array whose elements are of type int, whatever its length. For that reason, we have included a second parameter that tells the function the length of each array that we pass to it as its first parameter. This allows the for loop that prints out the array to know the range to iterate in the array passed, without going out of range.

In a function declaration, it is also possible to include multidimensional arrays. The format for a tridimensional array parameter is:





base_type[][depth][depth]




For example, a function with a multidimensional array as argument could be:





void procedure (int myarray[][3][4])




Notice that the first brackets [] are left empty, while the following ones specify sizes for their respective dimensions. This is necessary in order for the compiler to be able to determine the depth of each additional dimension.

In a way, passing an array as argument always loses a dimension. The reason behind is that, for historical reasons, arrays cannot be directly copied, and thus what is really passed is a pointer. This is a common source of errors for novice programmers. Although a clear understanding of pointers, explained in a coming chapter, helps a lot.
 */
