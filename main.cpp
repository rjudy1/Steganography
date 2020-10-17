/*
Author: Rachael Judy
Date: 10/17/2020
Purpose: Encode and decode some text in images provided by cmd line arguments

Attribution: used lodepng libraries from LodePNG to decode and encode images
				with Steg class
*/


#include <cstring>
#include <iostream>
#include <string>

#include "Steg.h"

using namespace std;

void printUsage() {
	cout << " steg -e <original image name> <modified image name> [input ASCII text file name]\n"
		<< "steg - d <modified image name> [output ASCII text file name]"
		<< endl;
}


int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Too few arguments" << endl;
		printUsage();
		return 1;
	}

	// encode or decode
	string directionED = argv[1];
	string imageToDecode = argv[2];
	string newImage;
	string textFile;

	if (directionED == "-e") {
		if (argc == 4) { 
			Steg encoder = Steg(argv[2], true, argv[3]);
		}
		else if (argc == 5) { // includes text file
			Steg encoder = Steg(argv[2], true, argv[3], argv[4]);
		}
	}
	else if (directionED == "-d") {
		if (argc == 4) {
			Steg decoder = Steg(argv[2], false, "", argv[3]);
		}
		else {
			Steg decoder = Steg(argv[2], false, "");
		}
	}
	else {
		printUsage();
		return 2;
	}
}