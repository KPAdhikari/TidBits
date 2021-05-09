/*
I started this file from the example in http://www.cplusplus.com/reference/map/map/cend/
and then tried it online by clicking on 'Edit & Run', which opened the code in http://cpp.sh/
and I could test it right there, without any hassles of compiling like in linux terminal.

The online test gave me the following output:
############ online test output #########
 True:  mymap.cend()->first = 
('a' != mymap.cend()->first) = 1
(next(mymap.cbegin(),3) == mymap.cend()) = 1
(next(mymap.cbegin(),7) == mymap.cend()) = 1
(next(mymap.cbegin(),7) != mymap.cend()) = 0
mymap.cbegin()->first/second a/200
next(mymap.cbegin(),1)->first/second b/100
next(mymap.cbegin(),2)->first/second c/300
next(mymap.cbegin(),3)->first/second /0
next(mymap.cbegin(),7)->first/second /0
mymap contains: [a:200] [b:100] [c:300]
#############

I also tested it in ifarm1802 of JLab CUE system. Here I had to compile it with the -std=c++11
option like 'g++ -std=c++11 -o map_cbegin_cend_first_second_next map_cbegin_cend_first_second_next.cpp'
else, it produced lots of errors.
The output on the ifarm1802 was as follows:
################# ifarm1802 output #######
ifarm1802.jlab.org> ./map_cbegin_cend_first_second_next 
 True:  mymap.cend()->first = 
('a' != mymap.cend()->first) = 1
(next(mymap.cbegin(),3) == mymap.cend()) = 1
(next(mymap.cbegin(),7) == mymap.cend()) = 1
(next(mymap.cbegin(),7) != mymap.cend()) = 0
mymap.cbegin()->first/second a/200
next(mymap.cbegin(),1)->first/second b/100
next(mymap.cbegin(),2)->first/second c/300
next(mymap.cbegin(),3)->first/second /0
next(mymap.cbegin(),7)->first/second /0
mymap contains: [a:200] [b:100] [c:300]
ifarm1802.jlab.org> 
#################


From (Source: https://stackoverflow.com/questions/10363646/compiling-c11-with-g)
To compile c++11 with g++:
	g++ -std=c++11 your_file.cpp -o your_program 
		or
	g++ -std=c++0x your_file.cpp -o your_program


However, I had segmentation fault issues in latter part of the code, I guess due to the fact 
that my 'g++' compiler is really not doing c++11 compilation, although it seemed like it had.
##########
KPAd's FunPrompt $ g++ -o map_cbegin_cend_first_second_next map_cbegin_cend_first_second_next.cpp
map_cbegin_cend_first_second_next.cpp:28:8: warning: 'auto' type specifier is a C++11 extension [-Wc++11-extensions]
  for (auto it = mymap.cbegin(); it != mymap.cend(); ++it)
       ^
1 warning generated.
KPAd's FunPrompt $ ./map_cbegin_cend_first_second_next 
 True:  mymap.cend()->first = ?
('a' != mymap.cend()->first) = 1
(next(mymap.cbegin(),3) == mymap.cend()) = 1
Segmentation fault: 11
KPAd's FunPrompt $ g++ -std=c++11 -o map_cbegin_cend_first_second_next map_cbegin_cend_first_second_next.cpp
KPAd's FunPrompt $ ./map_cbegin_cend_first_second_next 
 True:  mymap.cend()->first = ?
('a' != mymap.cend()->first) = 1
(next(mymap.cbegin(),3) == mymap.cend()) = 1
Segmentation fault: 11
KPAd's FunPrompt $ g++ -std=c++0x -o map_cbegin_cend_first_second_next map_cbegin_cend_first_second_next.cpp
KPAd's FunPrompt $ ./map_cbegin_cend_first_second_next 
 True:  mymap.cend()->first = ?
('a' != mymap.cend()->first) = 1
(next(mymap.cbegin(),3) == mymap.cend()) = 1
Segmentation fault: 11
KPAd's FunPrompt $
*/

// map::cbegin/cend
#include <iostream>
#include <map>
using namespace std; //kp
int main ()
{
  std::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  if('a' != mymap.cend()->first) 
    cout << " True:  mymap.cend()->first = "<<mymap.cend()->first<<endl;
    
  cout<<"('a' != mymap.cend()->first) = "<<('a' != mymap.cend()->first) <<endl;
  cout<<"(next(mymap.cbegin(),3) == mymap.cend()) = "<< (next(mymap.cbegin(),3) == mymap.cend()) <<endl;
  cout<<"(next(mymap.cbegin(),7) == mymap.cend()) = "<< (next(mymap.cbegin(),7) == mymap.cend()) <<endl;
  cout<<"(next(mymap.cbegin(),7) != mymap.cend()) = "<< (next(mymap.cbegin(),7) != mymap.cend()) <<endl;
  
  cout <<"mymap.cbegin()->first/second "<<mymap.cbegin()->first<<"/"<<mymap.cbegin()->second<<endl;
  cout <<"next(mymap.cbegin(),1)->first/second "<<next(mymap.cbegin(),1)->first<<"/"<<next(mymap.cbegin(),1)->second<<endl;
  cout <<"next(mymap.cbegin(),2)->first/second "<<next(mymap.cbegin(),2)->first<<"/"<<next(mymap.cbegin(),2)->second<<endl;
  cout <<"next(mymap.cbegin(),3)->first/second "<<next(mymap.cbegin(),3)->first<<"/"<<next(mymap.cbegin(),3)->second<<endl;
  cout <<"next(mymap.cbegin(),7)->first/second "<<next(mymap.cbegin(),7)->first<<"/"<<next(mymap.cbegin(),7)->second<<endl;
  // print content:
  std::cout << "mymap contains:";
  for (auto it = mymap.cbegin(); it != mymap.cend(); ++it)
    std::cout << " [" << (*it).first << ':' << (*it).second << ']';
  std::cout << '\n';

  return 0;
}
