# CMakeList.txt Tutorials ([link](https://cmake.org/cmake-tutorial/)):

**why cmake ?**([link](https://prateekvjoshi.com/2014/02/01/cmake-vs-make/))

CMake stands for Cross-platform Make. CMake recognizes which compilers to use for a given kind of source. In case you didn’t know, you can’t use the same compiler to build all the different kinds of sources. You can do this manually every time you want to build your project, but it would be tedious and painful. CMake invokes the right sequence of commands for each type of target. Therefore, there is no explicit specification of commands like $(CC).
___
**CMakeList.txt**
* this file begin with the name of the minimun version required for setting up **make_file for that code**
