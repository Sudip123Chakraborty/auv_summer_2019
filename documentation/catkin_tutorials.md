# Catkin_tutorials

 ## Create and buid workspace
 * 1st you have to setup your enveromentby
 > source/opt/ros/kinetic/setup.bash
 
 * then create and build the workspace by 
 > $ mkdir -p ~/catkin_ws/src
 > $ cd ~/catkin_ws/
 > $ catkin_make
 
 * Running the catkin_make command first time will build<br />
   * build
   * devel
   * CMakeList.txt inside the source file
   
to make your enveroment setup with the new setup.*sh file in the **devel** folder type
> $ source devel/setup.bash

* you can see your ROS_PACKAGE_PATH environment by 
> $ echo $ROS_PACKAGE_PATH:<br />

you will see something like it:<br />


> /home/youruser/catkin_ws/src:/opt/ros/kinetic/share

## Creating ros_package
For a package to be considered a catkin package it must meet a few requirements:

    The package must contain a catkin compliant package.xml file.
        That package.xml file provides meta information about the package. 

    The package must contain a CMakeLists.txt which uses catkin.

        If it is a catkin metapackage it must have the relevant boilerplate CMakeLists.txt file. 
    Each package must have its own folder
        This means no nested packages nor multiple packages sharing the same directory. 
        
  
  
  ## creating a catkin_packaget
  after creating the catkin_ws 
  
  now to make a new catkin package 
  Use the catkin_create_pkg script to create a new package called 'beginner_tutorials' which depends on std_msgs, roscpp, and rospy:

 > $ catkin_create_pkg beginner_tutorials std_msgs rospy roscpp
 
 
 
 * now build the workspace again by
 > $ cd catkin_ws
 > $ catkin_make
 
 
  
