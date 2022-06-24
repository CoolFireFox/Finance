#include <iomanip>
#include "menu.h"
using namespace std;

void Menu::addCommands(std::map<int, std::string> addCommands)
{
    commands.insert(addCommands.begin(), addCommands.end());
}

void Menu::addCommand(int command, std::string commandText)
{
    commands[command] = commandText;
}

void Menu::removeCommand(int command)
{
    commands.erase(command);
}

void Menu::run()
{
    int command = getCommand();
    while (command != cmdExit)
    {
        try
        {
            execCommand(command);
        }
        catch (const char* s)
        {
            cout << s << endl;
        }
        catch (...)
        {
            cout << "ќшибка!" << endl;
        }
        command = getCommand();
    }
}

int Menu::getCommand() const
{
    for (auto command : commands)
    {
        cout << setw(3) << command.first <<
            " " << command.second << endl;
    }
    cout << setw(3) << cmdExit <<
        " " << cmdExitText << endl;
    int command;
    getValue("->: ", command);
    while (!isCommand(command))
    {
        cout << "\nќшибка... ¬ведите по новой." << endl;
        getValue("->: ", command);
    }
    return command;
}

bool Menu::isCommand(const int command) const
{
    return commands.count(command) == 1 || command == cmdExit;
}

