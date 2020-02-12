#include <iostream> 
#include <chrono> 
// #include <opencv2/opencv.hpp>
// #include "TestClass.h"
#include "Camera.h"

using namespace std;
using namespace std::chrono; 


int main()
{   
    auto start = high_resolution_clock::now(); 
    Camera camera_m;
    if(camera_m.initCamera()){cout<<"Success\n";}
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << duration.count() << " milliseconds" <<  endl; 

    return EXIT_SUCCESS;
}
