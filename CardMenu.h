#pragma once
#include "Items.h"
#include "Operation.h"
#include "Menu.h"
#include "Card.h"
#include "Cards.h"
using namespace std;

class CardMenu : public Menu
{
public:
	CardMenu() = default;
	CardMenu(std::map<int, std::string> commands, Card* card) : Menu(commands), card{ card } {}
	enum class Command
	{
		choseCard = 1, expense, replenish, report, rateExpense, rateCategory
	};
private:
	Card* card;
	Cards* cards;
	void execCommand(int command) override;
};

std::map<int, std::string> cardCommands =
{
	{(int)CardMenu::Command::choseCard, "������� �����..."},
	{(int)CardMenu::Command::expense, "�������� �������..."},
	{(int)CardMenu::Command::replenish, "�������� ����������..."},
	{(int)CardMenu::Command::report, "����� �� ��������..."},
	{(int)CardMenu::Command::rateExpense, "������������ �������� �� ��������..."},
	{(int)CardMenu::Command::rateCategory, "������������ �������� �� ����������..."},
};

void CardMenu::execCommand(int command)
{
	Operation op;
	int key;
	long number;
	//getValue("", key);
	switch ((CardMenu::Command)command)
	{
	case CardMenu::Command::choseCard:
		//this->card = getCard(key);
		getValue("����� ����� �� ������\n", number);
		//this->card = cards->getCard(key);//getCardByNumber(number);
		this->card = cards->getCardByNumber(number);

		break;
	case CardMenu::Command::expense:
		op.addExpnditure();
		card->addOperation(op);
		break;
	case CardMenu::Command::replenish:
		op.addReplenish();
		card->addOperation(op);
		break;
	case CardMenu::Command::report:
		card->Card::report();
		break;
	case CardMenu::Command::rateExpense:
		card->Card::rateExpense();
		break;
	case CardMenu::Command::rateCategory:
		card->Card::rateCategory();
		break;

	default:
		break;
	}
}
