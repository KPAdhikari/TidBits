/*
Usage:

./getFileNameExtension    /path/../filename.ext


We can give any path to the filename.
 */



/*
//https://www.oreilly.com/library/view/c-cookbook/0596007612/ch10s14.html

  10.13. Extracting a File Extension from a String
  Problem

  Given a filename or a complete path, you need to retrieve the file extension, which is the part of a filename that follows the last period. For example, in the filenames src.cpp, Window.class, and Resume.doc, the file extensions are .cpp, .class, and .doc.
  Solution

  Convert the file and/or pathname to a string, use the rfind member function to locate the last period, and return everything after that. Example 10-20 shows how to do this.

  Example 10-20. Getting a file extension from a filename
 */

#include <iostream>
#include <string>

using namespace std;
//using std::string;//Not needed if 'using namespace std;' is used

string getFileExt(const string& s) {

  size_t i = s.rfind('.', s.length());
  cout<<"kp:   i = "<<i<<" where  size_t i = s.rfind('.', s.length());"<<endl;
  cout<<"string::npos = "<<string::npos<<endl;

  if (i != string::npos) {
	return(s.substr(i+1, s.length() - i));
  }

  return("");
}

//kp: Defining one that returns the 'filename' from '/path/../filename.ext'
string getFileName(const string& s) {

  size_t i = s.rfind('/', s.length());
  size_t j = s.rfind('.', s.length());
  cout<<"kp:   i = "<<i<<" where  size_t i = s.rfind('/', s.length());"<<endl;
  cout<<"kp:   j = "<<j<<" where  size_t i = s.rfind('.', s.length());"<<endl;

  if (i == string::npos) i = -1;

  //if (i != string::npos) {
	return(s.substr(i+1, j - i -1));
	//}

  return("");
}

int main(int argc, char** argv) {

  string path = argv[1];

  cout<<"=========== kp: Testing string::npos ======= "<<endl;
  cout<<"http://www.cplusplus.com/reference/string/string/npos/ says \n";
  cout<<"\t npos is a static member constant value with the greatest possible value for an element of type size_t.\n";
  cout<<" "<<endl;
  string str = "/bp/kp/bp/kp.adhikari@coldmail.com";
  cout<<"str.rfind('.', str.length()) = "<<str.rfind('.', str.length())<<endl;
  cout<<"str.rfind('@', str.length()) = "<<str.rfind('@', str.length())<<endl;
  cout<<"str.rfind('#', str.length()) = "<<str.rfind('#', str.length())<<endl;
  cout<<"str.rfind('/', str.length()) = "<<str.rfind('/', str.length())<<endl;
  cout<<"So, it seems if a string has a multiple delimiter of the same kind, rfind(..) will\n";
  cout<<"\t return the postion of the last delimiter of that type. For example, in '/bp/kp/bp/kp.adhikari\n";
  cout<<"\t if the delimiter '/' is used in rfind, it will return '9', because the first, second and third/last \n";
  cout<<"\t back slashes come after the 9th character postion.";
  cout<<"====== Done testing 'string::npos' and related things ====\n\n"<<endl;


  string ext = getFileExt(path);
  string fnm = getFileName(path);
  std::cout << "The extension is \"" << ext << "\"\n";
  cout << "The filename without extension is: "<< fnm << endl;
}

/*
  Discussion

  To get an extension from a filename, you just need to find out where the last dot “.” is and take everything to the right of that. The standard string class, defined in <string> contains functions for doing both of these things: rfind and substr.

  rfind will search backward for whatever you sent it (a char in this case) as the first argument, starting at the index specified by the second argument, and return the index where it was found. If the pattern wasn’t found, rfind will return string::npos. substr also takes two arguments. The first is the index of the first element to copy, and the second is the ...
*/

/*
  http://www.cplusplus.com/reference/string/string/npos/

  public static member constant
  <string>
  std::string::npos

  static const size_t npos = -1;

  Maximum value for size_t
  npos is a static member constant value with the greatest possible value for an element of type size_t.

  This value, when used as the value for a len (or sublen) parameter in string's member functions, means "until the end of the string".

  As a return value, it is usually used to indicate no matches.

  This constant is defined with a value of -1, which because size_t is an unsigned integral type, it is the largest possible representable value for this type.
*/

/*
  https://www.cplusplus.com/reference/string/string/substr/
  std::string::substr

string substr (size_t pos = 0, size_t len = npos) const;

Generate substring
Returns a newly constructed string object with its value initialized to a copy of a substring of this object.

The substring is the portion of the object that starts at character position pos and spans len characters (or until the end of the string, whichever comes first).

Parameters

pos
    Position of the first character to be copied as a substring.
    If this is equal to the string length, the function returns an empty string.
    If this is greater than the string length, it throws out_of_range.
    Note: The first character is denoted by a value of 0 (not 1).
len
    Number of characters to include in the substring (if the string is shorter, as many characters as possible are used).
    A value of string::npos indicates all characters until the end of the string.


size_t is an unsigned integral type (the same as member type string::size_type).

Return Value
A string object with a substring of this object.
 */
