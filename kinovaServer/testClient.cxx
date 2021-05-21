// CPP program to illustrate *char 
#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string>
#include <string.h>
#include <math.h>

using namespace std; 
typedef struct
{
  //The 6 double values to be sent represent the following signals:
  double q1; 
  double q2; 
  double q3; 
  double q4; 
  double q5; 
  double q6; 
 
} KinovaMsgData_rec;
  
int main() 
{ 
    // pointer str points to const string literal "Hello". 
    // No need to declare size. 
   const char* str1 = "This is GeeksForGeeks"; 
  
    cout << str1 << endl; 
    KinovaMsgData_rec *data_rec = new KinovaMsgData_rec();
    data_rec->q1 = 10;
    // cout <<  << endl; 

    return 0; 
} 