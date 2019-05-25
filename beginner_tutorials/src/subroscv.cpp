#include <ros/ros.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include "opencv2/videoio/videoio.hpp"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
using namespace std;
using namespace cv;

Mat img,src_gray;
int max_thresh = 255;
RNG rng(12345);

int thresh =40;
int AREA=200;


void thresh_callback();

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{ 

  try
  { 
     
     img =(cv_bridge::toCvShare(msg, "bgr8")->image).clone();

     cvtColor( img, src_gray, cv::COLOR_RGB2GRAY );
     blur( src_gray, src_gray, Size(3,3) );
     namedWindow("original",1);

     imshow("original",img);

      thresh_callback();
     
     createTrackbar( " Canny thresh:", "original", &thresh, 255 );
     createTrackbar( " Canny thresh:", "original", &AREA, 255 );
     
     waitKey(1);

     



   

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}








int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  namedWindow("view");
  startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);
  ros::spin();
  destroyWindow("view");
  return 0;
}



void thresh_callback()
{
  Mat canny_output(img.rows,img.cols,CV_8UC1,Scalar(0 ));
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  //Mat binary(img.rows,img.cols,CV_8UC1,Scalar(0 ));

  Mat binary(src_gray.rows,src_gray.cols,CV_8UC1,Scalar(0));

     for(int i=0;i<src_gray.rows;i++)
     {
      for(int j=0;j<src_gray.cols;j++)
      { 
        if((src_gray.at<uchar>(i,j))<thresh)
        {
          binary.at<uchar>(i,j)=0;
        }
        else binary.at<uchar>(i,j)=255;
      }
     }

  /// Detect edges using canny
  Canny( binary, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  /*for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }*/


// For calculating center of the contour
for (unsigned int i = 0;  i < contours.size();  i++)
    {
     


    if(contourArea(contours[i])>AREA)
    {
     	Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     
      
         ////////////////////
          	 vector<Moments> mu(contours.size() );
            	 for( int i = 0; i < contours.size(); i++ )
               	 mu[i] = moments( contours[i], false ); 

      /*************** calculation of the center of the gate*******************/
            	vector<Point2f> mc( contours.size() );
            	for( int i = 0; i < contours.size(); i++ )
		       { 
		          mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); 
				} 

			int flag=mc[i].x;
			int flag1=mc[i].y;
				for(int l=flag-1;l<flag+2;l++)
				{
					for(int m=flag1-1;m<flag1+2;m++)
						{
						drawing.at<Vec3b>(m,l)={255,255,255};			
						}			
				}
		cout<<"the center of the contour is:"<<mc[i].x<<","<<mc[i].y<<endl;
	}
	}
//double area1 = contourArea(contours);
//cout<<area1;
  /// Show in a window
     namedWindow("binary",1);
     imshow("binary",canny_output);
  namedWindow("source",1);
  imshow( "source", drawing );

  waitKey(1);
    
}
