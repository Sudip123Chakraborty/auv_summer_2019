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
![image](http://wiki.ros.org/pr2_plugs_executive?action=AttachFile&do=get&target=smach.png)

* The red boxes show the possible outcomes of the state machine container: outcome4 and outcome5. 



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
  * thus we connect one state to oother state <br />
![image](http://wiki.ros.org/smach/Tutorials/Getting%20Started?action=AttachFile&do=get&target=simple.png)

* The red boxes show the possible outcomes of the state machine container: outcome4 and outcome5. 


  
  > if \__name__ == '\__main__':<br />
 main()
 
 * here we are calling the main function .
 ___
 
 ## passing user data between state
 
 * here user data means basically the input and out put keys. or the input and output data of a state machine.
 ```
  class Foo(smach.State):
     def __init__(self, outcomes=['outcome1', 'outcome2'],
                        input_keys=['foo_input'],
                        output_keys=['foo_output'])

 ```
 here while initiating the state machine we have also mentioned the user data as:
 * input keys --that is needed for  a state to run
 * output keys -- that a state should provide after the  state is ended.
 * the interface of a stste machine will be ike:
 ![image](http://wiki.ros.org/smach/Tutorials/User%20Data?action=AttachFile&do=get&target=user_data_single.png)
 
 ## connecting user data
 when you a add multiple state in your state machine then you should mention their connectivity and their data exchange relation<br /> 
 their cames **re mapping concepts**
 ```
 sm_top = smach.StateMachine(outcomes=['outcome4','outcome5'],
                          input_keys=['sm_input'],
                          output_keys=['sm_output'])
  with sm_top:
     smach.StateMachine.add('FOO', Foo(),
                            transitions={'outcome1':'BAR',
                                         'outcome2':'outcome4'},
                            remapping={'foo_input':'sm_input',
                                       'foo_output':'sm_data'})
     smach.StateMachine.add('BAR', Bar(),
                            transitions={'outcome2':'FOO'},
                            remapping={'bar_input':'sm_data',
                                       'bar_output1':'sm_output'})
 ```
 * as in this state machine their are multiple  state so we just not only initiatate it with possible outcomes we initiatate with  userdata.
 * here in the state the remapping of the datas are also shown and their transition state.
 > in remapping we make both the datas pointing to a certain value .<br />
 means make those data equal to each other.
 
 
 * so if I make **foo_output**=**sm_output**
 thats means **sm_output**=**foo_output**
 * both the datas change simultaneously to a certain value.<br />
 
 In the above example the state and their data exchange are related to like this one:
 ![image](http://wiki.ros.org/smach/Tutorials/User%20Data?action=AttachFile&do=get&target=user_data.png)
 
 
 ___
 ## Creating a Hierarchical State Machine
 **Creating some states**
 ```
       # State Foo
      class Foo(smach.State):
         def __init__(self, outcomes=['outcome1', 'outcome2'])
         
         def execute(self, userdata):
            return 'outcome1'
    
    
      # State Bar
     class Bar(smach.State):
        def __init__(self, outcomes=['outcome1'])
        
        def execute(self, userdata):
           return 'outcome4'
   
   
     # State Bas
     class Bas(smach.State):
        def __init__(self, outcomes=['outcome3'])
       
        def execute(self, userdata):
           return 'outcome3'
 
 ```
 * here Foo bar and Bas state are added
 
**Creating a hierarchical state machine**
```
      # Create the top level SMACH state machine
       sm_top = smach.StateMachine(outcomes=['outcome5'])
   
       # Open the container
       with sm_top:
   
           smach.StateMachine.add('BAS', Bas(),
                                  transitions={'outcome3':'SUB'})
   
           # Create the sub SMACH state machine 
           sm_sub = smach.StateMachine(outcomes=['outcome4'])
   
           # Open the container 
           with sm_sub:
   
               # Add states to the container 
               smach.StateMachine.add('FOO', Foo(),
                                      transitions={'outcome1':'BAR', 
                                                   'outcome2':'outcome4'})
               smach.StateMachine.add('BAR', Bar(),
                                      transitions={'outcome1':'FOO'})
   
           smach.StateMachine.add('SUB', sm_sub,
                                  transitions={'outcome4':'outcome5'})


```
* in this case note that 1st we create a **sm_top** state machine and initiatete it.
   * with in the **sm_top** we added **Bas** state and a **sm_sub** state machine 
      * **sm_sub** state machine contain to stae **Bar** and **Foo**.
* there connection looks like <br />
![image](http://wiki.ros.org/smach/Tutorials/Create%20a%20hierarchical%20state%20machine?action=AttachFile&do=get&target=sm_expanded.png)

## Calling Actions from a State Machine (ROS)
**Empty goal message**
```
   sm = StateMachine(['succeeded','aborted','preempted'])
    with sm:
        smach.StateMachine.add('TRIGGER_GRIPPER',
                                  SimpleActionState('action_server_namespace',
                                                 GripperAction),
                               transitions={'succeeded':'APPROACH_PLUG'})

```
**Fixed goal message**
please import these  librarie:   from smach_ros import SimpleActionState

### Fixexd goal message

> 
```
   sm = StateMachine(['succeeded','aborted','preempted'])
    with sm:
        gripper_goal = Pr2GripperCommandGoal()
        gripper_goal.command.position = 0.07
        gripper_goal.command.max_effort = 99999
        StateMachine.add('TRIGGER_GRIPPER',
                          SimpleActionState('action_server_namespace',
                                            GripperAction,
                                            goal=gripper_goal),
                          transitions={'succeeded':'APPROACH_PLUG'})```

```
 

Instead of writting **goal=gripper_goal** you can also write **goal_slot={ position,max_effort}** 

### goal from userdata
if you want to set goal from user data do like this:
```
sm = StateMachine(['succeeded','aborted','preempted'])
with sm:
    StateMachine.add('TRIGGER_GRIPPER',
                      SimpleActionState('action_server_namespace',
                                        GripperAction,
                                        goal_slots=['max_effort', 
                                                    'position']),
                      transitions={'succeeded':'APPROACH_PLUG'},
                      remapping={'max_effort':'user_data_max',
                                 'position':'user_data_position'})

```
so you have to declare goal_slots and connect their variables through remapping;<br />

if you to do it by goal_callback do it by like :
* first define goal_callback function with in the state machine:
```
with sm:
    def gripper_goal_cb(userdata, goal):
       gripper_goal = GripperGoal()
       gripper_goal.position.x = 2.0
       gripper_goal.max_effort = userdata.gripper_input
       return gripper_goal
```
then in the **SimpleActionState function add this argument instead of goal_slots**
> goal_cb=gripper_callback ---the name of the function<br />
> add input_keys=['gripper_input']<br />

so the final defination of adding the state will be like:
> StateMachine.add{"name_of_the_state_machine",SimpleActionState("action_server_name",GripperAction,goal_cb=name+of_the callback_function,inputkeys,transition,remapping)}<br />

## Viewing State Machines :
it is same as state machine viewer.
[state_machine_viewer](http://wiki.ros.org/smach/Tutorials/Smach%20Viewer)


## concurence state machine
**outcum_map**
```
cc = Concurrence(outcomes = ['outcome1', 'outcome2'],
                 default_outcome = 'outcome1',
                 input_keys = ['sm_input'],
                 output_keys = ['sm_output'],
                 outcome_map = {'succeeded':{'FOO':'succeeded',
                                             'BAR':'outcome2'},
                                'outcome3':{'FOO':'outcome2'}})
with cc:
    Concurrence.add('FOO', Foo())
    Concurrence.add('BAR', Bar())
```
 Once all the states in the concurrence have terminated, if one of these child-outcome mappings is satisfied, the concurrence will return its associated outcome. If none of the mappings are satisfied, the concurrence will return its default outcome. 
 <br />
 * in this example if **Foo** has outcome **succeeded** and **Bar** has outcome **outcome2** then the state machine output will be **succeded**
 * if one of this does not happen **(rather than Foo has outcome outcome2)** the state machine will terminate to it's default outcome.


## using call back 
```
# gets called when ANY child state terminates
def child_term_cb(outcome_map):

  # terminate all running states if FOO finished with outcome 'outcome3'
  if outcome_map['FOO'] == 'outcome3':
    return True

  # terminate all running states if BAR finished
  if outcome_map['BAR']:
    return True

  # in all other case, just keep running, don't terminate anything
  return False


# gets called when ALL child states are terminated
def out_cb(outcome_map):
   if outcome_map['FOO'] == 'succeeded':
      return 'outcome1'
   else:
      return 'outcome2'

```
it's graphical vaalue will be like 
![image](http://wiki.ros.org/smach/Tutorials/Concurrent%20States?action=AttachFile&do=get&target=concurrence2.png)

## sequence container
The Sequence container is a StateMachine container, extended with auto-generated transitions that create a sequence of states from the order in which said states are added to the container.<br />
A container Sequence has its outcomes, specified on construction, along with the 'connector_outcome' which is used for the automatic transitions. The constructor signature is:

> __init__(self, outcomes, connector_outcome):


### adding states
* But, each state added will receive an additional transition from it to the state which is added after it. The transition will follow the outcome specified at construction of this container.

* If one of the transitions given in the dictionary mapping parameter to 'Sequence.add()' follows the connector outcome specified in the constructor, the provided transition will override the automatically generated connector transition. <>br /
```
sq = Sequence(
        outcomes = ['succeeded','aborted','preempted'],
        connector_outcome = 'succeeded')
with sq:
    Sequence.add('MOVE_ARM_GRAB_PRE', MoveVerticalGripperPoseActionState())
    Sequence.add('MOVE_GRIPPER_OPEN', MoveGripperState(GRIPPER_MAX_WIDTH))
    Sequence.add('MOVE_ARM_GRAB',     MoveVerticalGripperPoseActionState())
    Sequence.add('MOVE_GRIPPER_CLOSE', MoveGripperState(grab_width))
    Sequence.add('MOVE_ARM_GRAB_POST', MoveVerticalGripperPoseActionState())
```
* so as you see in the sequence container the states are added in a sequence .they will gwt an autogenerated transition means if outcome **succeded** it will procceeded to the next state .
* but with in **Sequence.add()** if we add transition here than this will cancelled out the auto_genarated transition. 


> you have to  import the sequence type:<br />
> from smach import Sequence

## Iterator container

The iterator allows you to loop through a state or states until success conditions are met.<br />
> __init__(self, outcomes, input_keys, output_keys, it=[], it_label='it_data', exhausted_outcome='exhausted')<br />



In this example, the outcomes now include preempted, a default outcome of the iterator. The it argument is the list of objects that will be iterated over and the it_label is key that holds the current value of the of the item in the it list. The exhausted argument should be set to the preferred state machine outcome, in this example the iterator outcome is succeeded when the iterator is done looping through the it list. 








