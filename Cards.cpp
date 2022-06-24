#include "Cards.h"
#include <algorithm>
using namespace std;

std::map<int, std::string> CardsCommands =
{ 
	{(int)Cards::Command::cardMenu, "���� �����..."},
	{(int)Cards::Command::findNumber, "����� �� ������..."},
	{(int)Cards::Command::sortByNumber, "����������� �� ������"},
	{(int)Cards::Command::sortBySum, "����������� �� �����"}
};
//
//std::map<int, std::string> RateCommand =
//{
//	{(int)Card::RateCommand::weekRate, "������"},
//	{(int)Card::RateCommand::monthRate, "�����"}
//};
//
//std::map<int, std::string> ReportCommand =
//{
//	{(int)Card::ReportCommand::dayReport, "����"},
//	{(int)Card::ReportCommand::weekReport, "������"},
//	{(int)Card::ReportCommand::monthReport, "�����"}
//};

Cards::Cards() : Items()
{
	addCommands(CardsCommands);
}

Item* Cards::createItem()
{
	return new Card();
}

void Cards::otherCommands(int command)
{
	switch (Command(command))
	{
	case Cards::Command::cardMenu:
		displayAll();
		subMenu();
		break;
	case Cards::Command::findNumber:
		findNumber();
		break;
	case Cards::Command::sortByNumber:
		sortByNumber();
		break;
	case Cards::Command::sortBySum:
		sortBySum();
		break;
	default:
		break;
	}
}

void Cards::findNumber()
{
	long value;
	cout << endl;
	getValue("������� �����: ", value);
	int key = findNumber(value);
	cout << (key == string::npos ? "\n�� �������." :
		to_string(key)) << endl;
}

int Cards::findNumber(long value, int key)
{
	map<int, Item*>::iterator it = items.begin();
	if (key != string::npos)
	{
		it = items.find(key);
		it++;
	}
	it = find_if(it, items.end(), Card::SumCompare(value));
	return it == items.end() ? string::npos : it->first;
}

Card* Cards::getCard(int key)
{
	Card* pCard;
	for (auto item : items) {
		if (item.first == key)
		{
			pCard = static_cast<Card*>(item.second);
			return pCard;
		}
	}
	return nullptr;
}

Card* Cards::getCardByNumber(long n)
{
	Card* pCard;
	for (auto item : items) {
		if (static_cast<Card*>(item.second)->num == n)
		{
			pCard = static_cast<Card*>(item.second);
			return pCard;
		}
	}
	return nullptr;
}

void Cards::sortByNumber()
{
	cout << endl;
	vector<Card*> pCards;
	for (auto item : items)
	{
		Card* pCard = static_cast<Card*>(item.second);
		pCards.push_back(pCard);
	}

	sort(pCards.begin(), pCards.end(), compareCardsByNumber());
	for (auto pCard : pCards)
	{
		cout << /*"[" << showKey(pCard->title) << "] " <<*/ pCard->num << " : " << pCard->sum << endl;
	}
	cout << endl;
}


void Cards::sortBySum()
{
	cout << endl;
	vector<Card*> pCards;
	for (auto item : items)
	{
		Card* pCard = static_cast<Card*>(item.second);
		pCards.push_back(pCard);
	}

	sort(pCards.begin(), pCards.end(),
		compareCardsBySum());
	for (auto pCard : pCards)
	{
		cout << pCard->num << " : " << pCard->sum << endl;
	}
	cout << endl;
}

void Cards::subMenu()
{
	int keyValue;
	Card* currentCard;
	currentCard = getCard(keyValue);
	CardMenu(currentCard);
}
