
#include "RealSense.h"

RealSense::RealSense(bool playback)
{
  cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
  cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

  if (playback)
  {
      cfg.enable_device_from_file("a.bag");
  } else {
      cfg.enable_record_to_file("a.bag");
  }
  pipe->start(cfg);
  device = pipe->get_active_profile().get_device();
}

RealSense::~RealSense ()
{
  pipe->stop();
}

cv::Mat RealSense::getColor()
{
  cv::Mat frame(cv::Size(640,480), CV_8UC3);
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
            rs2::frame depth = color_map.process(depth_frame); // Find and colorize the depth data

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
      rs2::frame depth = color_map.process(depth_frame); // Find and colorize the depth data

      //frame = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
      frame = color;
  }
  return frame;
}
