#pragma once
#include "Items.h"
#include "Card.h"
#include "CardMenu.h"

class Cards : public Items
{
private:
	
public:
	enum class Command
	{
		cardMenu = 10, findNumber, sortByNumber, sortBySum
	};

	Cards();
	Item* createItem() override;
	void otherCommands(int command) override;
	void findNumber();
	int findNumber(long value,
		int key = std::string::npos);

	Card* getCard(int key);
	Card* getCardByNumber(long n);
	void sortByNumber();
	void sortBySum();
	void subMenu();
	friend class CardMenu;
};

struct compareCardsByNumber
{
	bool operator()
		(const Card* prev, const Card* next)
	{
		if (prev->num != next->num)
		{
			return prev->num < next->num;
		}
	}
};

struct compareCardsBySum
{
	bool operator()
		(const Card* prev, const Card* next)
	{
		if (prev->sum != next->sum)
		{
			return prev->sum < next->sum;
		}
	}
};