// counting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <bitset>

#include <random>
#include <algorithm>
#include <iterator>

#include <vector>

#include "DecodeUnaryCharactersUsingStrings.h"
#include "EncodeUnaryRandom.h"
//#include <boost/dynamic_bitset.hpp>"



using namespace std;


int main()
{
    unsigned int EncodingArray[2][300];// up to 
    unsigned char schar = 0x0, krandom = 0, scheme = 8;
    
    char  temp = 0, Message[200];
    char Zero = 0x00, One = 0x01, Null1 = 0x06, Null2 = 0x03;
    unsigned char xin = 0;// data input character
    unsigned char t = 0x00, TotalBytes = 0;
    unsigned char AddNull = 0, PreviousNull = 1;
    unsigned char InsertNull1 = 0b1010, InsertNull2 = 0b0101;
    unsigned int vtemp = 0, rtemp = 0,v1 = 0, v2 = 0, r2 = 0, r1 = 0;
    unsigned int max = 0, i = 0, j = 0, k = 0, BytesFromInputLoop = 0, NumberBytes = 0, err = 0;
    unsigned int bufindex = 0, ErrorRate = 10000, RandomSeed = 0, Kbytes = 0;
    unsigned int Length = 0,BitsLeft=0;
    int NumberOfBitsInString = 0;
    unsigned int TrailerLength = 22;
    bool SwapChunks = 0;
    std::string OutputBytes = "";
    std::string ConsoleInput;
    std::string OriginalInput;
 
    //********************** Encrypt Array Setup *************************************
    // Each array element has 8 bits. from 0 to 255 randomly
   
 
AGAIN:
    ConsoleInput.erase();
    std::string TestMessage = "ABCD";//"The quick brown fox jumps over the lazy dogs back. 1234567890 !@#$%^&*() ABCDE";
   
    cout << " Just Enter return for a standard test message or Enter a message :";
    //********************************************************************************


   getline(cin, ConsoleInput);
    NumberBytes = ConsoleInput.length();// length in bytes in "1235" is 4
    if (NumberBytes == 0) {
        ConsoleInput = TestMessage;
    }

    cout << "You entered: " << ConsoleInput << " \n" << endl;
    OriginalInput = ConsoleInput;

    NumberBytes = ConsoleInput.length();// length in bytes in "1235" is 4
       
        EncodeUnaryRandom(ConsoleInput,SwapChunks);// length in bits
        
        ConsoleInput.erase();
       // ConsoleInput = "";
        cout << "\n";
        cout << " Again ?  enter a  message \n";
        std::cin >> temp;
      
        if (temp > 0) goto AGAIN;
        

}