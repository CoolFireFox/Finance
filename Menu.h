#pragma once
#include <iostream>
#include <map>
#include "common.h"

const int cmdExit{ 0 };
const std::string cmdExitText{ "Выход" };

class Menu
{
	std::map<int, std::string> commands;
public:
	Menu() = default;
	Menu(std::map<int, std::string> commands) : commands{commands}
	{}

	void addCommands(std::map<int, std::string> addCommands);
	void addCommand(int command, std::string commandText);
	void removeCommand(int command);

	void run();
	virtual void execCommand(int command) = 0;
private:
	int getCommand()  const;
	bool isCommand(const int command) const;
};

