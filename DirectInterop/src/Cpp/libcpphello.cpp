#include <iostream>

using namespace std;

extern "C" int hello_from_cpp(){
	
	char hello[] = "Hello from C++! As a simple function";
	std::cout << endl << hello << endl;
    
	return 0;
}
