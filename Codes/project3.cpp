#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

#include "ColorClass.h"
#include "constant.h"
#include "ColorImageClass.h"
#include "MsgClass.h"

// Programmer: Hongrui Liu, Mar 14 2021. 
// This program mainly operates on existing ppm files. It can encode the file 
//   by slightly changing the rgb value of each pixel in a specific way. Human
//   eyes cannot tell the difference, but with decoding message, the picture
//   will become completely different. In this way, people can use this program
//   to communicate in a confidential way that others will never know.
// There are four options:
// 1. Encoding: In this function, every pixel of the original picture will be 
//    modified according to the provided encoding message file. The encoding
//    messages convert all different color rgb to eight different colors by 
//    distinguishing their parity. The whole image and the encoding message 
//    will be stored in different objects.
// 2. Decoding: In this function, the program operate the file in an opposite 
//    way. It takes the picture and convert all pixels into that eight colors
//    by using the inversed encoding message. If there are some hidden messages
//    in the picture, it will display clearly after decoding.
// 3. Writing to a file: This function will allow users to write the stored 
//    image to a ppm file. It include all necessary components of a ppm file.
// 4. Exit: Simply exit the program.


int main(int argc, char* argv[])     // Include command line parameters
{
  int userChoice;
  bool isExit = false;
  int returnValue;
  bool isReaded = false;

  ColorImageClass imageMatrix;
  MsgClass msgMatrix;
  ifstream inFile;
  string imgFileName;
  string writeFileName;
  
  if (argc != CORRECT_INPUT)  //  command line parameters check
  {
    cout << "Usage: " << argv[FIRST_ITEM] << " <inputFileName.ppm>" << endl; 

    exit(USAGE_STATEMENT);
  }

  cout << "Reading initial image from: " << argv[SECOND_ITEM] << endl;
  
  imgFileName = argv[SECOND_ITEM];

  returnValue = imageMatrix.readColorImage(imgFileName); //Read the image file

  if (returnValue != NORMAL_RETURN_VALUE)
  {
    cout << "Image read successful: No" << endl;
    cout << "Error: While reading the image, an error was encountered. ";
    cout << "Exiting the program!" << endl; 
    exit(returnValue);
  }

  while (!isExit)         //Set the loop for the main functions
  {
    cout << ENCODE_IMAGE << ". Encode a message from file" << endl;
    cout << DECODE_IMAGE << ". Perform decode" << endl;
    cout << WRITE_IMAGE << ". Write current image to file" << endl;
    cout << EXIT_PROGRAM << ". Exit the program" << endl;
    cout << "Enter your choice: ";                   //Print the user's menu
    cin >> userChoice;

    if (cin.fail() || userChoice < ENCODE_IMAGE || userChoice > EXIT_PROGRAM) 
                                                 // Check input validity
    {
      cout << "Please input a valid choice (int type)" << endl;
      cin.clear();
      cin.ignore(IGNORE_LENGTH, '\n');          
    }
    else if (userChoice == ENCODE_IMAGE) 
    {
      if (msgMatrix.readMsg(imageMatrix.getRow(), imageMatrix.getCol()))
      {                                              // Read image data

        imageMatrix.encodeImg(msgMatrix.getRowPlcmt(), msgMatrix.getColPlcmt(), 
                              msgMatrix.getRowMsg(), msgMatrix.getColMsg(), 
                              msgMatrix);
                                  // Encode image using the message file
        cout << "Message encode successful: Yes" << endl;
        isReaded = true;
      }
      else
      { 
        cout << "Message encode successful: No" << endl;
      }
    }
    else if (userChoice == DECODE_IMAGE)
    {
        imageMatrix.decodeImg();                 //Perform decoding
        if (!isReaded)
        {
        cout << "Decoded the image without loading the encode message" << endl;
        }
    }

    else if (userChoice == WRITE_IMAGE)
    {
      cout << "Enter name of file to write image to: ";
      cin >> writeFileName;
      
      imageMatrix.writeToFile(writeFileName);  // Write image to the ppm file

    }
    else if (userChoice == EXIT_PROGRAM)
    {
      cout << "Thanks for using this program!" << endl;
      isExit = true;      //Come out of the loop
    }
  }
  return 0;
}





