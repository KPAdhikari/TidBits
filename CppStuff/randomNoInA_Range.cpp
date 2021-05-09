//kp: 4/24/21

// Example program
#include <iostream>
#include <string>
#include <time.h>

using namespace std;
//https://stackoverflow.com/questions/686353/random-float-number-generation
double randMToN(double M, double N)
{
    //https://www.cplusplus.com/reference/cstdlib/rand/
    /* initialize random seed: */
    //srand (time(NULL)); //If we put this seeding here, it will always produce the same random #
    //To produce different rand. #, it should be called only once from the main(). (see below)

    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
}

int main()
{
    //https://www.cplusplus.com/reference/cstdlib/rand/
    /* initialize random seed: */
    srand (time(NULL)); //This should be called only once from the main() and not from anywhere else.

    for (int i=0; i<10; i++)
        cout<<randMToN(2.0, 10.0)<<endl;
}
