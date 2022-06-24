#include "Cards.h"
#include <algorithm>
using namespace std;

std::map<int, std::string> CardsCommands =
{ 
	{(int)Cards::Command::cardMenu, "Меню карты..."},
	{(int)Cards::Command::findNumber, "Поиск по номеру..."},
	{(int)Cards::Command::sortByNumber, "Сортировать по номеру"},
	{(int)Cards::Command::sortBySum, "Сортировать по сумме"}
};
//
//std::map<int, std::string> RateCommand =
//{
//	{(int)Card::RateCommand::weekRate, "неделя"},
//	{(int)Card::RateCommand::monthRate, "месяц"}
//};
//
//std::map<int, std::string> ReportCommand =
//{
//	{(int)Card::ReportCommand::dayReport, "день"},
//	{(int)Card::ReportCommand::weekReport, "неделя"},
//	{(int)Card::ReportCommand::monthReport, "месяц"}
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
	getValue("Введите номер: ", value);
	int key = findNumber(value);
	cout << (key == string::npos ? "\nНе найдено." :
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
