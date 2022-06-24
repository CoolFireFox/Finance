#pragma once
#include "Items.h"
#include "Wallet.h"
#include "WalletMenu.h"
class Wallets : public Items
{
public:
	enum class Command
	{
		walletMenu = 10, findNumber = 11, sortByNumber, sortBySum
	};

	Wallets();
	Item* createItem() override;
	void otherCommands(int command) override;
	void setCurrentWalletKey(int key);
	void setCurrentWalletKey();
	int getCurrentWalletKey();
	void findNumber();
	int findNumber(long value,
		int key = std::string::npos);

	Wallet* getWallet(int key);
	Wallet* getWalletByNumber(long n);
	void sortByNumber();
	void sortBySum();
	void subMenu();
	friend class WalletMenu;
};

struct compareWalletsByNumber
{
	bool operator()
		(const Wallet* prev, const Wallet* next)
	{
		if (prev->num != next->num)
		{
			return prev->num < next->num;
		}
	}
};

struct compareWalletsBySum
{
	bool operator()
		(const Wallet* prev, const Wallet* next)
	{
		if (prev->sum != next->sum)
		{
			return prev->sum < next->sum;
		}
	}
};