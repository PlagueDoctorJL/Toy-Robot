#pragma once
// Library includes
#include <string>
#include <vector>

/** A simple object which takes text input and simulates movement upon a table of fixed width and length */
class Robot
{
public:
	Robot();
	~Robot();

	/**
	* Parse raw text input and execute appropriate actions in response.
	* @param _commmand: One line text input from the user specifying an action (e.g Place, Move, Left, Right, Report..)
	* @return: return false if failed to execute command
	*/
	bool ExecuteCommand(const std::string _command);	

	/**
	* Split a command into individual components
	* @param _command: the string to be split into individual components
	* @return: Return a vector containing each individual component of the command
	*/
	static std::vector<std::string> SplitCommand(const std::string& _command);

	/**
	* Transform each individual character of an std::string to uppercase
	* @param _string: the string to be transformed
	*/
	static void ToUpper(std::string& _string);

	/**
	* Split a string by comma
	* @param _string: the string to be split into individual components via comma separation
	* @return: Return a vector containing each individual component of the command
	*/
	static std::vector<std::string> CommaSplit(const std::string& _string);

	/** Returns true if x is within range (inclusive) */
	static bool InRange(const int _low, const int _high, const int _x);

	/** Private variable getters */
	unsigned int GetPosX() const { return posX; }
	unsigned int GetPosY() const { return posY; }
	int GetFacingX() const { return facingX; }
	int GetFacingY() const { return facingY; }
	bool GetIsPlaced() const { return isPlaced; }

private:
	// Robot location XY coordinates 
	unsigned int posX;
	unsigned int posY;

	// Robot facing direction
	int facingX;
	int facingY;

	// Dimensions of the table
	const int tableWidth = 5;
	const int tableLength = 5;

	// If the Robot has been placed on the table yet
	bool isPlaced;

private:
	/** 
	* Set the robot's XY location and facing XY.
	* @param _x: new x location
	* @param _y: new y location
	* @param _cardinalDirection: new facing direction specified as either.. N, S, W, or E
	* @return: return true if the command was successfully executed
	*/
	bool Place(const unsigned int _x, const unsigned int _y, const char _cardinalDirection);

	/** 
	* Try to move the robot one unit in the facing direction. 
	* @return: return true if the command was successfully executed
	*/
	bool Move();

	/** 
	* Output the robot's current location and cardinal direction
	* @return: return true if the command was successfully executed
	*/
	bool Report();

	/** 
	* Rotate the robot's facing direction
	* @param _angle: the angle to rotate the facing direction by
	*/
	void Rotate(const int _angle);	
};

