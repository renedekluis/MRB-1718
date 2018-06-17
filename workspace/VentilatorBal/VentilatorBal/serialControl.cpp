#include "serialControl.hpp"

#include <bitset>

SerialControl::SerialControl():
    nBaudRate(CBR_9600),
    SP(new Serial("COM2", nBaudRate))
{
}

bool SerialControl::CheckConnection()
{
    if (SP->IsConnected()) status = 1;
    else status = -1;
    return status;
}

int SerialControl::SearchFirstData(char pa[], int start, int filled)
{
    int result = start;
    int nulcnt = 0;
    for (int i = start; i < (start + filled); i++)
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
            result = (i + 1) % BUFFER_SIZE;
            break;
        }
    }
    return result;
}

int SerialControl::RollOver(int val)
{
    int bitConv = 128;
    int result = 0;
    for (int i = 0; i < 8; i++)
    {
        if ((val & (1 << i)) >> i)
        {
            result += bitConv;
        }
        bitConv /= 2;
    }
    return result;
}

int SerialControl::GetStatus()
{
    return status;
}

int SerialControl::GetData()
{
    if (CheckConnection())
    {
        readResult = SP->ReadData(incomingData, dataLength);
        //printf("%6d\n", (int)incomingData[0]);
        return (int)incomingData[0];
    }
    else
    {
        printf("Connection Failure!\n");
        return -1;
    }
}

int SerialControl::GetData2()
{
    if (CheckConnection())
    {
        readResult = SP->ReadData(incomingData, dataLength);
        
        incomingData[readResult] = 0;

        //printf("%6d\n", );
        int tempFilled = filled;
        for(int i = 0; i < readResult; i++)
        {
            int x = (filled + i) % BUFFER_SIZE;
            buffer[x] = (int)incomingData[i];

            
        }
        
        filled += readResult;

        bool printBool = false;
        if (filled > 7)
        {

            int x = idx;
            idx = SearchFirstData(buffer, idx, filled);
            int byte1 = buffer[idx];
            int byte2 = buffer[idx+1];
            if (byte1 < 0)
                byte1 = RollOver((int)buffer[idx]);
            
            if (byte2 < 0)
                byte2 = RollOver((int)buffer[idx + 1]);
            
            int diffidx = idx - x;
            if (diffidx < 0)diffidx += BUFFER_SIZE;
            
            filled -= diffidx + 2;
            filled = filled % BUFFER_SIZE;

            result = byte1;
            result *= 0xff;
            result += byte2;

        }

        std::bitset<8>b1(buffer[idx]);
        std::bitset<8>b2(buffer[idx+1]);

        int other = (int)buffer[idx];
        other *= 0xff;
        other += (int)buffer[idx+1];

        //std::cout << b1 << "  " << b2 << " ";
        //printf("%6d | %6d | %10d | %10d\n", (int)buffer[idx], (int)buffer[idx+1],result, other);
        //printf("%6d | %6d\n", buffer[idx], buffer[idx + 1]);
        return result;
    }
    else
    {
        printf("Connection Failure!\n");
        return -1;
    }
}


void SerialControl::SendData(char data[], int length)
{
    SP->WriteData(data, length);
}

SerialControl::~SerialControl()
{
}
