#include <iostream> 
#include <vector> 

#include "TestClass.h"

using namespace std;

TestClass::TestClass()
{   
    cout<< "setting up the test  class" <<endl;
    rand_num = 10;
}
TestClass::~TestClass()
{
    cout<< "calling destructors" <<endl;
}

void
TestClass::text_print(int &num)
{
    for (int i = 0; i < num; i++)
    {
        cout<< "random number is: " << rand_num <<endl;
    }
   
}