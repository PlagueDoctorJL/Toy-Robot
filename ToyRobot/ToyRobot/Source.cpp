// Library includes
#include <iostream>
#include <string>
#include <vector>

// Local includes
#include "Robot.h"
#include "Test.h"

int main()
{	
	/** Uncomment the line below to enable testing on program execution*/
	//RunTests();
	
	Robot ToyRobot;

	// Define a message to be output to the user when an exception is thrown
	std::string readmeReminder = "> Refer to the README file for example application usage.";

	// Program loop
	while (1)
	{
		std::vector<std::string> lines;
		std::string line;		

		// Loop through user input, sending individual commands to be executed in order
		while (std::getline(std::cin >> std::ws, line))
		{
			try {
				// Ignore empty input
				if (!line.empty())
				{
					// Send user input to robot for parsing and execution
					ToyRobot.ExecuteCommand(line);
				}				
			}
			catch (const std::exception& e)
			{
				std::cout << "> Failed to execute command due to " << e.what() << std::endl;
				std::cout << readmeReminder << std::endl;
			}	
			catch (...)
			{
				std::cout << "> Failed to execute command." << std::endl;
				std::cout << readmeReminder << std::endl;
			}
		}		
	}

	return 0;
}