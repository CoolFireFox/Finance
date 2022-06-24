#pragma once
#include "Items.h"
#include "Operation.h"

class Wallet : public Item
{
protected:
	long num;
	float sum;
	std::vector <Operation> history;
public:
	enum class ReportCommand
	{
		dayReport = 1, weekReport, monthReport
	};
	enum class RateCommand
	{
		weekRate = 1, monthRate
	};

	Wallet() = default;
	Wallet(long num, float sum, bool credit, float creditLimit = 0, float creditSum = 0)
		: Item(), num{ num }, sum{ sum }{}
	void enter() override;
	void edit() override;
	void write(std::ostream& output) override;
	void read(std::istream& input) override;
	void addOperation(const Operation& value);

	void report();
	void dayReport(Date date);
	void weekReport(Date date);
	void monthReport(Date date);
	int dayC(Date date);
	void dayRep(Date date, bool replenish = false);
	void rateExpense();
	void weekRateExpense(Date date);
	void monthRateExpense(Date date);
	void rateCategory();
	void weekRateCategory(Date date);
	void monthRateCategory(Date date);
	std::vector<Operation> dayOpVec(Date date, bool replenish = false);
	void rateDisplay(std::vector<Date>& date);
	friend class Wallets;

	friend struct compareWalletsByNumber;
	friend struct compareWalletsBySum;

	struct SumCompare
	{
		float value;
		SumCompare(float value) : value{ value } {};
		bool operator()(const std::pair<int, Item*>& two) const
		{
			return value == static_cast<Wallet*>(two.second)->sum;
		}
	};
};
