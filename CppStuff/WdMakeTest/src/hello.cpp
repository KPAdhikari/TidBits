//http://mrbook.org/blog/tutorials/make/

//#include <iostream.h>  //This gave "fatal error: iostream.h: No such file or directory"
//You should use #include <iostream>, not iostream.h; the .h form is very old and deprecated since years. //https://askubuntu.com/questions/130781/how-to-compile-c-source-code-iostream-h-not-found-error
#include <iostream>
#include "functions.h"

using namespace std;//kp: 

void print_hello(){
   cout << "Hello World!";
}
