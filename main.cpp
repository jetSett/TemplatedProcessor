#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "processor.hpp"

/// \warning Ceci va être impossible à comprendre


using namespace std;


int main(int argc, char** argv)
{
	if(argc < 3){
		cerr << "Please use a valid number of arguments. <path> {i, d} [file]\ni for interactive mode, d for direct mode" << endl;
		return 1;
	}

	bool interative;
	if(string(argv[1]) == string("i"))
		interative = true;
	else if(string(argv[1]) == string("d"))
		interative = false;
	else
		cerr << "Please use a valid first argument. Accepted : i, d" << endl;

	try{
		Processor proc(argv[2]);
		proc.run(interative);
	}catch(std::string s){
		cerr << s << endl;
		return 1;
	}catch(std::exception e){
		cerr << e.what() << endl;
		return 1;
	}

    return 0;
}
