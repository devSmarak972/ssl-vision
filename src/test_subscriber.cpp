#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
ros::Time last_msg_time_;
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
            ros::Time current_time = ros::Time::now();
    std::cout<<"CALLBACK CALLED"<<std::endl;
    cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    cv::waitKey(30);
    double acquisition_time = (current_time - last_msg_time_).toSec();
    last_msg_time_ = current_time;

    ROS_INFO("Data acquisition time: %.4f seconds", acquisition_time);

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}
// void imageCallback(const sensor_msgs::ImageConstPtr& msg)
// {
 

//   cv_bridge::CvImagePtr cv_ptr;
   
//   try
//   { 
   
//     // Convert the ROS message  
//     cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
     
   
//     cv::Mat current_frame = cv_ptr->image;
     
//     // Display the current frame
//     cv::imshow("view", current_frame); 
     
//     // Display frame for 30 milliseconds
//     cv::waitKey(30);
//   }
//   catch (cv_bridge::Exception& e)
//   {
//     ROS_ERROR("Could not convert from '%s' to 'bgr8'.\n%s", msg->encoding.c_str(),e.what());
//   }
// }
int main(int argc, char **argv)
{
  std::cout<<"Inside main"<<std::endl;
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::startWindowThread();
  last_msg_time_ = ros::Time::now();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/pylon_camera_node/image_raw", 1, imageCallback);
  std::cout<<"subsrcibed\n";
  ros::spin();
  cv::destroyWindow("view");
}