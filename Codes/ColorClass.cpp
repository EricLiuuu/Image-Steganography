#include <iostream>
#include <fstream>
using namespace std;

#include "constant.h"
#include "ColorClass.h"

// Programmer: Hongrui Liu, Mar 14 2021
// This is the implementation of the ColorClass.h file.

ColorClass::ColorClass()
{
  red = MAX_COLOR;
  green = MAX_COLOR;
  blue = MAX_COLOR;
}

void ColorClass::setToBlack(ColorClass& inColor)
{
  if (inColor.red % 2 != 0)
  {
    inColor.red = inColor.red - 1;
  }
  if (inColor.green % 2 != 0)
  {
    inColor.green = inColor.green - 1;
  }
  if (inColor.blue % 2 != 0)
  {
    inColor.blue = inColor.blue - 1;
  }
}

void ColorClass::setToRed(ColorClass& inColor)
{
  if (inColor.red % 2 == 0)
  {
    inColor.red = inColor.red + 1;
  }
  if (inColor.green % 2 != 0)
  {
    inColor.green = inColor.green - 1;
  }
  if (inColor.blue % 2 != 0)
  {
    inColor.blue = inColor.blue - 1;
  }
}

void ColorClass::setToGreen(ColorClass& inColor)
{
  if (inColor.red % 2 != 0)
  {
    inColor.red = inColor.red - 1;
  }
  if (inColor.green % 2 == 0)
  {
    inColor.green = inColor.green + 1;
  }
  if (inColor.blue % 2 != 0)
  {
    inColor.blue = inColor.blue - 1;
  }
}

void ColorClass::setToBlue(ColorClass& inColor)
{
  if (inColor.red % 2 != 0)
  {
    inColor.red = inColor.red - 1;
  }
  if (inColor.green % 2 != 0)
  {
    inColor.green = inColor.green - 1;
  }
  if (inColor.blue % 2 == 0)
  {
    inColor.blue = inColor.blue + 1;
  }
}

void ColorClass::setToWhite(ColorClass& inColor)
{
  if (inColor.red % 2 == 0)
  {
    inColor.red = inColor.red + 1;
  }
  if (inColor.green % 2 == 0)
  {
    inColor.green = inColor.green + 1;
  }
  if (inColor.blue % 2 == 0)
  {
    inColor.blue = inColor.blue + 1;
  }
}

void ColorClass::setToYellow(ColorClass& inColor)
{
  if (inColor.red % 2 == 0)
  {
    inColor.red = inColor.red + 1;
  }
  if (inColor.green % 2 == 0)
  {
    inColor.green = inColor.green + 1;
  }
  if (inColor.blue % 2 != 0)
  {
    inColor.blue = inColor.blue - 1;
  }
}

void ColorClass::setToMagenta(ColorClass& inColor)
{
  if (inColor.red % 2 == 0)
  {
    inColor.red = inColor.red + 1;
  }
  if (inColor.green % 2 != 0)
  {
    inColor.green = inColor.green - 1;
  }
  if (inColor.blue % 2 == 0)
  {
    inColor.blue = inColor.blue + 1;
  }
}

void ColorClass::setToCyan(ColorClass& inColor)
{
  if (inColor.red % 2 != 0)
  {
    inColor.red = inColor.red - 1;
  }
  if (inColor.green % 2 == 0)
  {
    inColor.green = inColor.green + 1;
  }
  if (inColor.blue % 2 == 0)
  {
    inColor.blue = inColor.blue + 1;
  }
}

void ColorClass::encodeColor(ColorClass& inColor, const int colorCode)
{
  if (colorCode == BLACK)
  {
    setToBlack(inColor);
  }
  if (colorCode == RED)
  {
    setToRed(inColor);
  }
  if (colorCode == GREEN)
  {
    setToGreen(inColor);
  }
  if (colorCode == BLUE)
  {
    setToBlue(inColor);
  }
  if (colorCode == WHITE)
  {
    setToWhite(inColor);
  }
  if (colorCode == YELLOW)
  {
    setToYellow(inColor);
  }
  if (colorCode == MAGENTA)
  {
    setToMagenta(inColor);
  }
  if (colorCode == CYAN)
  {
    setToCyan(inColor);
  }
}



bool ColorClass::checkColorValidity(const int inputColor)
{
  bool isValid;
  if (inputColor >= MIN_COLOR && inputColor <= MAX_COLOR)
  {
    isValid = true;
  }
  else
  {
    isValid = false;
  }

  return isValid;
}

void ColorClass::decodeColor(ColorClass& inColor)
{
  if (inColor.red % 2 == 0 && inColor.green % 2 == 0 && inColor.blue % 2 == 0)
  {
    inColor.decodeToBlack(inColor);
  }
  if (inColor.red % 2 != 0 && inColor.green % 2 == 0 && inColor.blue % 2 == 0)
  {
    inColor.decodeToRed(inColor);
  }
  if (inColor.red % 2 == 0 && inColor.green % 2 != 0 && inColor.blue % 2 == 0)
  {
    inColor.decodeToGreen(inColor);
  }
  if (inColor.red % 2 == 0 && inColor.green % 2 == 0 && inColor.blue % 2 != 0)
  {
    inColor.decodeToBlue(inColor);
  }
  if (inColor.red % 2 != 0 && inColor.green % 2 != 0 && inColor.blue % 2 != 0)
  {
    inColor.decodeToWhite(inColor);
  }
  if (inColor.red % 2 != 0 && inColor.green % 2 != 0 && inColor.blue % 2 == 0)
  {
    inColor.decodeToYellow(inColor);
  }
  if (inColor.red % 2 != 0 && inColor.green % 2 == 0 && inColor.blue % 2 != 0)
  {
    inColor.decodeToMagenta(inColor);
  }
  if (inColor.red % 2 == 0 && inColor.green % 2 != 0 && inColor.blue % 2 != 0)
  {
    inColor.decodeToCyan(inColor);
  }
}

void ColorClass::decodeToBlack(ColorClass& inColor)
{
  inColor.red = MIN_COLOR;
  inColor.green = MIN_COLOR;
  inColor.blue = MIN_COLOR;
}

void ColorClass::decodeToRed(ColorClass& inColor)
{
  inColor.red = MAX_COLOR;
  inColor.green = MIN_COLOR;
  inColor.blue = MIN_COLOR;
}

void ColorClass::decodeToGreen(ColorClass& inColor)
{
  inColor.red = MIN_COLOR;
  inColor.green = MAX_COLOR;
  inColor.blue = MIN_COLOR;
}

void ColorClass::decodeToBlue(ColorClass& inColor)
{
  inColor.red = MIN_COLOR;
  inColor.green = MIN_COLOR;
  inColor.blue = MAX_COLOR;
}

void ColorClass::decodeToWhite(ColorClass& inColor)
{
  inColor.red = MAX_COLOR;
  inColor.green = MAX_COLOR;
  inColor.blue = MAX_COLOR;
}

void ColorClass::decodeToYellow(ColorClass& inColor)
{
  inColor.red = MAX_COLOR;
  inColor.green = MAX_COLOR;
  inColor.blue = MIN_COLOR;
}

void ColorClass::decodeToMagenta(ColorClass& inColor)
{
  inColor.red = MAX_COLOR;
  inColor.green = MIN_COLOR;
  inColor.blue = MAX_COLOR;
}

void ColorClass::decodeToCyan(ColorClass& inColor)
{
  inColor.red = MIN_COLOR;
  inColor.green = MAX_COLOR;
  inColor.blue = MAX_COLOR;
}


bool ColorClass::setTo(const ColorClass inColor)
{
  bool isValid;
  bool isRedValid;
  bool isGreenValid;
  bool isBlueValid;
  isRedValid = checkColorValidity(inColor.red);
  isGreenValid = checkColorValidity(inColor.green);
  isBlueValid = checkColorValidity(inColor.blue);

  if (isRedValid == true && isGreenValid == true && isBlueValid == true)
  {
    isValid = true;
    red = inColor.red;
    green = inColor.green;
    blue = inColor.blue;
  }
  else
  {
    isValid = false;
  }

  return isValid;
}


void ColorClass::readRgb(const ColorClass inColor)
{
  red = inColor.red;
  green = inColor.green;
  blue = inColor.blue;
}

void ColorClass::readRgb(ifstream& inFile)
{
  inFile >> red >> green >> blue;
}

void ColorClass::writeRgb(ofstream& outFile)
{
  outFile << red << " " << green << " " << blue << " ";
}