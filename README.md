# Toy-Robot-Challenge
This application is a simulation of a toy robot moving on a square table top.

## How to setup and run the application
To run the application run ToyRobot.exe, located under */Toy-Robot-Challenge/ToyRobot/Release/*

### Example application usage:
Enter the following commands into the console to view an example usage of the application:
```
Place 0,0,North
Move
Right
Move
Right
Report
```
### Example test application usage:
The following sets of commands can be entered to view the applications ability to handle incorrect usage, and ability to stay within the bounds of the table.
(Commands can be entered individually or by copy pasting a set of commands, each on a new line like below in the examples)

#### Example test of incorrect usage:
This test displays the functionality of the robot to ignore commands that require the robot to be placed on the table, if the robot is not yet placed on the table, as well as displaying the applications ability to deal with mistakes in input.
```
Report
Move
Left
Report
Place p,0,North
Place 0,0,SoUTh
Report
Place 0,0,Morth
   .sd#5%4$^&
Place0,0,North
```

#### Example test of table bounds:
This test displays the robot's ability to stay within the bounds of the table.
```
Place 4,4,North
Move
Report
```

## How to run tests
All testing is located under Test.h (*/Toy-Robot-Challenge/ToyRobot/ToyRobot/Test.h*)

Tests can be enabled by uncommenting line 13 of Source.cpp, the RunTests() function.
Build/run the solution to see if any tests fail. An assertion will be raised upon failure. ***MAKE SURE TO RUN IN DEBUG MODE - Release mode will ignore asserts.***

![this is where the RunTests function is](https://i.imgur.com/UgQo69z.png)