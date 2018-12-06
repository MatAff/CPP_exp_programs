

#include "RealSense.h"

// Default constructor
RealSense::RealSense() {} // : RealSense(true, true, false) {}

// Argument constructor
RealSense::RealSense(bool rgb, bool depth, bool ir)
{
    //Add desired streams to configuration
    if (rgb) { cfg.enable_stream(RS2_STREAM_COLOR, rsSize.width, rsSize.height, RS2_FORMAT_BGR8, 30); }
    if (depth) { cfg.enable_stream(RS2_STREAM_DEPTH, rsSize.width, rsSize.height, RS2_FORMAT_Z16, 30); }
    if (ir) { cfg.enable_stream(RS2_STREAM_INFRARED, rsSize.width, rsSize.height, RS2_FORMAT_Y8, 30); }

    //Instruct pipeline to start streaming with the requested configuration
    pipe.start(cfg);

    // Camera warmup - dropping several first frames to let auto-exposure stabilize
    for(int i = 0; i < 30; i++)
    {
        //Wait for all configured streams to produce a frame
        frames = pipe.wait_for_frames();
    }
}

// Destructor
RealSense::~RealSense()
{
}

// Method to return rgb image
cv::Mat RealSense::getColor()
{
    frames = pipe.wait_for_frames();
    rs2::frame color_frame = frames.get_color_frame();

    // Creating OpenCV Matrix from a color image
    cv::Mat color(cv::Size(rsSize.width, rsSize.height), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);

    // Return color image
    return color;
}

// Method to return IR image
cv::Mat RealSense::getIR()
{
    frames = pipe.wait_for_frames();
    rs2::frame ir_frame = frames.first(RS2_STREAM_INFRARED);

    // Creating OpenCV matrix from IR image
    cv::Mat ir(cv::Size(rsSize.width, rsSize.height), CV_8UC1, (void*)ir_frame.get_data(), cv::Mat::AUTO_STEP);

    // Apply Histogram Equalization
    equalizeHist( ir, ir );
    applyColorMap(ir, ir, cv::COLORMAP_JET);

    // Return ir image
    return ir;
}

// Method to return depth visualization
cv::Mat RealSense::getDepth()
{
    frames = pipe.wait_for_frames();
    //rs2::frame ir_frame = frames.first(RS2_STREAM_DEPTH);
    const rs2::frame depth_frame = frames.get_depth_frame(); // Find depth data
    rs2::frame depth = color_map(depth_frame); // Find and colorize the depth data

    // OpenCV Matrix from a color image
    cv::Mat color(cv::Size(rsSize.width, rsSize.height), CV_8UC3, (void*)depth.get_data(), cv::Mat::AUTO_STEP);

    // Return image
    return color;
}
