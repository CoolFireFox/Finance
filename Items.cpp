#include <fstream>
#include <iomanip>
#include "Items.h"
using namespace std;

std::map<int, std::string> itemCommands =
{
    {(int)Items::Command::add, "��������..."},
    {(int)Items::Command::edit, "��������..."},
    {(int)Items::Command::remove, "�������..."},
    {(int)Items::Command::displayAll, "�������� ��"},
    {(int)Items::Command::display, "�������� ���������..."},
    {(int)Items::Command::open, "�������..."},
    {(int)Items::Command::save, "���������"},
    {(int)Items::Command::saveAs, "��������� ���..."},
    {(int)Items::Command::clear, "��������..."}
};

Items::Items() : Menu(itemCommands)
{}

Items::Items(map<int, string> commands) : Menu(commands)
{}

Items::~Items()
{
    clear();
}

void Items::run()
{
    Menu::run();
}

void Items::execCommand(int command)
{
    switch ((Items::Command)command)
    {
    case Items::Command::add:
        add();
        break;
    case Items::Command::edit:
        edit();
        break;
    case Items::Command::remove:
        remove();
        break;
    case Items::Command::displayAll:
        displayAll();
        break;
    case Items::Command::display:
        display();
        break;
    case Items::Command::open:
        open();
        break;
    case Items::Command::save:
        save(filename);
        break;
    case Items::Command::saveAs:
        save();
        break;
    case Items::Command::clear:
        clear();
        break;
    default:
        otherCommands(command);
        break;
    }
}

void Items::add()
{
    Item* item = createItem();
    item->enter();
    items[key++] = item;
}

void Items::checkKey(int key) const
{
    if (items.count(key) == 0)
    {
        throw "\n������������ ����.";
    }
}

void Items::display()
{
    int key;
    getValue("\n������� ����: ", key);
    display(key);
}

void Items::display(int key)
{
    checkKey(key);
    cout << setw(4) << key << " : ";
    items[key]->write(cout);
}

void Items::displayAll()
{
    for (auto item : items)
    {
        display(item.first);
    }
}

void Items::edit()
{
    int key;
    getValue("\n������� ����: ", key);
    edit(key);
}

void Items::edit(int key)
{
    checkKey(key);
    items[key]->edit();
}

void Items::remove()
{
    int key;
    getValue("\n������� ����: ", key);
    remove(key);
}

void Items::remove(int key)
{
    checkKey(key);
    delete items[key];
    items.erase(key);
}

void Items::save()
{
    string filename;
    getValue("\n������� ��� �����: ", filename);
    save(filename);
    this->filename = filename;
}

void Items::save(string filename)
{
    ofstream output(filename);
    if (!output.is_open())
    {
        throw "\n�� ������� ������� ����.";
    }
    output << key << endl;
    output << items.size() << endl;
    for (auto item : items)
    {
        output << item.first << " ";
        item.second->write(output);
    }
    output.close();
}

void Items::open()
{
    string filename;
    getValue("\n������� ��� �����: ", filename);
    open(filename);
    displayAll();
    this->filename = filename;
}

void Items::open(string filename)
{
    ifstream input(filename);
    if (!input.is_open())
    {
        throw "\n�� ������� ������� ����.";
    }
    input >> key;
    string endLine;
    getline(input, endLine);
    int size;
    input >> size;
    getline(input, endLine);
    for (int i = 0; i < size; i++)
    {
        Item* item = createItem();
        int key;
        input >> key;
        input.ignore(1);
        item->read(input);
        items[key] = item;
    }
    input.close();
}

void Items::clear()
{
    for (auto item : items)
    {
        delete item.second;
    }
    filename.clear();
    items.clear();
}

