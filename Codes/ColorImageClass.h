#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include "constant.h"
#include "ColorClass.h"
#include "MsgClass.h"

// Programmer: Hongrui Liu, Mar 14 2021. 
// This is the header file of the ColorImageClass. 
// An object of ColorImageClass stores an image as a dynamic 2D array. 
// Every elements in the array is an object of ColorClass.
// It has some member functions which can operate on the whole image such as 
//   encoding, decoding, reding from and writing to files.

class ColorImageClass
{
private:
  ColorClass ** imageMatrix;      // Define the dynamic 2D array
  int rowInput;             // Store the size information of the ppm file
  int columnInput;

public:

  // Constructor
  ColorImageClass();
  
  // Return the size information of the image
  int getRow();
  int getCol();

  // This function open the ppm file and read the image information.
  // It stores the image in a ColorImageClass object and check all possible 
  //   errors.
  // If the function fails to the input ppm file, the program will exit with a 
  //   specific return value other than zero.
  // And an informative message will show the exact error.
  int readColorImage(string fileName);
  
  // This function performs encoding for the whole image by modifying each 
  //   pixel according to the encoding message file.
  // It will not directly operate on the rgb values of a single pixel.
  // Instead, it calls a function in the ColorClass to finish this job.
  // When encoding a message, the user may request a position of the message 
  //   within the image that causes some or all of the encoded message to be 
  //   ¡°out of bounds¡± in the original image. 
  // If this happens, this function will encode the message for the pixels that 
  //   are ¡°in bounds¡± and do nothing for the ones that are ¡°out of bounds¡±.
  void encodeImg(const int rowPlcmt, const int colPlcmt, const int rowMsg, 
                 const int colMsg, MsgClass msg);

  // This function performs decoding for the whole image by modifying each 
  //   pixel according to the inverse of the encoding message file.
  // It will not directly operate on the rgb values of a single pixel.
  // Instead, it calls a function in the ColorClass to finish this job.
  void decodeImg();

  // This function write the current ColorImageClass object (image) to a ppm
  //   file with all necessary components.
  // It produces one pixel element at a time, and the function of ColorClass 
  //   will convert that information to rgb values which can be write to files.
  void writeToFile(string fileName);

  // This function deletes the dynamic 2D array and frees the memory.
  // Did not use in this project.
  // Save for later
  void deleteImg();
}; 



#endif
