// General
#include <iostream>

// Open CV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// Robot classes
#include <librealsense2/rs.hpp>
#include <RealSense.h>

// Main program
int main(int argc,char ** argv)
{

    //bool doPlayback = false;
    bool doPlayback = true;

    rs2::frameset frames;
    rs2::frame depth;
    rs2::colorizer color_map;

    // RealSense
    //auto pipe = std::make_shared<rs2::pipeline>();
    std::shared_ptr<rs2::pipeline> pipe = std::make_shared<rs2::pipeline>();
    rs2::config cfg; // Declare a new configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    if (doPlayback)
    {
        cfg.enable_device_from_file("a.bag");
    } else {
        cfg.enable_record_to_file("a.bag");
    }
    pipe->start(cfg);
    rs2::device device = pipe->get_active_profile().get_device();

    // Frame
    cv::Mat frame(cv::Size(640,480), CV_8UC3);

    // Main loop
    while (true)
    {

        // Clear frame
        frame = cv::Scalar(0,0,0);

        if (device.as<rs2::playback>())
        {
              //rs2::playback playback = device.as<rs2::playback>();
              if (pipe->poll_for_frames(&frames)) // Check if new frames are ready
              {
                  //depth = color_map(frames.get_depth_frame()); // Find and colorize the depth data for rendering
                  //frame = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)depth.get_data(), cv::Mat::AUTO_STEP);

                  rs2::frame colorFrame = frames.get_color_frame();
                  cv::Mat color(cv::Size(640, 480), CV_8UC3,
                                (void*)colorFrame.get_data(), cv::Mat::AUTO_STEP);

                  const rs2::frame depth_frame = frames.get_depth_frame(); // Find depth data
                  rs2::frame depth = color_map(depth_frame); // Find and colorize the depth data

                  //frame = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
                  frame = color;
              }

        } else {
            frames = pipe->wait_for_frames(); // wait for next set of frames from the camera
            //depth = color_map.process(frames.get_depth_frame()); // Find and colorize the depth data
            rs2::frame colorFrame = frames.get_color_frame();
            cv::Mat color(cv::Size(640, 480), CV_8UC3,
                          (void*)colorFrame.get_data(), cv::Mat::AUTO_STEP);

            const rs2::frame depth_frame = frames.get_depth_frame(); // Find depth data
            rs2::frame depth = color_map(depth_frame); // Find and colorize the depth data

            //frame = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
            frame = color;
        }

        // Output - display - record
        imshow("Live", frame);

        // User input (This pause is required to show the frame)
        int key = cv::waitKey(5);

        // Process user input
        if (key==97) { break; } // a

   }
   pipe->stop();
    return 0;
}
