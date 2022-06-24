#include "Operation.h"
#include "common.h"
#include <sstream>
using namespace std;

void Operation::enter()
{
	cout << "\nДобавить операцию" << endl;
	cout << "Тип операции:\n[1] Затрата;\n[2] Пополнение;\n";
	int type = 0;
	while (type < 1 || type > 2)
	{
		getValue("[->] ", type);
	}
	if (type == 1) { expenditure == true; }
	else
		if (type == 2) { expenditure == false; }
	cout << endl;
	cout << "Категория: ";
	getline(cin, category);
	cout << "Дата (д,м,г): ";
	cin >> date;
	getValue("Сумма: ", sum);
	
	/*int year = -1, month = -1, day = -1;
	while (!Date::isCorrectDate(year, month, day)) 
	{
		cin >> year;
		cin >> day;
		cin.ignore(1);
		cin >> month;
		cin.ignore(1);
		cin >> year;
	}
	setDate(year, month, day);*/
}

void Operation::edit()
{
	cout << "\nИзменить" << endl;
	editLine("Категория: ", category);
	editValue("Сумма: ", sum);
}

void Operation::write(std::ostream& output)
{
	output << category << endl << 
		date << endl << sum << endl;
}

void Operation::read(std::istream& input)
{
	getline(input, category);
	input >> date;
	input >> sum;
}

void Operation::setCategory(std::string value)
{
	this->category = value;
}

void Operation::setSum(float sum)
{
	this->sum = sum;
}

void Operation::setDate(int year, int month, int day)
{
	date.Date::setDate(year, month, day);
}

std::string Operation::getCategory()
{
	return category;
}

float Operation::getSum()
{
	return sum;
}

Date Operation::getDate()
{
	return date;
}

void Operation::addReplenish() // добавить пополнение
{
	cout << "\nДобавить пополнение" << endl;
	expenditure == false;
	cout << endl;
	cout << "Категория: ";
	getline(cin, category);
	cout << "Дата (д,м,г): ";
	cin >> date;
	getValue("Сумма: ", sum);
}

void Operation::addExpnditure() // добавить затрату
{
	cout << "\nДобавить затрату" << endl; 
	expenditure == true;
	cout << endl;
	cout << "Категория: ";
	getline(cin, category);
	cout << "Дата (д,м,г): ";
	cin >> date;
	getValue("Сумма: ", sum);
}
