#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<iostream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>

#include <cv_bridge/cv_bridge.h>


using namespace std;
using namespace cv;


int main(int argc ,char ** argv	)
{

	ros::init(argc, argv, "image_publisher");
  	ros::NodeHandle nh;
  	image_transport::ImageTransport it(nh);
	 image_transport::Publisher pub = it.advertise("camera/image", 1000);

	namedWindow("win",0);
	VideoCapture Video(0);//if you want any video from your folder then replace 0 by it's name
	Mat frame;
	


	sensor_msgs::ImagePtr msg;

  	ros::Rate loop_rate(5);
  	while (nh.ok()) 
  	{
	  	Video>>frame;
	    // Check if grabbed frame is actually full with some content
	    if(!frame.empty())
	     {
	      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
	      pub.publish(msg);
	      imshow("win",frame);
	      waitKey(1);
	     }

	    ros::spinOnce();
	    loop_rate.sleep();
	}
}


