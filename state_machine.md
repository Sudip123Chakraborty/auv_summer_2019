# State Machine(smach)
smach(state machine) is a task-level architecture for rapidly creating complex robot behavior. At its core, SMACH is a ROS-independent Python library to build hierarchical state machines. <br />

## when should one use smach?
SMACH is useful when you want a robot to execute some complex plan, where all possible states and state transitions can be described explicitly
* **Fast prototyping:** The straightforward Python-based SMACH syntax makes it easy to quickly prototype a state machine and start running it.
* **Complex state machines:** SMACH allows you to design, maintain and debug large, complex hierarchical state machines. You can find an example of a complex hierarchical state machine here. 
* **Introspection:** SMACH gives you full introspection in your state machines, state transitions, data flow, etc. See the smach_viewer for more details. 
## you should not use smach when:
* **Unstructured tasks:** SMACH will fall short as the scheduling of your task becomes less structured.

* **Low-level systems:** SMACH is not meant to be used as a state machine for low-level systems that require high efficiency, SMACH is a task-level architecture. 
## smach viewer:
The smach viewer is a GUI that shows the state of hierarchical SMACH state machines. It can visualize the possible transitions between states, as well as the currently active state and the values of user data that is passed around between states. The smach viewer uses the SMACH debugging interface based on the **smach messages** to gather information from running state machines.<br />
* **graph view**
* **depth view**
* **tree view**
* The image below shows an example state machine used to coordinate actionlib actions that allow the PR2 robot to charge itself at a standard outlet. <br />
![](http://wiki.ros.org/pr2_plugs_executive?action=AttachFile&do=get&target=smach.png)


**smach messages**
* The smach messages are only used for communication between the introspection server and the smach viewer, and are considered part of the internal ROS API. 
    * [SmachContainerInitialStatusCmd](http://docs.ros.org/api/smach_msgs/html/msg/SmachContainerInitialStatusCmd.html)
    * [SmachContainerStatus](http://docs.ros.org/api/smach_msgs/html/msg/SmachContainerStatus.html)
    * [SmachContainerStructure](http://docs.ros.org/api/smach_msgs/html/msg/SmachContainerStructure.html)






___
**An example of smach package**

>   import rospy <br />
    import smach
* we have to import this things to connect with ros
  * in this example it is not going to intereact with ros though we are importing this things
  ___
 ```
     # define state Foo
     class Foo(smach.State):
       def __init__(self):
           smach.State.__init__(self, outcomes=['outcome1','outcome2'])
           self.counter = 0
   
       def execute(self, userdata):
           rospy.loginfo('Executing state FOO')
           if self.counter < 3:
               self.counter += 1
               return 'outcome1'
           else:
               return 'outcome2'
               
  ```
  * this is class which inheritated the predefined **smach.state** class
    * then **smach.State.__init__** where you initiatate the state with the possible outcome that the robot may have.
    * outcomes are only the strings
  * then **executed** is the code that has to be executed when robot is in that state
  ```
  # define state Bar
   class Bar(smach.State):
       def __init__(self):
           smach.State.__init__(self, outcomes=['outcome2'])
   
       def execute(self, userdata):
           rospy.loginfo('Executing state BAR')
           return 'outcome2'
  ```
  * this another class that inheritate the same class and it's structure is same as that of the previous one.
    * here the Foo state have two outcome possible where the Bar has ony one.
  ```
  # main
   def main():
       rospy.init_node('smach_example_state_machine')
   
       # Create a SMACH state machine
       sm = smach.StateMachine(outcomes=['outcome4', 'outcome5'])
   
       # Open the container
       with sm:
           # Add states to the container
           smach.StateMachine.add('FOO', Foo(), 
                                  transitions={'outcome1':'BAR', 
                                               'outcome2':'outcome4'})
           smach.StateMachine.add('BAR', Bar(), 
                                  transitions={'outcome2':'FOO'})
   
       # Execute SMACH plan
       outcome = sm.execute()
   
   
 

  ```
  * here in this function main it is defined how the nodes are connected
    * here we create the ros node
    * then we are creating the real state machine by
    > sm = smach.StateMachine(outcomes=['outcome4', 'outcome5'])
                                               
     * every state machine can provide a outcome .
      * so when state machine is ended it will return the outcomes.
    > with sm:<br />
   *  with  in state machine we are adding two states which was previously empty then we added two state
    > smach.StateMachine.add('Name of the state',What kind os state, 
                                  transitions={'outcome1':'BAR', 
                                               'outcome2':'outcome4'})
   * so here we have to specify the transittions when the robot will be on that state.
  * then please jump to the outcome which is lebbel "bar " or "outcome 4"
  * thus we connect one state to oother state
  
  > if __name__ == '__main__':<br />
 main()
 
 * here we are calling the main function .
 ___
 
 ## passing user data between state
 
 
 ___
 ## Creating a Hierarchical State Machine
 
 
