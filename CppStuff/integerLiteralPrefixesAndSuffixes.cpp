#include <iostream>
#include <iomanip>

using namespace std;


int main() {
  cout<<"checking setw(n) method: "<<endl;

  cout<<"H"<<setw(15)<<"I"<<endl;
#define width 18L
  cout<<"H"<<setw(width)<<"I"<<endl;
  //#define width L
  cout<<"H"<<setw(1L)<<"I"<<endl; //works
  //cout<<"H"<<setw(1M)<<"I"<<endl; //error: invalid suffix 'M' on integer constant


  //https://www.geeksforgeeks.org/integer-literal-in-c-cpp-prefixes-suffixes/
  //Integer literal in C/C++ (Prefixes and Suffixes)
  //For more, see below:

  // PREFIXES
  cout << 213   << '\n'  // decimal integer literal
       << 0213  << '\n'  // Octal integer literal
       << 0x213A << '\n' // hexadecimal integer literal
       << 0b101  << '\n' // binary integer literal

    // SUFFIXES
    // long long literal
       << 1234567890123456789LL << '\n'

    // unsigned long long literal
       << 12345678901234567890ull << '\n'

    // automatic conversion of unsigned long long even
    // without long long prefix
       << 12345678901234567890u;

  return 0;
}

/*
  https://www.geeksforgeeks.org/integer-literal-in-c-cpp-prefixes-suffixes/


  Integer literal in C/C++ (Prefixes and Suffixes)

  Integer literal is a type of literal for an integer whose value is directly represented in source code. For example, in the assignment statement x = 1, the string 1 is an integer literal indicating the value 1, while in the statement x = 0x10 the string 0x10 is an integer literal indicating the value 16(in decimal), which is represented by 10 in hexadecimal (indicated by the 0x prefix).
  Further, in x = “1” the “1” is a string literal(not a character or an integer literal), because it is in quotes. The value of the string is 1, which happens to be an integer string.

  Integer literals are expressed in two types i.e.,

  Prefixes which indicates the base. For example, 0x10 indicates the value 16 in hexadecimal having prefix 0x.
  Suffixes which indicates the type. For example, 12345678901234LL indicates the value 12345678901234 as an long long integer having suffix LL.


  ===== Prefixes: They are basically represent in four types.=====

  Decimal-literal(base 10):- a non-zero decimal digit followed by zero or more decimal digits(0, 1, 2, 3, 4, 5, 6, 7, 8, 9). For example, 56, 78.
  Octal-literal(base 8):- a zero followed by zero or more octal digits(0, 1, 2, 3, 4, 5, 6, 7). For example, 045, 076, 06210.
  Hex-literal(base 16):- 0x or 0X followed by one or more hexadecimal digits(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, A, b, B, c, C, d, D, e, E, f, F). For example, 0x23A, 0Xb4C, 0xFEA.
  Binary-literal(base 2):- 0b or 0B followed by one or more binary digits(0, 1). For example, 0b101, 0B111.

  =======  Suffixes: They are represented in many ways according to their data types. ======

  int:- No suffix are required because integer constant are by default assigned as int data type.
  unsigned int: character u or U at the end of integer constant.
  long int: character l or L at the end of integer constant.
  unsigned long int: character ul or UL at the end of integer constant.
  long long int: character ll or LL at the end of integer constant.
  unsigned long long int: character ull or ULL at the end of integer constant.




// C++ program to demonstrate the use of
// integer literal
#include <iostream>
using namespace std;

int main()
{
    // PREFIXES
    cout << 213   << '\n'  // decimal integer literal
         << 0213  << '\n'  // Octal integer literal
         << 0x213A << '\n' // hexadecimal integer literal
         << 0b101  << '\n' // binary integer literal

         // SUFFIXES
         // long long literal
         << 1234567890123456789LL << '\n'

         // unsigned long long literal
         << 12345678901234567890ull << '\n'

         // automatic conversion of unsigned long long even
         // without long long prefix
         << 12345678901234567890u;

    return 0;
}

Output:
213
139
8506
5
1234567890123456789
12345678901234567890
12345678901234567890
1221300

Digit separator: In C++, integer literals may contain digit separators to allow digit grouping into more readable forms. This is particularly useful for bit fields, and makes it easier to see the size of large numbers (such as a million) at a glance by subitizing rather than counting digits. It is also useful for numbers that are typically grouped, such as credit card number or social security numbers.[a] Very long numbers can be further grouped by doubling up separators.
Typically decimal numbers (base-10) are grouped in three digit groups (representing one of 1000 possible values), binary numbers (base-2) in four digit groups (one nibble, representing one of 16 possible values), and hexadecimal numbers (base-16) in two digit groups (each digit is one nibble, so two digits are one byte, representing one of 256 possible values). Numbers from other systems (such as id numbers) are grouped following whatever convention is in use.



// C++ program to demonstrate digit separator
#include <iostream>
using namespace std;

int main()
{
cout << 12345678901245LL <<'\n'

// long long int literal digit separator
<< 12'345'678'901'245LL <<'\n'

// binary literal digit separator
<< 0b1000'111'0 <<'\n'

// hexadecimal literal digit separator
<< 0X12A'2b4;
return 0;
}

Output:
12345678901245
12345678901245
142
1221300

Reference:- https://en.wikipedia.org/wiki/Integer_literal
This article is contributed by Shubham Bansal. If you like GeeksforGeeks and would like to contribute, you can also write an article using contribute.geeksforgeeks.org or mail your article to contribute@geeksforgeeks.org. See your article appearing on the GeeksforGeeks main page and help other Geeks.
 */
