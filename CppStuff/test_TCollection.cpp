//https://www.codeproject.com/Articles/6381/Creating-a-Collection-Class-in-C
/*
Creating a Collection Class in C++


fyrewolfe

Rate this:
	2.11 (9 votes)

8 Mar 2004
How to use a template to create a custom collection class and using the C++ std::vector STL library as well as the operator. I will expect you to understand how pointers, classes, templates and the operator works.
Introduction

C++ comes with its own set of containers in the STL (Standard Template Libraries) libraries; (e.g. std::vector). It is always best to use these containers over writing your own since the C++ designers have gone to great lengths to insure performance.
Why a collection class?

"A collection class is a container class that holds one or more items of a certain type"

Say for example I want to develop a game where there is a board with 9 buttons. Each button will have a status of on or off. Each button is located on a specific x,y position on the board and is of a certain color depending on the status and player that clicked on the button. The figure below show the board with nine buttons.

Image 1
Figure.1.

On the code side I will thus have a board class containing a collection of buttons. The figure below shows a UML representation of the board class.

Image 2
Figure.2.

The collection class will allow us to have access to each button as well as that button’s properties and functions (e.g status , x and y position, color).

Ok lets get coding.
The Code

The code for the collection class is fairly simple. If you understand how pointers, classes, templates and the operator works, then you are already 90% there. The only thing left is for you to bring these technologies together and “voila!” you will have your collection class.

In your favorite C++ compiler, create a new win32 project and a header file. I called mine “TCollection.h”.

Then add the following line of code to the header:

#include <span class="code-keyword"><vector></span>
using namespace std;
//This simply includes the vector container from the STL.
//Next we create the template class:
template <class TBase>class TCollection{
};

After the template class is created, we first add the protected vector member. Protected because we want the member to be available to classes derived from the collection class.

template <class TBase>
class TCollection
{
  protected:
  //The Vector container that will hold the collection of Items
  vector<TBase> m_items;
};

There are basically three things we want to do to our container: Add an Item, Remove an Item and Clear the Container. We also want to know how many items are in the container and for that we will need a Count() function. All of the functions will be public.
The Add() Function

Because we already know that we want to add items of type TBase to the container, we simply declare and define an Add() function:

int Add(void)
{
  //Create a new base item
  TBase BaseItem;
  //Add the item to the container
  m_items.push_back(BaseItem);
  //Return the position of the item within the container.
  //Zero Based
  return (m_items.size()-1);
}

The Remove() function

For the Remove() function we will need to declare and define a function that will return a pointer to the item to be removed. This is so because our vector container’s erase function requires a pointer to be able to remove an item.

//Function to return the memory address of a specific Item
TBase* GetAddress(int ItemKey)
{
  return &(m_items[ItemKey]);
}

It is always best to program defensively, but for the purpose of this article I didn’t do that because I want to show the principle behind the collection class. E.g. you can test whether the Item really exist in the container before returning it’s address.

Now that we have our GetAddress() function we can continue to our remove function.

void Remove(int ItemKey)
  //Remove a specific Item from the collection
{
  //Remove the Item using the vector’s erase function
  m_items.erase(GetAddress(ItemKey));
}

The Clear() Function

The Clear function is fairly simple:

void Clear(void) //Clear the collection
{
  m_items.clear();
}

The Count() function

The Count function is also very simple:

//Return the number of items in collection
int Count(void)
{
  return m_items.size(); //One Based
}

Note that the number returned is one based. This mean that to access the last item in the collection you will have to use Count()-1.

Now that we have all our functions we only have to do one more thing. We want to gain access to an Item by using the [] braches. We do that by using operator overloading.
The operator []

We want the operator to return a reference to our base item. Remember that the base item is of type TBase.

//Operator Returning a reference to TBase
TBase& operator [](int ItemKey)
{
  return m_items[ItemKey];
}

Our collection class is now done. See the whole file below.

The header file:

*/

#include <iostream>
#include<string>
//TCollection.h
//#include <span class="code-keyword"><vector></span> //kp disabled
#include <vector> //kp added
using namespace std;

template <class TBase>
class TCollection
{
protected:
  //The Vector container that will hold the collection of Items
  vector<TBase> m_items;
public:
  int Add(void)
  {
    //Create a new base item
    TBase BaseItem;
    //Add the item to the container
    m_items.push_back(BaseItem);
    //Return the position of the item within the container.
    //Zero Based
    return (m_items.size()-1);
  }
  //Function to return the memory address of a specific Item
  TBase* GetAddress(int ItemKey)
  {
    return &(m_items[ItemKey]);
  }
  //Remove a specific Item from the collection
  void Remove(int ItemKey)
  {
    //Remove the Item using the vector’s erase function
    m_items.erase(GetAddress(ItemKey));
  }
  void Clear(void) //Clear the collection
  {
    m_items.clear();
  }
  //Return the number of items in collection
  int Count(void)
  {
    return m_items.size(); //One Based
  }
  //Operator Returning a reference to TBase
  TBase& operator [](int ItemKey)
  {
    return m_items[ItemKey];
  }
};

//#include <windows.h>
int main()
{
  vector <int> vInt; //kp:
  //cout<<"vInt[0] = "<<vInt[0]<<endl; //kp: gives segfault
  vInt.push_back(3); //kp: If we don't have at least one push_back() call, it gives us a segmentation fault.
  cout<<"vInt[0], [1] = "<<vInt[0]<<", "<<vInt[1]<<endl;

  TCollection<string> ColClass; //Create a collection of strings
  int i = ColClass.Add();
  ColClass[i] = "Hello";
  i = ColClass.Add();
  ColClass[i] = "Krishna";
  ColClass.Add();
  //MessageBox(NULL, ColClass[i].c_str(),"",MB_OK);
  cout<<"ColClass[i-1].c_str() = "<<ColClass[i-1].c_str()<<endl;
  cout<<"ColClass[i].c_str() = "<<ColClass[i].c_str()<<endl;
  cout<<"ColClass[i+1].c_str() = "<<ColClass[i+1].c_str()<<endl;
  cout<<"ColClass[i+2].c_str() = "<<ColClass[i+2].c_str()<<endl; //No error
  cout<<"ColClass[i+100].c_str() = "<<ColClass[i+100].c_str()<<endl; //No error
  return(0);
}
/*

  Testing the collection class

We test the collection class by creating a winmain.cpp file that includes our TCollection.h file.

#define WIN32_MEAN_AND_LEAN
//Normal win32 headers
#include <span class="code-keyword"><windows.h> </span>
#include <span class="code-keyword"><windowsx.h></span>
//---------------------
//The collection class header
#include <span class="code-string">"TCollection.h"</span>
//The string class
#include <span class="code-keyword"><string></span>
using namespace std;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
char * cmdParam, int cmdShow)
{
TCollection<string> ColClass; //Create a collection of strings
int i = ColClass.Add();
ColClass[i] = "Hallo";
MessageBox(NULL, ColClass[i].c_str(),"",MB_OK);
return(0);
}

As can be seen from the above code, I created a new collection of strings, add an item and then accessed that item and its properties. We now have a collection class that can take any type. No fuss…

Take for example if I use an int for my collection class:

char buffer[20];
TCollection<int> ColClass2;
int j = ColClass2.Add();
ColClass2[j] = 3;
sprintf(buffer,"Item %d = %d",j, ColClass2 [j]);
MessageBox(NULL,buffer,"",MB_OK);

ToDo

Create a CBoard and CButton class as previously in this article. Add nine buttons to the board, set the properties of each button and then loop through each button and display it’s properties.
License

This article has no explicit license attached to it but may contain usage terms in the article text or the download files themselves. If in doubt please contact the author via the discussion board below.

A list of licenses authors might use can be found here
*/
