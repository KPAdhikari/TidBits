#include "myHeaders.h"
#include "/u/home/adhikari/LinkedFiles/myOwnHeaderFiles.h"
#include "/u/home/adhikari/LinkedFiles/someFns4_Q2_W_etc.h"
//Lund format information: https://gemc.jlab.org/gemc/html/documentation/generator/lund.html

using namespace std; //kp: 11/19/20

//#include "/u/home/adhikari/LinkedFiles/checkIfFileExists.h"

std::string ReadNthLine(const std::string& filename, int N);

void DrawPlots();
int main(int argc, char **argv)
{
  //gStylesKP("ne");
  char *fName; //[200]; 
  if(argc<4) 
    {
      cout<<"\t Usage: "<<endl;
      cout<<"\t\t exe <filename>  <eventNum: max # of events per file>  <linesInEachEventIncludingHeader>"<<endl;
      cout<<"\t\t\t for example there were 23 lines for each event in the lund file ep_34118_20.lund.\n";
      cout<<"\t\t\t because one is for header and 22 lines - one each for 22 particles of the event.\n";
      //cout<<"\t\t Table4What=0 - create table for Signal Cable Delays\n";
      return -1;
    }

  fName=argv[1];  //Table4What=atoi(argv[1]);  
  int eventNum = atoi(argv[2]),  linesInEachEvent = atoi(argv[3]);
  //string strN = ReadNthLine(fName, lineNum); cout<<endl<< strN <<endl;

  //After defining and adding a new header (to myOwnHeaderFiles.h) that processes a filename (5/9/21)
  string fExt = getFileExt(fName); //fName can have path too
  string fStem = getFileName(fName); //fName can have path too

  //http://www.cplusplus.com/reference/string/string/getline/
  //https://www.cplusplus.com/reference/string/string/reserve/
  //http://www.cplusplus.com/reference/istream/istream/seekg/
  //std::ifstream file ("test.txt",std::ios::in |std::ios::ate);
  std::ifstream file (fName);
  if (file) {
    cout<<"Hello ..., I am opening a file named "<<fName<<endl;
    std::ifstream::streampos filesize = file.tellg(); cout << "The filesize is "<<filesize <<endl;
    /*
    str.reserve(filesize);    file.seekg(0);
    while (!file.eof()) { str += file.get();  }      std::cout << str;
    */
  }

  ofstream kpout; 
  
  char newFile[50] = "file_00.lund";
  int maxEvtsPerFile = eventNum; //5;
  int lN = 0, fN=0, pfN = -1; //line #, new file number, previous file number.
  ifstream inFile;
  string lineFromFile;
  //istringstream is("llllnnn");
  //inFile.open("file1_forDiff_y.txt");
  //inFile.open("test_lund_file.txt");
  inFile.open(fName);
  while( !inFile.eof() )
    {
      getline( inFile, lineFromFile );
      fN = lN/(linesInEachEvent*maxEvtsPerFile);

      if(fN > pfN) {
	cout<<"Closed file #"<<pfN<<" and opened a new one i.e. file #"<<fN<<" \n";
	//sprintf(newFile,"ep_34118_20_ev%02dk_file%02d.lund",(maxEvtsPerFile/1000), fN);
	sprintf(newFile,"%s_ev%02dk_file%02d.lund",fStem.c_str(),(maxEvtsPerFile/1000), fN);
	if(kpout.is_open()) kpout.close(); //Close the previously opened file
	if(!lineFromFile.empty()) kpout.open(newFile,ios_base::out);   //Now open a new file; 
	//Above if-block to avoid last empty line creating a last empty file
	pfN = fN;
      }
      if(!lineFromFile.empty()) //To avoid the last empty line (which could exist in a file)
	{
	  //cout<<lineFromFile<<" line#: "<<lN<<", file#: "<<fN<<", prev. file#: "<<pfN<<endl;
	  kpout<<lineFromFile<<endl;
	}
      
      lN++;
    }
  if(kpout.is_open()) kpout.close(); //Close the last file that was opened

  //https://gemc.jlab.org/gemc/html/documentation/generator/lund.html
  double particleArr[14]; //Lund particle is defined by 14 different numbers as follows:
  //      (partIndex, lifetime, type (1 is active), PID, parentIndex, daughterIndex, px, 
  //      py, pz (GeV/c), Energy (GeV), mass (GeV), vx, vy, vz (cm))
  int initLine = linesInEachEvent  * (eventNum - 0); // (eventNum - 1);

  int some_reasonable_max_line_length = 10000; //400;
  std::ifstream in(fName); cout << in <<endl;
  cout<<"Event #: "<<eventNum<<endl;
  if (in) {
    std::string s;
    //for performance
    s.reserve(some_reasonable_max_line_length);    

    //skip N lines
    //for(int i = 0; i < initLine; ++i)      std::getline(in, s);

    //Now getting and printing the Nth line
    //std::getline(in,s); cout << s << endl<<endl;
    
    //Finally getting and printing the next NN lines
    int NN = linesInEachEvent;
    int nEvt2Process = eventNum;
    double pp = 0.0;
    for(int i = 0; i < nEvt2Process*NN; ++i)
      {
	std::getline(in, s); //cout << s <<endl; //if (i > 2) break;
	
	//if( (i % NN) == 0 || (i % NN) > 2) continue;  //cout<< s <<endl;
	if( (i % NN) == 0 ) continue;  //skip only the header

	//https://www.cs.auckland.ac.nz/~mjd/prog_contest/www.cppreference.com/string/getline
	istringstream ss(s); 
	int k=0; double d;
        while( ss >> d ) {
          //cout << "  got a number: " << d << endl;
	  particleArr[k] = d; k++;
        }
	
	pp = sqrt(pow(particleArr[6],2) + pow(particleArr[7],2) + pow(particleArr[8],2));
	//cout<<"px, E, vz: "<<particleArr[6]<<", "<<particleArr[9]<<", "<<particleArr[13]<<endl;
	//if( (i % NN) == 0 || (i % NN) > 2) continue;  cout<< s <<endl;
	if( (i%NN) == 1 ) //primary electron
	  {

	  }
	else if( (i%NN) == 2 ) //coincidental proton
	  {
	    //h1pXpp->Fill(particleArr[6]); h1pYpp->Fill(particleArr[7]); h1pZpp->Fill(particleArr[8]);
	    
	  }
	else //random protons
	  {
	    
	  }
      }

  }
  

  time_t rawtime; time ( &rawtime );  printf ( "\n\n The current local time is: %s", ctime (&rawtime) );//Time Tracker
  return 0;
}



//https://stackoverflow.com/questions/7273326/getting-the-nth-line-of-a-text-file-in-c
//Answer by: Armen Tsirunyan
//How about this?
std::string ReadNthLine(const std::string& filename, int N)
{
  int some_reasonable_max_line_length = 1000; //400;
  std::ifstream in(filename.c_str());

  std::string s;
  //for performance
  s.reserve(some_reasonable_max_line_length);    

  //skip N lines
  for(int i = 0; i < N; ++i)
    std::getline(in, s);

  std::getline(in,s);
  return s; 
}

/*

//Answer by David Nehme
//If you want to read the start of the nth line, you can use stdin::ignore to skip over the first n-1 lines, then read from the next line to assign to the variable.

template<typename T>
void readNthLine(istream& in, int n, T& value) {
  for (int i = 0; i < n-1; ++i) {
    in.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  in >> value;
}

//Answer by: Mooing Duck
//      Response: Clever. This is the best solution IMO.
//Armen's solution is the correct answer, but I thought I'd throw out an alternative, based on jweyrich's caching idea. For better or for worse, this reads in the entire file at construction, but only saves the newline positions (doesn't store the entire file, so it plays nice with massive files.) Then you can simply call ReadNthLine, and it will immediately jump to that line, and read in the one line you want. On the other hand, this is only optimal if you want to get only a fraction of the lines at a time, and the line numbers are not known at compile time.
class TextFile {
    std::ifstream file_stream;
    std::vector<std::ifstream::streampos> linebegins;
    TextFile& operator=(TextFile& b) = delete;
public;
    TextFile(std::string filename) 
    :file_stream(filename) 
    {
        //this chunk stolen from Armen's, 
        std::string s;
        //for performance
        s.reserve(some_reasonable_max_line_length); 
        while(file_stream) {
            linebegins.push_back(file_stream.tellg());
            std::getline(file_stream, s);
        }
    }
    TextFile(TextFile&& b) 
    :file_stream(std::move(b.file_stream)), 
    :linebegins(std::move(b.linebegins))
    {}
    TextFile& operator=(TextFile&& b) 
    {
        file_stream = std::move(b.file_stream);
        linebegins = std::move(b.linebegins);
    }
    std::string ReadNthLine(int N) {
        if (N >= linebegins.size()-1)
            throw std::runtime_error("File doesn't have that many lines!");
        std::string s;
        // clear EOF and error flags
        file_stream.clear();
        file_stream.seekg(linebegins[N]);
        std::getline(file_stream, s);
        return s;
    }
};


//Answer by Gian:
//It's certainly possible. There are (n-1) '\n' characters preceding the nth line. Read lines until you reach the one you're looking for. You can do this on the fly without storing anything except the current line being considered.
*/
