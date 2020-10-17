/*
Author: Rachael Judy
Date: 10/16/2020
Purpose: Specification for steganography class - meant to be handled entirely in 
			constructor by providing message/output direction
			Creation involves providing the direction, image, new image, and 
			form of i/o for this op
Credits: Using code from lodepng

*/

#ifndef STEG_H
#define STEG_H

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

#include "lodepng.h"

class Steg {
public:
	Steg(std::string image, bool encode, std::string newImage, std::string txt = "");
	void decode();
	void encode();

private:
	void decodeImage();
	void insertMsg();
	void extractMsg();
	void encodeToImage();

	unsigned width, height;
	// input file, message content
	std::string txtfile, msg;
	// image to work with, new image name for encoding
	std::string ogImg, newImg;
	// vector of RGBA content
	std::vector<unsigned char> image;
	// direction to go with image
	bool toEncode;

};

#endif // !STEG_H