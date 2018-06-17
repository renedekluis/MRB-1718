#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "windowControl.hpp"
#include "serialControl.hpp"
#include <chrono>
#include <thread>
#include <ctime>
#include <ratio>
#include <conio.h>
#include <windows.h>





using namespace cv;
using namespace std;

char* convToData(int value)
{
    char out[100];
    out[0] = value;
    value /= 0xff;
    out[1] = value;
    return out;
}

int main(int argc, char** argv) {

    using namespace std::chrono;

    VideoCapture video_load(0);
    namedWindow("Adjust", CV_WINDOW_AUTOSIZE);

    WindowControl w;

    SerialControl siri;

    int startpoint = 500;
    char output[255];

    int setpoint[] = {250,150,300,100,200,150};
    int setIdx = 3;
    int stadyCnt = 0;

    float kp = 0.0507;
    float ki = 0.0205;
    float kd = 0.0226;


    float oldError = 0;
    float error = setpoint[setIdx] - w.GetVertLast();


    float errorsum = 0;

    float edelta = 0;

    float u = 0;
    duration<double> time_span;
    float tijd;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    high_resolution_clock::time_point timeStamp = high_resolution_clock::now();
    duration<double>timer;

    while (1)
    {

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);

        timer = duration_cast<duration<double>>(high_resolution_clock::now() - timeStamp);

        if (timer.count() > 25)
        {
            setIdx++;
            setIdx %= 6;
            timeStamp = high_resolution_clock::now();
        }

        

        kp = (float)w.kp_upper/10000;
        ki = (float)w.ki_upper/10000;
        kd = (float)w.kd_upper/10000;



        if (waitKey(30) == 27) {
            std::cout << "Escape key is pressed by User" << endl;
            break;
        }

        w.run();
        long incommingData = siri.GetData();

        //if (incommingData > 0)
       // {
            //setpoint[setIdx] =  incommingData;
        //}


        if (siri.GetStatus() == -1)
        {
            std::cout << "Connection to serial interface cannot be made." << endl;
            break;
        }


        

        tijd = time_span.count();

        error = setpoint[setIdx] -(400- w.GetVertLast());



        errorsum = errorsum + error * tijd;
        edelta = -(error - oldError) / tijd;
        u = kp * error + ki * errorsum + kd * ((error - oldError) / tijd);

        oldError = error;

        printf("%6d    %6d  | ", w.GetVertLast(), setpoint);
        printf("%10.2f = %6.2f * %6.2f + %6.2f * %10.2f + %6.2f * ((%10.2f - %10.2f) / %6.2f)\n", u, kp, error, ki, errorsum, kd, error, oldError, tijd);


        u = 50 -u;
        if (u < 0)u = 0;
        output[0] = u;
        //printf("%10.5f", u);
        siri.SendData(output, 1);

        t1 = t2;
       
    }

    destroyAllWindows();
    while (1);
    return 0;
}