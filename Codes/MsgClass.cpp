#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "constant.h"
#include "ColorClass.h"
#include "MsgClass.h"

// Programmer: Hongrui Liu, Mar 14 2021. 
// This is the implementation file of the MsgClass.



MsgClass::MsgClass()
{
  msgMatrix = NULL;
  rowPlcmt = MIN_DIMENSION;
  colPlcmt = MIN_DIMENSION;
  rowMsg = MIN_DIMENSION;
  colMsg = MIN_DIMENSION;
}

bool MsgClass::readMsg(const int rowInput, const int columnInput)
{
  int rowIdxMsg;
  int colIdxMsg;
  int encodeMsg;

  ifstream inFile;
  string eofTesting;
  string encodingFileName;

  cout << "Enter name of file containing message: ";
  cin >> encodingFileName;
  inFile.open(encodingFileName.c_str());
  if (inFile.fail())
  {
    cout << "Error: File doesn't exist or access denied" << endl;
    cin.clear();
    cin.ignore(IGNORE_LENGTH, '\n');
    return false;
  }
  else
  {
    cout << "Enter row and column for message placement: ";
    cin >> rowPlcmt >> colPlcmt;     //initial encoding location

    if (cin.fail())
    {
      cout << "Please input valid numbers (int type)" << endl;
      cin.clear();
      cin.ignore(IGNORE_LENGTH, '\n');
      return false;
    }
    else
    {
      inFile >> colMsg >> rowMsg;   //Read header information of message file

      if (inFile.eof())
      {
        cout << "Error: Message file is empty." << endl;
        inFile.close();
        return false;
      }
      else if (inFile.fail() || rowMsg < MIN_DIMENSION || 
                                colMsg < MIN_DIMENSION)
      {
        cout << "Error: Invalid message file header" << endl;
        inFile.close();
        return false;
      }
      else
      {
        msgMatrix = new int * [rowMsg];
        for (rowIdxMsg = 0; rowIdxMsg < rowMsg; rowIdxMsg ++)
        {
          msgMatrix[rowIdxMsg] = new int[colMsg];
        }
        for (rowIdxMsg = 0; rowIdxMsg < rowMsg; rowIdxMsg ++)
        {
          for (colIdxMsg = 0; colIdxMsg < colMsg; colIdxMsg ++)
          {
            inFile >> encodeMsg;
            msgMatrix[rowIdxMsg][colIdxMsg] = encodeMsg;
            if (inFile.fail() || encodeMsg < MIN_MSG_VALUE
                              || encodeMsg > MAX_MSG_VALUE)
            {
              cout << "Error: Reading message value at row/col: ";
              cout << rowIdxMsg << " " << colIdxMsg << endl;
              inFile.close();
              return false;
            }
          
          }
        }

        if (inFile.fail())
        {
          inFile.clear();
          inFile.ignore(IGNORE_LENGTH, '\n');
        }

        inFile >> eofTesting;

        if (!inFile.fail())
        {
          cout << "Error: Message amount doesn't match (larger)" << endl;
          inFile.close();
          return false;
        }
        else
        {
          inFile.close();
           return true;
        }
      }
    }
  }
}

int MsgClass::getRowPlcmt()
{
  return rowPlcmt;
}
int MsgClass::getColPlcmt()
{
  return colPlcmt;
}
int MsgClass::getRowMsg()
{
  return rowMsg;
}
int MsgClass::getColMsg()
{
  return colMsg;
}

int MsgClass::getMsgAtLocation(const int row, const int col)
{
  return msgMatrix[row][col];
}

void MsgClass::deleteMsg()
{
  for (int rowIdxMsg = 0; rowIdxMsg < rowMsg; rowIdxMsg ++)
  {
    delete [] msgMatrix[rowIdxMsg];
  }
  delete [] msgMatrix;
}

