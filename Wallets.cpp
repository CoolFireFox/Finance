#include "Wallets.h"
#include <algorithm>
using namespace std;

std::map<int, std::string> WalletsCommands =
{
	{(int)Wallets::Command::walletMenu, "���� �����..."},
	{(int)Wallets::Command::findNumber, "����� �� ������..."},
	{(int)Wallets::Command::sortByNumber, "����������� �� ������"},
	{(int)Wallets::Command::sortBySum, "����������� �� �����"}
};

std::map<int, std::string> RateCommand =
{
	{(int)Wallet::RateCommand::weekRate, "������"},
	{(int)Wallet::RateCommand::monthRate, "�����"}
};

std::map<int, std::string> ReportCommand =
{
	{(int)Wallet::ReportCommand::dayReport, "����"},
	{(int)Wallet::ReportCommand::weekReport, "������"},
	{(int)Wallet::ReportCommand::monthReport, "�����"}
};

Wallets::Wallets() : Items()
{
	addCommands(WalletsCommands);
}

Item* Wallets::createItem()
{
	return new Wallet();
}

void Wallets::otherCommands(int command)
{
	switch (Command(command))
	{
	case Wallets::Command::walletMenu:
		displayAll();
		subMenu();
		break;
	case Wallets::Command::findNumber:
		findNumber();
		break;
	case Wallets::Command::sortByNumber:
		sortByNumber();
		break;
	case Wallets::Command::sortBySum:
		sortBySum();
		break;
	default:
		break;
	}
}

void Wallets::findNumber()
{
	long value;
	cout << endl;
	getValue("������� �����: ", value);
	int key = findNumber(value);
	cout << (key == string::npos ? "\n�� �������." :
		to_string(key)) << endl;
}

int Wallets::findNumber(long value, int key)
{
	map<int, Item*>::iterator it = items.begin();
	if (key != string::npos)
	{
		it = items.find(key);
		it++;
	}
	it = find_if(it, items.end(), Wallet::SumCompare(value));
	return it == items.end() ? string::npos : it->first;
}

Wallet* Wallets::getWallet(int key)
{
	Wallet* pWallet;
	for (auto item : items) {
		if (item.first == key)
		{
			pWallet = static_cast<Wallet*>(item.second);
			return pWallet;
		}
	}
	return nullptr;
}

Wallet* Wallets::getWalletByNumber(long n)
{
	Wallet* pWallet;
	for (auto item : items) {
		if (static_cast<Wallet*>(item.second)->num == n)
		{
			pWallet = static_cast<Wallet*>(item.second);
			return pWallet;
		}
	}
	return nullptr;
}

void Wallets::sortByNumber()
{
	cout << endl;
	vector<Wallet*> pWallets;
	for (auto item : items)
	{
		Wallet* pWallet = static_cast<Wallet*>(item.second);
		pWallets.push_back(pWallet);
	}

	sort(pWallets.begin(), pWallets.end(), compareWalletsByNumber());
	for (auto pWallet : pWallets)
	{
		cout << /*"[" << showKey(pWallet->title) << "] " <<*/ pWallet->num << " : " << pWallet->sum << endl;
	}
	cout << endl;
}


void Wallets::sortBySum()
{
	cout << endl;
	vector<Wallet*> pWallets;
	for (auto item : items)
	{
		Wallet* pWallet = static_cast<Wallet*>(item.second);
		pWallets.push_back(pWallet);
	}

	sort(pWallets.begin(), pWallets.end(),
		compareWalletsBySum());
	for (auto pWallet : pWallets)
	{
		cout << pWallet->num << " : " << pWallet->sum << endl;
	}
	cout << endl;
}

void Wallets::subMenu()
{
	int keyValue;
	Wallet* currentWallet;
	currentWallet = getWallet(keyValue);
	WalletMenu(currentWallet);
}