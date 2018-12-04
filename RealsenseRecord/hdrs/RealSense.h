
#pragma once

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class RealSense
{
public:
    RealSense(bool playback);
    ~RealSense();

    cv::Mat getColor();

    std::shared_ptr<rs2::pipeline> pipe = std::make_shared<rs2::pipeline>();
    rs2::config cfg; // Declare a new configuration
    rs2::frameset frames;
    rs2::frame depth;
    rs2::colorizer color_map;
    rs2::device device;


};
