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
    *  Faster  R-CNN uses a convolutional neural network to draw accurate andprecise bounding boxes around target objects
    
    ___
# 3.National University of Singapore - Special Award (Static Judging):([Link](https://robonation.org/sites/default/files/MontanaStateUni_2016_RoboSub_Journal.pdf)):

There work flow <br />
![image](https://github.com/Sudip123Chakraborty/auv_summer_2019/blob/master/documentation/newname.jpg)

* Bumblebees software stack runs on the open source messagepassing  interface,  Robot  Operating  System  (ROS)  which  inturn  runs  on  top  of  Linux. 

## A. Mission Planner:
* The mission planner is implemented using Finite State Ma-chines and a graph walking algorithm
 * Finite State Machinesare  used  because  each  task  in  the  mission  sequence  can  berepresented  as  its  own  individual  states  with  known  inputsand a deterministic set of outcomes.
## B. Navigation:
* All  the sensors are  interfaced and integrated  with therest  of  the  system  over  the  ROS  IPC  framework.
* An errorstate  Kalman  Filter  is  used  to  obtain  much  higher  accuracythan  each  sensor  is  able  to  provide  independently.
* Since error variables are used as the state vector, nonlinearities can be canceled through using traditiional full scale KF.
## c. Compuer Vision:
Basic vision processing pipeline can be divided into 4 main stages:
> preprocessing <br />
> enhancement<br />
> detection <br />
> track-ing.<br />

**Chalanges over operating the boat**
1. Non uniform illumination.<br />
2. Colour degradation.<br />
**Solution**
* preprocess the images with homomorphic filtering toremove  flickering  effect,  gamma  correction.<br />
* Gray-Worldalgorithm  to  recover  original  color  of  the  images.<br />
* Saliencyregion detection enables us to operate on objects that pop-up to the human vision system and this information is used         as aprimary  filter  to  remove  artifact  noises  and  other  features  in TRANSDEC .<br />

## D. Imaging Sonar:
* Multi-sensory  approach  to  tracking  and  localization  isadopted,  using  the  camera,  sonar  and  vehicle  POSE  andvelocity. In order for the sensor fusion to work, a calibrationstep  is  performed  to  obtain  the  relationship  between  sonar,camera and vehicular dynamic.
* Various filters and thresholding techniques are used on thesonar  image  to  extract  objects  of  interest,  before  applyingfeature  tracking  methods  such  as  Lucas-Kanade  tracking  onthese  objects.

* Once  we  determine  that  an  object  is  to  be  tracked,  we **initialize a particle filter with the 3D position and velocities** ofthe  object  in  the  **sonar  frame**,  with  **low  uncertainty  in  R and θ**,  but  **higher  uncertainty  in φ**
*  The  particle  update  model  is based  on  **vehicular  dynamics**,  obtained  from **DVL  and  IMU**.
* Once the update step is done, these 3D points are projectedinto  both  sonar  and  camera  image  Each  particle  is  assigned a weightage based on **several heuristics**,
```
1. Intensity 
1. Andoptical velocity of the sonar pixel 
1. The object dimensions 
1. camera  pixel  color.
```
___

# 4.Northwestern Polytechnical University - Special Award (Best New Team):([Link](https://robonation.org/sites/default/files/NorthwesternPolytechTeamAUV_2016_RoboSub_Journal.pdf))

The  software  of  NEMO  II  can  be  roughly divided  into   two part:


|sl.no|name|work|
|-----|----|----|
|1|control sub system team|The  control  sub-system  is  supposed  to decide when to launch and when to cut off energy, how  to  operate  maneuvering  and  at  which  to change  to following tasks, based on the external and   internal information that   observed.|
|2|vision sub system team|The vision sub-systemis designed to give the vehicle  up-to-date and accurate data about the surrounding  mission  elements|

* The software   architecture   of   control   sub-system   is   built   upon   **Visual   Studio   MFC framework**,   written   in **C/C++**
* they have used the tools used  in opencv .

___
# 5.North Carolina State University:([Link](https://robonation.org/sites/default/files/NorthCarolinaStateUni_2016_RoboSub_Journal.pdf))
**SVR(Seawolf Video Route)**<br />
Seawolf VI features a streaming video router called SVR (Seawolf Video Router).SVR allows for efficient handlingof multiplevideo  stream  sources,  and allows  for  the  creation  of live debug video streamswhich can be monitoredremotelyoveranetworkconnection to Seawolf VI


## A.Vision Processing:
* The vision  application  takesimages  from  SVR  and interprets  them  by  looking  for  objects. Examples  of  objects include  buoys,  the  gate,  and  a  pathmarker,bins and  thehedge object
* To recognize   these   objects,   Seawolf   uses   a   set   of   OpenCV algorithms including adaptive thresholding, the Canny Edge detector, and the Hough Transform.
## B.Vision Processing:
* Seawolf  ’s  mission  controlsubsystem  utilizes  vision and sensor data in order to make all the decisions necessary to complete tasks.
* When a mission is completed, mission control progresses on to the next linearly.Each mission has its own logic code that  navigates  the  robot  and  positions it  for  the next task.
* These  navigation commands  are  given  to  the  PID controller subsystem, which controls the values to be set to each thruster.
* PID  is  a  **common  control  loop algorithm**  which  uses  three  terms: **proportional**,  **integral**  and **derivative**;
* Seawolf  VI  has  **four**  PID controllers
> yaw<br />
>depth<br />
>pitch<br />
>roll movements<br />
of   the robot. 
## SerialApplication:
The   serial application handles communication to and from the microcontroller and other sensors except for the cameras, which communicate directly to the SVR. T**he serial application goes through each serial interfaces and deduces which device it is connected to. It then starts the correct driver for each serial device.**


**They wrote programe in openGL**

___
## 6. Oregon Institute of Technology, OTUS/AUVSI Club:([Link](https://robonation.org/sites/default/files/OregonTech_2016_RoboSub_Journal%20%281%29.pdf)):

The machine codes running in the robot on target computer are downloaded after compiling Simulink with Embedded MATLAB files through the host laptop computer, equipped Real-time Workshop and with 2010 VC++ compiler and later updated by Windows SDK 7.1.

## 7.Northwestern Polytechnical University:([Link](https://robonation.org/sites/default/files/NorthwesternPolyUniTeamNACIT_2016_RoboSub_Journal.pdf)):

The software system of Paxer consists of two-tierstructures of the:<br />

|Name|work|
|----|----|
|host computer (HC)| The host computer is operation command center of the vehicle and responsible for dealing with the information|
|slave computer(SC)|slave computer uploads, judging and deciding the actions, then sending instructions to the slave computer which will then reassign to the execution mechanism including thrusters, grabber and so on to accomplish the given task|








