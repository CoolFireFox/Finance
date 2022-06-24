#include "Operation.h"
#include "common.h"
#include <sstream>
using namespace std;

void Operation::enter()
{
	cout << "\n�������� ��������" << endl;
	cout << "��� ��������:\n[1] �������;\n[2] ����������;\n";
	int type = 0;
	while (type < 1 || type > 2)
	{
		getValue("[->] ", type);
	}
	if (type == 1) { expenditure == true; }
	else
		if (type == 2) { expenditure == false; }
	cout << endl;
	cout << "���������: ";
	getline(cin, category);
	cout << "���� (�,�,�): ";
	cin >> date;
	getValue("�����: ", sum);
	
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
	cout << "\n��������" << endl;
	editLine("���������: ", category);
	editValue("�����: ", sum);
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

void Operation::addReplenish() // �������� ����������
{
	cout << "\n�������� ����������" << endl;
	expenditure == false;
	cout << endl;
	cout << "���������: ";
	getline(cin, category);
	cout << "���� (�,�,�): ";
	cin >> date;
	getValue("�����: ", sum);
}

void Operation::addExpnditure() // �������� �������
{
	cout << "\n�������� �������" << endl; 
	expenditure == true;
	cout << endl;
	cout << "���������: ";
	getline(cin, category);
	cout << "���� (�,�,�): ";
	cin >> date;
	getValue("�����: ", sum);
}
