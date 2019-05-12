# CMakeList.txt Tutorials ([link](https://cmake.org/cmake-tutorial/)):

**why cmake ?**([link](https://prateekvjoshi.com/2014/02/01/cmake-vs-make/))

CMake stands for Cross-platform Make. CMake recognizes which compilers to use for a given kind of source. In case you didn’t know, you can’t use the same compiler to build all the different kinds of sources. You can do this manually every time you want to build your project, but it would be tedious and painful. CMake invokes the right sequence of commands for each type of target. Therefore, there is no explicit specification of commands like $(CC).
___
**CMakeList.txt**
* this file begin with the name of the minimun version required for generating **makefile for that code**.
* then in the paranthesis of **project()** we have to give the name of the package
> cmake_minimum_required(VERSION 2.8.3)<>br /
> project(actionlib_tutorials)
### Finding the library
**find_package([link](https://cmake.org/cmake/help/v2.8.8/cmake.html#command%3afind_package))**
First, CMake needs to find the library. For catkin dependencies, this is easy:<br />
the structure of find_package looks like:
```
find_package(<package> [version] [EXACT] [QUIET] [MODULE]
               [[REQUIRED|COMPONENTS] [components...]]
               [OPTIONAL_COMPONENTS components...]
               [NO_POLICY_SCOPE]
```
> Finds and loads settings from an external project. <package>_FOUND will be set to indicate whether the package was found.<br />
> The QUIET option disables messages if the package cannot be found.<br />
> The REQUIRED option stops processing with an error message if the package cannot be found.<br />
  A package-specific list of required components may be listed after the COMPONENTS option or directly after the REQUIRED option <br />
  
 
  

> find_package(catkin REQUIRED COMPONENTS roscpp)


example:
> find_package(catkin REQUIRED COMPONENTS roscpp actionlib actionlib_msgs)
 
* here you have to give all the dependences of the package

* This find_package() call defines CMake variables that will be needed later for the compile and linkedit steps. List all additional catkin dependencies in the same command:
___
###################################
## catkin specific configuration ##
###################################<br />
The **catkin_package()** command is only called once. In addition to any other parameters, <br />
> it must declare the non-catkin system library and header packages needed by the interfaces you export to other ROS packages:


* Note tha this dependencies you would already declared in the **find_package**.




```
* The catkin_package macro generates cmake config files for your package
* Declare things to be passed to dependent projects
* INCLUDE_DIRS: uncomment this if your package contains header files
* LIBRARIES: libraries you create in this project that dependent projects also need
* CATKIN_DEPENDS: catkin_packages dependent projects also need
* DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
* INCLUDE_DIRS include
*  LIBRARIES actionlib_tutorials
* CATKIN_DEPENDS actionlib actionlib_msg message_generation roscpp rospy std_msgs
*  DEPENDS system_lib
)
```
___
### Include directories
Before compiling, collect all the header paths you found earlier using find_package():<br />


> include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

* The include parameter is needed only if that subdirectory of your package contains headers used to compile your programs.
```
 ## Specify additional locations of header files
 ## Your package locations should be listed before other locations
  include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  #${Boost_INCLUDE_DIRS}
```
)

___
### declaring messages services and actoin from this packages.
To declare and build messages, services or actions from within this package:
```
* Let MSG_DEP_SET be the set of packages whose message types you use in
*   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
 * In the file package.xml:
   * add a build_depend tag for "message_generation"
   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
     but can be declared for certainty nonetheless:
     * add a exec_depend tag for "message_runtime"
 * In this file (CMakeLists.txt):
   * add "message_generation" and every package in MSG_DEP_SET to
     find_package(catkin REQUIRED COMPONENTS ...)
   * add "message_runtime" and every package in MSG_DEP_SET to
     catkin_package(CATKIN_DEPENDS ...)
   * uncomment the add_*_files sections below as needed
     and list every .msg/.srv/.action file to be processed
   * uncomment the generate_messages entry below
   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

``` 
add this three things: in this order::

* add_dependencies(name_of_the_node $(package_name_EXPORTED_TARGETS))
* add_executable(name_of_the_node path_w_r_t_cmakelist.txt)
* target_link_libraries(name_of_the_node ${catkin_LIBRARIES}) 




so your final CMakeList.txt will loke like as:
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



add_executable(fibonacci_client src/fibonacci_client.cpp)

target_link_libraries( 
  fibonacci_client
  ${catkin_LIBRARIES}
)

add_dependencies(
  fibonacci_client
  ${actionlib_tutorials_EXPORTED_TARGETS}
)
add_executable(averaging_server src/averaging_server.cpp)
target_link_libraries(averaging_server ${catkin_LIBRARIES})
add_dependencies(
  averaging_server
  ${actionlib_tutorials_EXPORTED_TARGETS}
)

add_executable(averaging_client src/averaging_client.cpp)
target_link_libraries(averaging_client ${catkin_LIBRARIES})

add_dependencies(
  averaging_client
  ${actionlib_tutorials_EXPORTED_TARGETS}
)

```















