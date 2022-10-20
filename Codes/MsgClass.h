#ifndef _MSGCLASS_H_
#define _MSGCLASS_H_

#include <iostream>
using namespace std;

#include "constant.h"
#include "ColorClass.h"

// Programmer: Hongrui Liu, Mar 14 2021. 
// This is the header file of the MsgClass.
// An object of the MsgClass will store the information of an encoding message
//   file including size, initial placement and data.
// The main function of this class is to read data from a txt file and store it
//   in a dynamic 2D array.
class MsgClass
{
private:
  int ** msgMatrix;      // Define 2D array
  int rowPlcmt;          // Create pricate attributes
  int colPlcmt;
  int rowMsg;
  int colMsg;

public:

  // Constructor
  MsgClass();

  // This function can read data from a txt file which contains the encoding 
  //   messages. 
  // It will then store the data in a int type 2D dynamic array for later use.
  // It will return false if anything goes wrong.
  // It can check the validity if the txt file (input error or data error).
  bool readMsg(const int rowInput, const int columnInput);

  // These functions simply return the private attributes of MsgClass.
  int getRowPlcmt();
  int getColPlcmt();
  int getRowMsg();
  int getColMsg();

  // This function returns the integer at the location provided.
  int getMsgAtLocation(const int row, const int col);

  // This function deletes the dynamic 2D array and frees the memory.
  // Did not use in this project.
  // Save for later
  void deleteMsg();
};
#endif
