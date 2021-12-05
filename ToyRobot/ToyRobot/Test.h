#pragma once
/** I used a rudimentary system of asserts to execute my unit tests in an attempt to maintain simplicity and keep the focus on the logic of the code */

#include <iostream>
#include <assert.h>

void SplitCommandTest_SplitsCorrectly()
{
	std::vector<std::string> ExpectedResult = { "One", "Two", "Three" };
	std::vector<std::string> ReturnedResult = Robot::SplitCommand("One Two Three");

	assert(ReturnedResult.size() == 3);
	assert(ReturnedResult[0] == ExpectedResult[0]);
	assert(ReturnedResult[1] == ExpectedResult[1]);
	assert(ReturnedResult[2] == ExpectedResult[2]);
}

void CommaSplitTest_SplitsCorrectly()
{
	std::vector<std::string> ExpectedResult = { "One", "Two", "Three" };
	std::vector<std::string> ReturnedResult = Robot::CommaSplit("One,Two,Three");

	assert(ReturnedResult.size() == 3);
	assert(ReturnedResult[0] == ExpectedResult[0]);
	assert(ReturnedResult[1] == ExpectedResult[1]);
	assert(ReturnedResult[2] == ExpectedResult[2]);
}

void RobotActionTest_HandleNotPlaced()
{
	Robot TestRobot;
	assert(!TestRobot.ExecuteCommand("Left"));
}

void RobotActionTest_HandleRotation()
{
	Robot TestRobot;
	int facingX = TestRobot.GetFacingX();
	int facingY = TestRobot.GetFacingY();

	TestRobot.ExecuteCommand("Place 0,0,North");
	TestRobot.ExecuteCommand("Left");

	assert(TestRobot.GetFacingX() == -1);
	assert(TestRobot.GetFacingY() == 0);
}

void RobotActionTest_HandleBounds()
{
	Robot TestRobot;
	TestRobot.ExecuteCommand("Place 4,4,North");
	TestRobot.ExecuteCommand("Move");
	assert(TestRobot.GetPosX() == 4);
	assert(TestRobot.GetPosY() == 4);

	TestRobot.ExecuteCommand("Place 0,0,South");
	TestRobot.ExecuteCommand("Move");
	assert(TestRobot.GetPosX() == 0);
	assert(TestRobot.GetPosY() == 0);
}

// Should fail move if attempting to move out of bounds
void RobotActionTest_HandleFailMove()
{
	Robot TestRobot;
	TestRobot.ExecuteCommand("Place 4,4,North");
	assert(!TestRobot.ExecuteCommand("Move"));
}

// Should fail report if not placed on the table yet
void RobotActionTest_HandleFailReport()
{
	Robot TestRobot;
	assert(!TestRobot.ExecuteCommand("Report"));
}

void InRangeTest()
{
	assert(Robot::InRange(2, 4, 3));
	assert(!Robot::InRange(2, 4, 5));
	assert(Robot::InRange(2, 4, 4));
	assert(Robot::InRange(2, 4, 2));
}

void ToUpperTest_TransformsCorrectly()
{
	std::string testString = "move";
	Robot::ToUpper(testString);
	assert(testString == "MOVE");
}

/** All tests are run from this function, which is called at the top of main in Source.cpp */
void RunTests()
{
	SplitCommandTest_SplitsCorrectly();
	CommaSplitTest_SplitsCorrectly();
	ToUpperTest_TransformsCorrectly();
	InRangeTest();
	RobotActionTest_HandleNotPlaced();
	RobotActionTest_HandleRotation();
	RobotActionTest_HandleBounds();
	RobotActionTest_HandleFailReport();
	RobotActionTest_HandleFailMove();
}

