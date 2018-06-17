#include "windowControl.hpp"

using namespace cv;
using namespace std;

WindowControl::WindowControl():
    video_load(VideoCapture(0))
{
    namedWindow("Adjust", CV_WINDOW_NORMAL);

    //createTrackbar("Hue_Lower", "Adjust", &Hue_Lower_Value, 179);
    //createTrackbar("Hue_Lower", "Adjust", &Hue_Upper_Value, 179);
    //createTrackbar("Sat_Lower", "Adjust", &Saturation_Lower_Value, 255);
    //createTrackbar("Sat_Upper", "Adjust", &Saturation_Upper_Value, 255);
    //createTrackbar("Val_Lower", "Adjust", &Value_Lower, 255);
    //createTrackbar("Val_Upper", "Adjust", &Value_Upper, 255);
    createTrackbar("MotorSpeed", "Adjust", &Motor_speed_lower, 200);
    createTrackbar("MotorSpeed", "Adjust", &Motor_speed_upper, 200);
    video_load.read(temp);

    createTrackbar("P", "Adjust", &kp_lower, pidMax);
    createTrackbar("P", "Adjust", &kp_upper, pidMax);
    createTrackbar("I", "Adjust", &ki_lower, pidMax);
    createTrackbar("I", "Adjust", &ki_upper, pidMax);
    createTrackbar("D", "Adjust", &kd_lower, pidMax);
    createTrackbar("D", "Adjust", &kd_upper, pidMax);


    track_motion = Mat::zeros(temp.size(), CV_8UC3);
}


int WindowControl::run()
{
    Mat actual_Image;
    bool temp = video_load.read(actual_Image);
    Mat convert_to_HSV;

    cvtColor(actual_Image, convert_to_HSV, COLOR_BGR2HSV);
    Mat adjusted_frame;

    inRange(convert_to_HSV,
        Scalar(Hue_Lower_Value, Saturation_Lower_Value, Value_Lower),
        Scalar(Hue_Upper_Value, Saturation_Upper_Value, Value_Upper),
        adjusted_frame);

    erode(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));



    Moments detecting_object = moments(adjusted_frame);
    double vertical_moments = detecting_object.m01;
    double horizontal_moment = detecting_object.m10;
    double tracking_area = detecting_object.m00;

    if (tracking_area>10000) {
        int posX = horizontal_moment / tracking_area;
        int posY = vertical_moments / tracking_area;
        if (Horizontal_Last >= 0 && Vertical_Last >= 0 && posX >= 0 && posY >= 0) {
            line(track_motion, Point(posX, posY), Point(Horizontal_Last, Vertical_Last), Scalar(0, 0, 255), 2);

        }
        Horizontal_Last = posX;
        Vertical_Last = posY;
    }
    imshow("Detected_Object", adjusted_frame);
    actual_Image += track_motion;
    imshow("Actual", actual_Image);

    //std::cout << "Position of the object is: " << Horizontal_Last << "," << Vertical_Last << endl;
    return 0;

}

WindowControl::~WindowControl()
{
}
