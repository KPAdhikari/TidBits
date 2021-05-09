//kp: It appears, the string class doesn't have a method for word count, so I googled (4/23/21)
// Example program
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
/*
//http://www.cplusplus.com/forum/general/30929/ 
//def countWords(str: String) = str.split("\\s+").size

#include <vector>
#include <string>
#include <boost/algorithm/string/split.hpp>
*/

using namespace std;

int count_words( string s ) {
    int word_count( 0 );
    stringstream ss( s ); //needs '#include <sstream>'
    string word;
    while( ss >> word ) ++word_count;
    return word_count;
}
/*
size_t word_count(std::string s)
{
	return s.empty() ? 0 : std::count_if(std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))), std::unique(s.begin(), s.end()), std::ptr_fun<int, int>(std::isspace)) + !std::isspace(*s.rbegin());
}

int countWords(std::string str) {
  vector< std::string > result;
  boost::algorithm::split_regex(result, str, regex( "\\s+" ));
  return result.size();
}
*/
int main()
{
  std::string name;
  std::cout << "What is your name? ";
  getline (std::cin, name);
  std::cout << "Hello, " << name << "!\n";
  
  string sentence = "What the hell is that?";
  //cout<<sentence.split("\\s+").size <<endl;
  cout<<count_words(sentence)<<endl;
  cout<<count_words("K. P. Adhikari")<<endl;
}
