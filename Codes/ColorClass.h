#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include "constant.h"

// Programmer: Hongrui Liu, Mar 14 2021
// This is the header file for ColorClass. 
// ColorClass is a class for storing three rgb values of a single pixel. 
// It has three attributes which represent those rgb values. 
// It also comes with some member functions, which can operate on single pixel's
//   rgb values. 
// As long as we deal with images, this class would be useful.


class ColorClass
{
private:       // Define three RGB color components in ColorClass
  int red;
  int green;
  int blue;

  // Compare the input color component values to the valid range of color
  //   value (0~255). 
  // If the input color value is outside the valid color range, the function 
  //   will return false, and return true otherwise.  
  bool checkColorValidity(const int inputColor);

public:
  // Default constructor (initial color to full white)
  ColorClass();

  // Set RGB color to a specific color according to the encoding message.
  // Here is the descrption:
  // Color description : Black, Encoding RGB : (Even, Even, Even)
  // Color description : Red, Encoding RGB : (Odd, Even, Even)
  // Color description : Green, Encoding RGB : (Even, Odd, Even)
  // Color description : Blue, Encoding RGB : (Even, Even, Odd)
  // Color description : White, Encoding RGB : (Odd, Odd, Odd)
  // Color description : Yellow, Encoding RGB : (Odd, Odd, Even)
  // Color description : Magenta, Encoding RGB : (Odd, Even, Odd)
  // Color description : Cyan, Encoding RGB : (Even, Odd, Odd)
  // If a color is odd and we need to encode even, then we simply subtract one 
  //   from its value. 
  // If a color is even, and we need to encode odd, then we add one to its 
  //   value.

  void setToBlack(ColorClass& inColor);
  void setToRed(ColorClass& inColor);
  void setToGreen(ColorClass& inColor);
  void setToBlue(ColorClass& inColor);
  void setToWhite(ColorClass& inColor);
  void setToYellow(ColorClass& inColor);
  void setToMagenta(ColorClass& inColor);
  void setToCyan(ColorClass& inColor);

  // This function modifies a pixel such that whether the individual RGB 
  //   components are even or odd implies different colors. 
  // This limits us to being able to encode only 8 different colors. 
  // And these 8 colors shows above.
  void encodeColor(ColorClass& inColor, const int colorCode);

  // This function has the opposite function as the encodeColor function.
  // It simply reads the rgb value of a pixel and convert this pixel to the
  //   color corresponding to the encoding message file. 
  void decodeColor(ColorClass& inColor);

  // These functions convert one single pixel to a specific color according to
  //   the encoding message file. 
  void decodeToBlack(ColorClass& inColor);
  void decodeToRed(ColorClass& inColor);
  void decodeToGreen(ColorClass& inColor);
  void decodeToBlue(ColorClass& inColor);
  void decodeToWhite(ColorClass& inColor);
  void decodeToYellow(ColorClass& inColor);
  void decodeToMagenta(ColorClass& inColor);
  void decodeToCyan(ColorClass& inColor);

  // Set RGB color to a provided color
  // Check validity to make sure the color range value within 0~255
  // If the input color value is outside the valid color range, the function 
  //   will return false, and return true otherwise.  
  bool setTo(const ColorClass inColor);

  // Read rgb values into a ColorClass object
  void readRgb(const ColorClass inColor);
  void readRgb(ifstream& inFile);

  // Write rgb values to files according to the provided ofstream object
  void writeRgb(ofstream& outFile);
};
#endif