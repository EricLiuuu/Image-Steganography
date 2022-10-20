#include <iostream>
#include <fstream>
using namespace std;

#include "ColorImageClass.h"
#include "constant.h"
#include "ColorClass.h"
#include "MsgClass.h"

// Programmer: Hongrui Liu, Mar 14 2021. 
// This is the implementation of the ColorImageClass.h file.

ColorImageClass::ColorImageClass()
{
  imageMatrix = NULL;
  rowInput = MIN_DIMENSION;
  columnInput = MIN_DIMENSION;
}

int ColorImageClass::getRow()
{
  return rowInput;
}

int ColorImageClass::getCol()
{
  return columnInput;
}


int ColorImageClass::readColorImage(string fileName)
{
  ifstream inFile;
  string ppmMagicNum;
  string eofTesting;
  ColorClass rgbColor;
  int maxColor;
  int colIndex;
  int rowIndex;
  bool isInTheRange = true;

  inFile.open(fileName.c_str());
  if (inFile.fail())
  {
    cout << "Error: File doesn't exist or access denied" << endl;
    inFile.close();
    return FILE_ERROR;
  }
  else
  {

    inFile >> ppmMagicNum >> columnInput >> rowInput >> maxColor;

    if (inFile.fail())
    {
      cout << "Error: Invalid .ppm file header information" << endl;
      inFile.close();
      return HEADER_ERROR;
    }
    if (ppmMagicNum != "P3")       // ppm file magic number
    {
      cout << "Error: Invalid .ppm file magic number" << endl;
      inFile.close();
      return MAGIC_ERROR;
    }
    if (columnInput > MAX_DIMENSION || rowInput > MAX_DIMENSION ||
        columnInput < MIN_DIMENSION || rowInput < MIN_DIMENSION)
    {
      cout << "Error: Image size out of reasonable range" << endl;
      inFile.close();
      return SIZE_ERROR;
    }
    if (maxColor != MAX_COLOR)
    {
      cout << "Error: Maximum color value should be 255" << endl;
      inFile.close();
      return MAX_COLOR_ERROR;
    }

    imageMatrix = new ColorClass * [rowInput];
    for (rowIndex = 0; rowIndex < rowInput; rowIndex ++)
    {
      imageMatrix[rowIndex] = new ColorClass[columnInput];
    }

    for (rowIndex = 0; rowIndex < rowInput; rowIndex ++)  
    {
      for (colIndex = 0; colIndex < columnInput; colIndex ++)
      {

        rgbColor.readRgb(inFile);

        isInTheRange = imageMatrix[rowIndex][colIndex].setTo(rgbColor);

        if (inFile.fail())
        {
          cout << "Error: Reading color from file" << endl; 
          cout << "Error: Reading image pixel at row: " << rowIndex << " col: ";
          cout << colIndex << endl;
          inFile.close();
          return DATA_TYPE_ERROR;                                  
        }

        if (!isInTheRange)
        {
          cout << "Error: Color is outside the valid range" << endl;
          cout << "Error: Reading image pixel at row: " << rowIndex << " col: ";
          cout << colIndex << endl;
          inFile.close();
          return OUT_RANGE_ERROR;
        }
      }
    }
    if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(IGNORE_LENGTH, '\n');
    }

    inFile >> eofTesting;        // Test the end of file

    if (!inFile.fail())
    {
      cout << "Error: pixel amount doesn't match (larger)" << endl;
      inFile.close();
      return AMOUNT_ERROR;
    }
   
    cout << "Image read successful: Yes" << endl;
    inFile.close();
    return 0;
  }
}

void ColorImageClass::encodeImg(const int rowPlcmt, const int colPlcmt, 
                                const int rowMsg, const int colMsg, 
                                MsgClass msg)
{

  int encodeMsg;
  for (int rowIdxMsg = msg.getRowPlcmt(); 
           rowIdxMsg < msg.getRowMsg() + msg.getRowPlcmt();
           rowIdxMsg ++)
  {
    for (int colIdxMsg = msg.getColPlcmt();
             colIdxMsg < msg.getColMsg() + msg.getColPlcmt();
             colIdxMsg ++)
    {
      if (rowIdxMsg < rowInput && colIdxMsg < columnInput &&
          rowIdxMsg >= MIN_DIMENSION && colIdxMsg >= MIN_DIMENSION)
      {
        encodeMsg = msg.getMsgAtLocation(rowIdxMsg - msg.getRowPlcmt(), 
                                         colIdxMsg - msg.getColPlcmt());

        imageMatrix[rowIdxMsg][colIdxMsg].encodeColor(imageMatrix[rowIdxMsg]
                                                     [colIdxMsg], encodeMsg);

      }
    }
  }
}


void ColorImageClass::decodeImg()
{
  for (int row = 0; row < rowInput; row ++)
  {
    for (int col = 0; col < columnInput; col ++)
    {
      imageMatrix[row][col].decodeColor(imageMatrix[row][col]);
    }
  }
  cout << "Image modified to decoded image contents" << endl;
}


void ColorImageClass::writeToFile(string fileName)
{
  ColorClass rgbColor;
  ofstream outFile;
  outFile.open(fileName.c_str());

  if (outFile.fail())
  {
    cout << "Error: Fail to open file" << endl;
  }
  else
  {
    outFile << "P3" << endl;
    outFile << columnInput << " " << rowInput << endl;
    outFile << MAX_COLOR << endl;

    for (int row = 0; row < rowInput; row ++)
    {
      for (int col = 0; col < columnInput; col ++)
      {
        rgbColor.readRgb(imageMatrix[row][col]);

        rgbColor.writeRgb(outFile);
        
      }
      outFile << endl;
    }
    cout << "Image write successful: Yes" << endl;
  }
}


void ColorImageClass::deleteImg()
{
  for (int rowIndex = 0; rowIndex < rowInput; rowIndex ++)
  {
    delete [] imageMatrix[rowIndex];
  }
  delete [] imageMatrix;
}


