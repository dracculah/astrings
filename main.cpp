#include <iostream>
#include "AString_Tester.h"

using namespace std;

int main(int argc, char** argv) 
{   
    AString_Tester test;
    if (test.run_tests())
        cout << "All tests were OK!" << std::endl;
            
    return 0;
}