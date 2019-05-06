# Actionlib_tutorials
So actionlib packages act like an API system it provide tools to create server to execute long running goal that could be preemted and also client to send request to server. <br />

_The action client and Action server communicate via ros messages .<br />
the client and server provides a simple API for user to request goal(on client side) or execute goal (on server side)_<br />
The client_server interaction will be like<br />
![Markdown Logo](http://wiki.ros.org/actionlib?action=AttachFile&do=get&target=client_server_interaction.png)

___
## Creating action_messages
**So first we have to define**
* **goal** -----so here action client send goals to the action server o accomplish our tasks<br />
* **result** --------A result is sent from the ActionServer to the ActionClient upon completion of the goal.As it is send exactly once <br />
* **feedback messages**--------------Feedback provides server implementers a way to tell an ActionClient about the incremental progress of a goal <br />
  >And this action messages will automatically genarate from **.action** file.
  And the **.action file** has the _goal defination_ followed by _result defination_ and followed by _feed back defination_ 
  and each portion are separated by three underscores(\_\).<br />

As an example:-
```
#goal definition
int32 order
---
#result definition
int32[] sequence
---
#feedback
int32[] sequence
```
so in the server/client just define goal/result/feedback .<br />
while taking the data or publishing write like this 
* goal.order
* result.sequence[]
* feedback.sequence[] <br />
___
## server_code
```
    #include <ros/ros.h>
    #include <actionlib/server/simple_action_server.h>//library used for implementing the simple action
    #include <actionlib_tutorials/FibonacciAction.h>/*this include the action yhe action message genarated from the*/ 
    
    class FibonacciAction
   {
    protected:
   
     ros::NodeHandle nh_;// node_handle is just as like creating or defining nodes
     actionlib::SimpleActionServer<actionlib_tutorials::FibonacciAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs. **Here actually a Action_server is defined**
     std::string action_name_;  //a string action_name_ has been defined
     // create messages that are used to published feedback/result
     actionlib_tutorials::FibonacciFeedback feedback_;
     actionlib_tutorials::FibonacciResult result_;
   
   public:
   /* here action_server takes 4 arguments first node handle then name of the node the an optionally executeCB function and a boolean value*/
     FibonacciAction(std::string name) :
       as_(nh_, name, boost::bind(&FibonacciAction::executeCB, this, _1), false),
       action_name_(name) // here in action_name_ (name= fibonacci that was defined in  main function )is stored here.
    {
       as_.start();// action_server as_ started
     }
   
     ~FibonacciAction(void)
     {
     }
   /* The callback function is passed a pointer to the goal message. Note: This is a boost shared pointer, given by appending "ConstPtr" to the end of the goal message type. */
     void executeCB(const actionlib_tutorials::FibonacciGoalConstPtr &goal)
     {
       // helper variables
       ros::Rate r(1);
    bool success = true;
   /*
   the sequence is computed at a rate of 1 hz
   .clear() is used to clear all the data from a vector
   .pushback() push the datas from the backs to a vector
   and c_str() makes a pointer to  a string terminated to a null pointer.
   ie if Ros::String s1="aditya"
   pf("s1.c_str[1]")=d
   pf("s1.c_str[]")=aditya
   
   */
       // push_back the seeds for the fibonacci sequence
     feedback_.sequence.clear();
       feedback_.sequence.push_back(0);
       feedback_.sequence.push_back(1);
       
   
       // publish info to the console for the user
       ROS_INFO("%s: , creating fibonacci sequence of order %i with seeds %i, %i", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);
   
       // start executing the action
       for(int i=1; i<=goal->order; i++)
       {
         // check that preempt has not been requested by the client
        if (as_.isPreemptRequested() || !ros::ok())
         {
           ROS_INFO("%s: Preempted", action_name_.c_str());
          // set the action state to preempted
           as_.setPreempted();
          success = false;
           break;
         }
         feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i-1]);
         // publish the feedback
         as_.publishFeedback(feedback_);
         // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
         r.sleep();// some times it may happen that the data coming from the clint in more speed than executing from server for that sleep() command is used.
      }
   
       if(success)
     {
         result_.sequence = feedback_.sequence;
         ROS_INFO("%s: Succeeded", action_name_.c_str());
       // set the action state to succeeded
        as_.setSucceeded(result_);
       }
    }
  
   
  };
   
   
   int main(int argc, char** argv)
   {
     ros::init(argc, argv, "sudip");
   
    FibonacciAction fibonacci("sudip");
     ros::spin();
   
    return 0;
   }

```
spin() just lets all the callbacks get called for your subscribers<br />
when you do have a subscriber, all of your code runs then you put a spin() at the end to keep the program from just exiting when it reaches the end of main(). Instead of exiting, a loop continuously runs to allow the callbacks to be called when a new message arrives. To be clear, ROS will not process any callback until spin() is called. <br />
there is a detailed discussion about ros::spin()     
  [ros::spin](http://wiki.ros.org/roscpp/Overview/Callbacks%20and%20Spinning)
___
## Simple_Action_Client
```


```



___
>So you have to change the the CMakeLIst.txt file too:<br />
After changing the ultimate **CMakeList.txt** file will be look like:<br />
```
cmake_minimum_required(VERSION 2.8.3)
project(actionlib_tutorials)

find_package(catkin REQUIRED COMPONENTS roscpp actionlib actionlib_msgs)
find_package(Boost REQUIRED COMPONENTS system)

add_action_files(
  DIRECTORY action
  FILES Fibonacci.action
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs
)

catkin_package(
  CATKIN_DEPENDS actionlib_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(fibonacci_server src/fibonacci_server.cpp)

target_link_libraries(
  fibonacci_server
  ${catkin_LIBRARIES}
)

add_dependencies(
  fibonacci_server
  ${actionlib_tutorials_EXPORTED_TARGETS}
)
```
 * Do not forget to add actionlib_msgs in the CMakeList.txt
 * And add <br />
 >first add_executable followed by target_link_libraries followed by add_dependences
 
 
 
 
