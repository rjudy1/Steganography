The Steganography Program

Usage
Run steg with either of these commands to encode or decode respectively. The program will take the input image and input text, place the text in the image, and then write it to the modified name. It will let you know if you use an invalid input file. If you attempt to decode an image without a message, it will take a while to read the whole image looking for the terminator. If you use the decode, it will take the image and write to specified output the message contained within. It verifies there are at least two additional arguments and that input files exist, displaying an appropriate error if not. The images must be pngs.

 steg -e <original image name> <modified image name> [input ASCII text file name]
 steg -d <modified image name> [output ASCII text file name]

Build
To build the program, use g++ main.cpp steg.cpp lodepng.cpp -o steg. Alternatively, place all the files in Visual Studio and build from there. The executable is provided
