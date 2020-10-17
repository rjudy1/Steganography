/*
Author: Rachael Judy
Date: 10/17/2020
Purpose: Implementation of Steg class specification 
			to allow for decoding and encoding messages
Credits: uses lodepng code for decoding and encoding of png to vectors

*/

#include "Steg.h"

using namespace std;

// constructor takes name of image to either encode or decode, direction to go (encode == true),
// new image name if going to encode, and optional text file name
Steg::Steg(std::string image, bool toEncode, std::string newImage, std::string txt) 
	: ogImg(image), txtfile(txt), newImg(newImage), toEncode(toEncode) {

	// boolean to know where to input/output
	bool useFile = (txt != "");
	if (toEncode) {
		cout << "Encoding..." << endl;
		if (useFile) {
			ifstream ifile(txtfile);
			// if something wrong with file, don't modify output
			if (!ifile.is_open()) {
				cout << "Error opening input file" << endl;
				cout << "Enter a message to encode: " << endl;
				std::getline(cin, msg);
			}
			else {
				// put file contents in msg
				std::stringstream strStream;
				strStream << ifile.rdbuf(); //read the file
				msg = strStream.str(); //str holds the content of the file
				ifile.close();
			}
		}
		// if not using file, get the message from the std input
		else {
			cout << "Enter a message to encode: " << endl;
			std::getline(cin, msg);
		}

		encode();
		cout << "The image was encoded to " << newImage << endl;
	}

	else {
		cout << "Decoding..." << endl;

		decode();

		// open and write to text file if using it, otherwise display only cout
		if (useFile) {
			// put output in text file
			ofstream ofile(txtfile);
			if (!ofile.is_open()) {
				cout << "Error opening output file. Message was: " << endl;
				cout << msg;
				return;
			}
			
			ofile << msg << endl;
			cout << "The message was placed in " << txtfile << endl;
			cout << "It contained the message:\n" << msg;
			ofile.close();
		}
		else {
			// put content in cout
			cout << msg;
		}
	}
}


// encode the message in the image
void Steg::encode() {
	decodeImage();
	insertMsg();
	encodeToImage();
}

// decode the message from the image
void Steg::decode() {
	decodeImage();
	extractMsg();
}


// decode image to its array RGBA form - uses code from the lodepng site
void Steg::decodeImage() {
	//decode
	unsigned error = lodepng::decode(image, width, height, ogImg);

	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image" of the class, 4 bytes per pixel, ordered RGBARGBA...
}


// modifies RGBA vector to produce modified encoded image vector
void Steg::insertMsg() {
	// set iterator for image and add a end of file character to msg for detection later
	vector<unsigned char>::iterator imgItr = image.begin();
	msg.push_back(0x03);

	// iterate through each character in the message, inserting from MSB to LSB
	// to LSB of the image vector
	for (auto& c : msg) {
		for (int bit = 0x80, shift = 7; bit > 0 && imgItr != image.end(); bit /= 2, shift--) {
			// shift to LSB and & with end
			*imgItr = (*imgItr & 0xFE) | ((c & bit) >> shift); 
			imgItr++;
		}
	}
}


// gets the encoded message from the RGBA vector, looking at LSB for terminator character
void Steg::extractMsg() {
	msg = "";
	unsigned char c = 0x00;
	vector<unsigned char>::iterator imgItr = image.begin();

	// go through until terminator character is found
	// taking each bit and shifting into place
	while (c != 0x03) {
		c = 0x00;
		for (int shift = 7; shift >= 0 && imgItr != image.end(); shift--) {
			c = c | ((*imgItr & 0x01) << shift);
			imgItr++;
		}
		msg.push_back(c);
	}

	// drop the terminator
	if (imgItr != image.end()) {
		msg.pop_back();
	}
}


// returns image vector back to image form
void Steg::encodeToImage() {
	//Encode the image
	unsigned error = lodepng::encode(newImg, image, width, height);

	//if there's an error, display it - from lodepng
	if (error) {
		std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
}