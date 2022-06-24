#pragma once
#include "Items.h"
#include "Operation.h"
#include "Menu.h"
#include "Wallet.h"
#include "Wallets.h"
using namespace std;

class WalletMenu : public Menu
{
public:
	WalletMenu() = default;
	WalletMenu(std::map<int, std::string> commands, Wallet* Wallet) : Menu(commands)
	{}
	enum class Command
	{
		choseWallet = 1, expense, replenish, report, rateExpense, rateCategory
	};
private:
	Wallet* wallet;
	Wallets* wallets;
	void execCommand(int command) override;
};

std::map<int, std::string> WalletCommands =
{
	{(int)WalletMenu::Command::choseWallet, "������� ����..."},
	{(int)WalletMenu::Command::expense, "�������� �������..."},
	{(int)WalletMenu::Command::replenish, "�������� ����������..."},
	{(int)WalletMenu::Command::report, "����� �� ��������..."},
	{(int)WalletMenu::Command::rateExpense, "������������ �������� �� ��������..."},
	{(int)WalletMenu::Command::rateCategory, "������������ �������� �� ����������..."},
};

void WalletMenu::execCommand(int command)
{
	Operation op;
	int key;
	long number;
	//getValue("", key);
	switch ((WalletMenu::Command)command)
	{
	case WalletMenu::Command::choseWallet:
		getValue("����� ����� �� ������\n", number);
		//this->wallet = wallets->getWallet(key);
		this->wallet = wallets->getWalletByNumber(number);

		break;
	case WalletMenu::Command::expense:
		op.addExpnditure();
		wallet->addOperation(op);
		break;
	case WalletMenu::Command::replenish:
		op.addReplenish();
		wallet->addOperation(op);
		break;
	case WalletMenu::Command::report:
		wallet->Wallet::report();
		break;
	case WalletMenu::Command::rateExpense:
		wallet->Wallet::rateExpense();
		break;
	case WalletMenu::Command::rateCategory:
		wallet->Wallet::rateCategory();
		break;

	default:
		break;
	}
}
