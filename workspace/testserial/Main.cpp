#include <stdio.h>
#include <tchar.h>
#include "Serial.h"	// Library described above
#include <string>


int SearchFirstData(char pa[], int start, int filled)
{
    int result = start;
    int nulcnt = 0;
    for (int i = start; i < (start+filled); i++)
    {
        if (pa[i] == 0)
        {
            nulcnt++;
        }
        else
        {
            nulcnt = 0;
        }
        if (nulcnt == 3)
        {
            result = (i + 1)%100;
            break;
        }
    }
    return result;
}

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	printf("Welcome to the serial test app!\n\n");

	int nBaudRate = CBR_9600; //CBR_9600;
	Serial* SP = new Serial("COM2", nBaudRate);	 // COM7 nano
		//new Serial("\\\\.\\COM10");    // use this prefix for COM10 and higher on windows systems.

	if (SP->IsConnected())
	{
		printf("We're connected");
	}
	else
	{
		printf("failed to connect");
		system("pause");
	}

	char incomingData[256] = "";			// don't forget to pre-allocate memory
											//printf("%s\n",incomingData);
	char outGoingData[256] = "";

	int dataLength = 255;
	int readResult = 0;
    long result = 0;
    long save = 0;
    bool first = true;

    char buffer[100];
    int idx=0;
    int filled = 0;
	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;

        for (int i = 0; i < readResult;i++)
        {
            buffer[readResult + filled] = (int)incomingData[i];
        }
        filled+=readResult;
        if (filled > 7)
        {
            int x = idx;
            idx = SearchFirstData(buffer, idx, filled);
            int diffidx = idx - x;
            if (diffidx < 0)diffidx += 100;
            filled -= diffidx+2;
            result = buffer[idx];
            result *= 0xff;
            result += buffer[idx + 1];
        }
        printf("%d ", result);
        printf("\n");
        

        


        /*if (first)
        {
            save = readResult;
            first = false;
        }
        else
        {
            save *= 0xff;
            save = readResult;
            first = true;
            result = save;
            save = 0;
        }
		printf("%d ", save);*/

		outGoingData[0] = 66; // 'B'
		SP->WriteData(outGoingData,1/*nbChar*/);
		Sleep(5);
	}
	return 0;
}

// For testing purposes, I copied next code to the Arduino:
//
//void setup()
//{
//	Serial.begin(115200);
//}
//
//void loop()
//{
//	// Echo characters
//	int nByte = 0;
//	bool bByteRead = false;
//	while (Serial.available())
//	{
//		nByte = Serial.read();
//		Serial.write(nByte);
//		bByteRead = true;
//	}
//
//	if (!bByteRead)
//	{
//		Serial.write(65); // If nothing is read, write "A" instead.
//	}
//}