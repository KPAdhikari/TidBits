#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream> //this and the following line required for cout, cin etc. (otherwise, it's basically C)
//#include "/u/home/adhikari/LinkedFiles/myOwnHeaderFiles.h"
//https://www.jlab.org/Hall-B//secure/eg4/adhikari/myHomeLinked/MyHm/RadCorr/RCSLACPOL_STEG/SingleProg2Stage/TestExe/createNsubJobs4rcslacpolStegPassVarsFrmMain.C

#include <dirent.h> //Needed for the following function which is fully defined at the bottom

//#include <iostream>
#include <sys/types.h>
//#include <sys/stat.h>
#include <sys/stat.h>
//#include <stdio.h>
//#include <stdlib.h>


using namespace std;


int fileExists(const char *filename)
{
  int truth=0;
  //http://bytes.com/topic/c/answers/215642-good-way-checking-if-file-exists
  //A standard C compatible way could be:

  FILE *fp = fopen(filename,"r");
  if( fp )
    {
      truth=1;
      // exists
      fclose(fp);
    }
  //else {   }// doesnt exist
  return truth;
}


int main(int argc, char **argv)
{
  int forWhat, testOrAna;
  int whExe=1;
  /*
  char *ext, *jobNmStr;
  if(argc<2) //If 1, no extra argument, just the executable name i.e., run as ./exe
    {
      cout<<endl<<"\t This program is used to submit basically three types of jobs (to the Jlab batch farm) "<<endl

      return -1;
    }
  forWhat=atoi(argv[1]);

  char cstr[200]; ext = argv[argc-1];
  sprintf(cstr,"\t Just for test.%s.%c.%c.%c ",ext,ext[0],ext[1],ext[2]);
  cout<<"\t argc="<<argc<<" "<<cstr<<ext<<endl<<endl;

  if(forWhat==0 && argc<11) //8/19/13 (adding jobNmStr)
    {
      system("tput bold"); system("tput setaf 4"); //Bold & Red //http://linuxtidbits.wordpress.com/2008/08/11/output-color-on-bash-scripts/ //Bold
      cout<<"Usage: exe <int forWhat> <int testOrAnalysis> <int HowManyJobs> <int: jobHours> <int WbinsFactor>  <int Q2binCase>"<<endl
      system("tput sgr0"); // Reset
      return -1;
    }

  int GppHow=0, EventNum=70000; //12/8/12, 1/16/13

  ext = argv[argc-3]; jobNmStr = argv[argc-2]; SubJobNowOrNot=atoi(argv[argc-1]);   //8/19/13 (adding jobNmStr)
  */



  /*
    https://stackoverflow.com/questions/26401051/run-2-or-more-cmd-command-using-system-in-c
    The cd command used in the system() call will change the directory only for the sub shell opened, not for
    your actual process. – πάντα ῥεῖ Oct 16 '14 at 9:41

    You need to put both steps in one system() command and how that is done will be platform depe
    ndant. – Galik Oct 16 '14 at 9:42

   */

  system("pwd");
  system("cd .."); //didn't work  (read above comment by πάντα ῥεῖ), we have to use all commands together.
  cout<<"After a separate system(\"cd ..\")\n"<<endl;
  system("pwd");
  cout<<"=====\n";
  system("cd ..; pwd; ls");
  cout<<"=====\n";
  cout<<"Above lines between ===== are produced by system(\"cd ..; pwd; ls\").\n"<<endl;
  system("pwd");
  system("cd /Users/kpadhikari/GitProj/KPAdhikari/TidBits/; pwd; ls"); //works

  system("pwd");   system("ls");
  //system("cd ./CppStuff"); //Didn't work
  system("cd /Users/kpadhikari/GitProj/KPAdhikari/TidBits/CppStuff");
  system("pwd");
  system("ls");


  //gStylesKP("ne"); //In rootHeaderFiles.h"

  int checkDir = fileExists("TmpDir");
  if(checkDir == 0) system("mkdir TmpDir");
  system("cp cppHelloWorld.cpp ./TmpDir/; cd TmpDir; g++ -o cppHelloworld cppHelloworld.cpp; ./cppHelloWorld;  pwd");
  system("pwd");
}
