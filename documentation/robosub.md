# ROBOSUB 2k16

## 1. McGill University - _SEVENTH PLACE & Special Award (Static Judging)_ :([link](https://robonation.org/sites/default/files/McGillUni_2016_RoboSub_Journal.pdf))
They have improve their software skill by iterating over  last  year’s  design  and  <br />
architectureto  allow  for  the  reusability  of  high  level  components  onMcGill  Robotics’ <br />
new  autonomous  Drone  with  a  minimalamount of modification.<br />

## A. Computer vision <br />

* the computer vision pipeline was completely rewritten thisyear  to  make  use  of  a <br />
**machine  learning**  approach  ratherthan   a   filter   based   approach
  *    This   allows   for   a   moreflexible object recognition module applicable to any imageclassification problem.
* Intensify the featuresof the image to recover details lost due to underwater hazeand color cast.
* The  artificial  neural  network  then  takes  the  SURF features  of  multiple  areas  of  
the  preprocessed  image  andclassifies  them  based  on  previously  seen  data  from  pastcompetitions to locate regions of interest in the frame.
## B. Sonar
* They have devoloped a sonar scan pipleline that can give a **360 degree** view through **Tritech micron scaner**
  * Applying **adaptive threshoulding** and **mean shift clustering algorithm** on the obtained circlar scans localized point of interest.


## C. State Estimation
* The  State  Estimation  system  receives  data  from  theInertial Measurement Unit, Sonar, depth sensor and camerasto  synthesize  useful  information
for  the  Autonomy  andControls systems.
* The  on-board  IMU,  the  X-IMU  from  x-io  Technologies,provides 9 degrees of freedom measurements directly to themain computer through USB
  * System uses an Extended Kalman Filter to fusethe data from the accelerometers, gyroscopes, and magne-tometer  and  generates  a  stable  estimate  of  the  orientationof the vehicle
* Using  the  downward  facing  camera  with  a  Visual  **SLAMalgorithm**  ,  the  position  and  pose  of  the  robot  is  esti-mated.

## D. Planner and Controls
* The  planner  is  the  strategical  component  of  the  robot,sending commands to the other software modules in orderto  complete  the  desired  tasks. 
  *The  mission  planner  wasre-written  using  ROS’  SMACH  library  
  
  ___
  # 2.Montana State University([Link](https://robonation.org/sites/default/files/MontanaStateUni_2016_RoboSub_Journal.pdf))
  * They have done the whole things in **ROS** and the code was written in **python**
  * Used **exteneded kalmen filter ** for path estimation 
  *The downward stereo camerasprovide odometry information using an library called libviso2.
    * This  is  able  to  construct  a  3D  point  cloud  of  the  bottomof the pool using the disparity between the images
  * They use **faster R-CNN** for object detecting.
    *.  Faster  R-CNN uses a convolutional neural network to draw accurate andprecise bounding boxes around target objects
    
    ___
# 3.National University of Singapore - Special Award (Static Judging):([Link](https://robonation.org/sites/default/files/MontanaStateUni_2016_RoboSub_Journal.pdf)):


    
