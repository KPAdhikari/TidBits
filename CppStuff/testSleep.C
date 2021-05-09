#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
  for(int i=0; i<10; i++)
    {
      printf("Sleeping for 1 second.\n");
      system("sleep 1s");
    }
  return 0;
}
