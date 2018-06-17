#pragma once

#include <iostream>
#include "Serial.h"	// Library described above
#include <string>
#include <stdio.h>
#include <tchar.h>


#define BUFFER_SIZE 106



class SerialControl
{
private:
    int nBaudRate;
    Serial* SP;

    char incomingData[256] = "";			// don't forget to pre-allocate memory
                                            //printf("%s\n",incomingData);
    char outGoingData[256] = "";
    int dataLength = 255;
    int readResult = 0;
    long result = 0;
    long save = 0;
    bool first = true;
    char buffer[BUFFER_SIZE];
    int idx = 0;
    int filled = 0;

    int status = 0;

    bool CheckConnection();
    int RollOver(int val);
    int SearchFirstData(char pa[], int start, int filled);
public:
    SerialControl();

    int GetStatus();
    
    int GetData();
    int GetData2();
    long GetValue() { return result; };
    void SendData(char data[], int length);
    ~SerialControl();
};

