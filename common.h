#pragma once
#include <iostream>
#include <string>
using namespace std;
template <class T>
void getValue(const std::string& prompt, T& value)
{
    std::cout << prompt;
    std::cin >> value;

    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Ошибка... попробуйте ещё раз." << std::endl;

        std::cout << prompt;
        std::cin >> value;
    }

    std::string endLine;
    getline(std::cin, endLine);
}

template <class T>
void editValue(const std::string& prompt, T& value)
{
    std::cout << prompt << " (" << value << "): ";
    if (std::cin.peek() != '\n')
    {
        std::cin >> value;
    }
    std::string endLine;
    getline(std::cin, endLine);
}

void editLine(const std::string& prompt, std::string& value)
{
    std::cout << prompt << " (" << value << "): ";
    if (std::cin.peek() != '\n')
    {
        getline(cin, value);
    }
    else
    {
        std::string endLine;
        std::getline(cin, endLine);
    }
}
