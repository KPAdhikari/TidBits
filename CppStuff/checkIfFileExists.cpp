//#include "/u/home/adhikari/LinkedFiles/myOwnHeaderFiles.h"
//#include "/u/home/adhikari/LinkedFiles/checkIfFileExists.h"
//#include "/u/home/adhikari/LinkedFiles/someFreqFuncs4h1h10processing.h"
#include <iostream>
#include <sys/types.h>
//#include <sys/stat.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


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



//void MakeTable4SignalCableDelay();
int main(int argc, char **argv)
{
  //gStylesKP("ne");
  char *fName; //[200];
  if(argc<2)
    {
      cout<<"\t Usage: "<<endl<<"\t\t exe < ... path .../filename >"<<endl<<endl;
      //cout<<"\t\t Table4What=0 - create table for Signal Cable Delays\n";
      return -1;
    }
  fName=argv[1];  //Table4What=atoi(argv[1]);

  int fEx=0; fEx=fileExists(fName);
  cout<<"Function fileEixts(filename) says the file does ";
  if(fEx==1) cout<<"exist.\n"; else cout<<"not exist.\n";

  time_t rawtime; time ( &rawtime );  printf ( "The current local time is: %s", ctime (&rawtime) );//Time Tracker
  return 0;
}




//6/7/15: http://stackoverflow.com/questions/13945341/c-check-if-a-file-exists-without-being-able-to-read-write-possible
/*
fopen actually tries to open the file, which you can't do if you don't have read access. In order to check whether the file exists without opening it, use stat; stat gives you metadata about the file, and requires only read access to the directory containing the file, not the file itself.
You could get fancier by checking errno if result is not 0; if errno is ENOENT then the file does not exist, if it is ENOTDIR then part of the path you provided is not a directory, if it's EACCESS then you didn't have read permission on one of the directories in the path and so stat can't give you an answer, and so on.

Also, be aware that if you're on a platform with symlinks (any Unix-like, or Windows Vista or later), that you should be aware of whether you are querying about the symlink or the file it points to. If you call stat, then you are asking about the file it points to; if you have a symlink dir/link which points to other/file, then stat will return results about other/file (which is usually what you want, since that's what you would get if you opened the file). However, if you are curious about the link itself (if you want to know "does dir/link exist, even if other/file does not?"), then you should use lstat().

stat() works on Windows as a compatibility wrapper (they prefer you use _stat(), and will warn if you don't), but it's generally better to use the native platform APIs. On Windows, you should probably use GetFileAttributes():


*/

/*
int doesFileExist(const char *filename)
{
    struct stat st;

    //error: 'int stat(const char*, stat*)' redeclared as different kind of symbol
    //error: previous declaration of 'Char_t stat [20]'

    int result = stat(filename, &st);
    return result == 0;
}



int doesFileExistFancier(const char *filename) {
    return GetFileAttributes(filename) != INVALID_FILE_ATTRIBUTES;
}
*/
