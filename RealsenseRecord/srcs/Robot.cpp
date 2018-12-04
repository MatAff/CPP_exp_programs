// General
#include <iostream>

// Open CV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// Robot classes
#include <librealsense2/rs.hpp>
#include "RealSense.h"

// Main program
int main(int argc,char ** argv)
{

    //bool playback = false;
    bool playback = false;

    RealSense rs(playback);

    // Frame
    cv::Mat frame(cv::Size(640,480), CV_8UC3);

    // Main loop
    while (true)
    {

        // Clear frame
        frame = cv::Scalar(0,0,0);

        frame = rs.getColor();

        // Output - display - record
        imshow("Live", frame);

        // User input (This pause is required to show the frame)
        int key = cv::waitKey(5);

        // Process user input
        if (key==97) { break; } // a

   }

    return 0;
}
