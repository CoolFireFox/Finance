#pragma once
#include <iostream>
#include "Date.h"
#include "Items.h"
class Operation : Item
{
private:
	std::string category;
	Date date;
	float sum;
	bool expenditure;
public:
	void enter() override;
	void edit() override;
	void write(std::ostream& output) override;
	void read(std::istream& input) override;
	void setCategory(std::string value);
	void setSum(float sum);
	void setDate(int year, int month, int day);
	std::string getCategory();
	float getSum();
	Date getDate();

	void addExpnditure();
	void addReplenish();
	friend class Card;
	friend class Wallet;

	struct CompareOperationsBySum
	{
		bool operator()
			(const Operation& prev, const Operation& next)
		{
			if (prev.sum != next.sum)
			{
				return prev.sum > next.sum;
			}
		}
	};
};

