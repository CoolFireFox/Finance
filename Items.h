#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "item.h"
#include "menu.h"

class Items : public Menu
{
public:
    enum class Command
    {
        add = 1, edit, remove,
        displayAll, display,
        open, save, saveAs, clear
    };

protected:
    std::map <int, Item*> items;
    int key;
    std::string filename;

public:
    Items();
    Items(std::map<int, std::string> commands);
    virtual ~Items();
    void run();
    void execCommand(int command) override;

    virtual Item* createItem() = 0;
    //Item* makeItem(); возможный smart-pointer
    void add();
    void checkKey(int key) const;
    void display();
    void display(int key);
    void displayAll();

    void edit();
    void edit(int key);
    void remove();
    void remove(int key);
    
    void open();
    void open(std::string filename);
    void save();
    void save(std::string filename);
    void clear();
    friend class CardMenu;

    virtual void otherCommands(int command)
    {}

    Item* operator[](int key)
    {
        return items[key];
    }
};

