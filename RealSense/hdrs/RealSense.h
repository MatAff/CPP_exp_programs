
#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

// External libraries
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

class RealSense
{
public:
    RealSense ();
    RealSense(bool rgb, bool depth, bool ir);
    ~RealSense ();

    cv::Mat getColor();
    cv::Mat getIR();
    cv::Mat getDepth();

private:

    //Contruct a pipeline which abstracts the device
    rs2::pipeline pipe;

    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;

    // Frame size
    cv::Size rsSize = cv::Size(640, 480);

    // Frame set
    rs2::frameset frames;

    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

};
