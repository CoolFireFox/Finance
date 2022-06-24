#pragma once
#include <iostream>

class Item
{
public:
    virtual void enter() = 0;
    virtual void edit() = 0;
    virtual void write(std::ostream& output) = 0;
    virtual void read(std::istream& input) = 0;
};

