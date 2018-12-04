#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// Main program
int main(int argc,char ** argv)
{

    // Frame
    cv::Mat frame(cv::Size(640,480), CV_8UC3);

    // Main loop
    while (true)
    {

        // Clear frame
        frame = cv::Scalar(0,0,0);

        // Output - display - record
        imshow("Live", frame);

        // User input (This pause is required to show the frame)
        int key = cv::waitKey(5);

        // Process user input
        if (key==97) { break; } // a

   }

    return 0;
}
