// Local includes
#include "Robot.h"

#define _USE_MATH_DEFINES

// Library includes
#include <sstream>
#include <math.h>
#include <iostream>

Robot::Robot()
{
	// Initialize member variables
	posX = 0;
	posY = 0;
	facingX = 1;
	facingY = 0;
	isPlaced = false;
}

Robot::~Robot()
{
	// Deallocate any dynamically allocated memory
	// ..
}

bool Robot::ExecuteCommand(const std::string _command)
{	
	std::vector<std::string> commandComponents = Robot::SplitCommand(_command);	
	const int vectorSize = commandComponents.size();	

	// Define a flag to be set false if we fail to execute a command
	bool executedCommand = true;

	// Parse the type of command
	std::string commandType = commandComponents[0];

	// modify the first component by reference so that it is all uppercase (for normalization purposes)
	Robot::ToUpper(commandType);

	// Call associated functionality depending on command type
	if (commandType == "PLACE" && vectorSize == 2)
	{		
		// Split out the arguments for place and convert them to the correct data type
		std::vector<std::string> placeArguments = CommaSplit(commandComponents[1]);
		int placeX = std::stoi(placeArguments[0].c_str());
		int placeY = std::stoi(placeArguments[1].c_str());
		const char cardinalDirection = placeArguments[2][0];

		// Only pass the first character of the string as that is enough to signify the cardinal direction
		executedCommand = Place(placeX, placeY, cardinalDirection);
	}
	else if (commandType == "REPORT")
	{
		executedCommand = Report();
	}
	else if (commandType == "LEFT" && isPlaced)
	{
		Rotate(-90);
	}
	else if (commandType == "RIGHT" && isPlaced)
	{
		Rotate(90);
	}	
	else if (commandType == "MOVE" && isPlaced)
	{
		executedCommand = Move();
	}
	else
	{
		executedCommand = false;
	}

	// Should return false if no command was executed successfully
	return executedCommand;
}

std::vector<std::string> Robot::SplitCommand(const std::string& _command)
{
	std::stringstream ss(_command);
	std::vector<std::string> commandComponents;
	std::string component;

	while (ss >> component)
	{
		commandComponents.push_back(component);
	}

	return commandComponents;
}

void Robot::ToUpper(std::string& _string)
{
	for (auto& c : _string) c = toupper(c);
}

std::vector<std::string> Robot::CommaSplit(const std::string& _string)
{
	std::stringstream ss(_string);
	std::vector<std::string> stringComponents;
	std::string substr;

	while (ss.good())
	{
		std::getline(ss, substr, ',');
		stringComponents.push_back(substr);
	}

	return stringComponents;
}

bool Robot::InRange(const int _low, const int _high, const int _x)
{
	return (_low <= _x && _x <= _high);
}

bool Robot::Place(const unsigned int _x, const unsigned int _y, const char _cardinalDirection)
{
	// Don't move if the placement is out of 
	if (!InRange(0, 4, _x) && !InRange(0, 4, _y))
	{
		return false;
	}

	// Set new position
	posX = _x;
	posY = _y;

	// Set facing XY according to cardinal direction
	if (_cardinalDirection == 'N')
	{
		facingX = 0;
		facingY = 1;
	} 
	else if (_cardinalDirection == 'S')
	{
		facingX = 0;
		facingY = -1;
	}
	else if (_cardinalDirection == 'E')
	{
		facingX = 1;
		facingY = 0;
	}
	else if (_cardinalDirection == 'W')
	{
		facingX = -1;
		facingY = 0;
	}
	else
	{
		std::cout << "> Please enter a valid cardinal direction" << std::endl;
		return false;
	}

	isPlaced = true;
	return true;
}

bool Robot::Move()
{
	// Calculate new location
	int newPosX = posX + facingX;
	int newPosY = posY + facingY;

	if (InRange(0, 4, newPosX) && InRange(0, 4, newPosY))
	{
		posX = newPosX;
		posY = newPosY;
		return true;
	}
	return false;	
}

bool Robot::Report()
{
	// Abort the execution of the Report command if the robot is not placed yet
	if (!isPlaced)
	{
		return false;
	}

	// Convert xy facing coordinates back to cardinal direction for console output
	// stored as a const char* in this situation for compatibility with printf
	const char* cardinalDirection = "";
	if (facingX == 1)
	{
		cardinalDirection = "East";
	}
	else if (facingX == -1)
	{
		cardinalDirection = "West";
	}
	else if (facingY == 1)
	{
		cardinalDirection = "North";
	}
	else if (facingY == -1)
	{
		cardinalDirection = "South";
	}

	printf("> Output: %i, %i, %s \n", posX, posY, cardinalDirection);

	return true;
}

void Robot::Rotate(const int _angle)
{
	// The rotation matrix produces a counter clockwise rotation 
	// We negate the angle to produce a clockwise rotation of the specified amount
	double radians = _angle * M_PI / 180;
	radians *= -1; 

	// Apply a 2D rotation matrix
	int newFacingX = static_cast<int>(facingX * cos(radians) - facingY * sin(radians));
	int newFacingY = static_cast<int>(facingX * sin(radians) + facingY * cos(radians));

	facingX = newFacingX;
	facingY = newFacingY;
}