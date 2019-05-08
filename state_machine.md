# State Machine(smach)
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
