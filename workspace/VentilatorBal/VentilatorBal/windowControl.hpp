#pragma once

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



class WindowControl
{
private:
    int Hue_Lower_Value = 0;
    int Hue_Upper_Value = 255;
    int Saturation_Lower_Value = 110;
    int Saturation_Upper_Value = 255;
    int Value_Lower = 120;
    int Value_Upper = 255;

    int Motor_speed_lower = 0;
    int Motor_speed_upper = 200;





    int Horizontal_Last = -1;
    int Vertical_Last = -1;

    cv::VideoCapture video_load;
    cv::Mat temp;

    cv::Mat track_motion;

    /*
    Most optimal values found:

    Hue_Lower: 98
    Sat_Lower: 75
    Sat_Upper: 255
    Val_Lower: 255
    Val_Upper: 255

    */


public:
    int pidMax = 1000;


    int kp_lower = 0;
    int kp_upper = 507;

    int ki_lower = 0;
    int ki_upper = 205;

    int kd_lower = 0;
    int kd_upper = 226;

    WindowControl();

    int GetHorLast() { return Horizontal_Last; };
    int GetVertLast() { return Vertical_Last; };
    int GetMotorSpeed() { return Motor_speed_upper;  };
    int run();
    ~WindowControl();
};

