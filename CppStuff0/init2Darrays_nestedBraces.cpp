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

  int a[3][4] = {
    {0, 1, 2, 3} ,   /*  initializers for row indexed by 0 */
    {4, 5, 6, 7} ,   /*  initializers for row indexed by 1 */
    {8, 9, 10, 11}   /*  initializers for row indexed by 2 */
  };

  //The nested braces, which indicate the intended row, are optional. The following initialization is equivalent to previous example:

  //int a[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};


  /* output each array element's value */
  for (int i = 0; i < 3; i++ ) {
    for (int j = 0; j < 4; j++ ) {
      printf("a[%d][%d] = %d\n", i, j, a[i][j] );
    }
  }


  int b[3][4] = {
    {0, 1, 2, 3} ,   /*  initializers for row indexed by 0 */
    {4, 5, 6} ,   /*  initializers for row indexed by 1 */
    {8, 9, 10, 11}   /*  initializers for row indexed by 2 */
  };
  /* output each array element's value */
  for (int i = 0; i < 3; i++ ) {
    for (int j = 0; j < 4; j++ ) {
      printf("b[%d][%d] = %d,   ", i, j, b[i][j] );
    }
    printf("\n");
  }

  double db[3][4] = {
    {0, 1, 2} ,   /*  initializers for row indexed by 0 */
    {4, 5, 6} ,   /*  initializers for row indexed by 1 */
    {8, 9, 10, 11}   /*  initializers for row indexed by 2 */
  };
  /* output each array element's value */
  for (int i = 0; i < 3; i++ ) {
    for (int j = 0; j < 4; j++ ) {
      printf("db[%d][%d] = %2.1f,   ", i, j, db[i][j] );
    }
    printf("\n");
  }

  return 0;

}
