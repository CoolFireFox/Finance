#pragma once
#include "Items.h"
#include "Operation.h"
class Card : public Item
{
protected:
	long num;
	float sum; 
	bool credit;
	float creditLimit;
	float creditSum;
	std::vector <Operation> history;
	std::vector <Operation> creditHistory;
	static const float startCreditLimit;
public:
	enum class ReportCommand
	{
		dayReport = 1, weekReport, monthReport
	};
	enum class RateCommand
	{
		weekRate = 1, monthRate
	};

	Card() = default;
	Card(long num, float sum, bool credit, float creditLimit = 0, float creditSum = 0) 
	: Item(), num{ num }, sum{ sum }, credit{ credit }, creditLimit{ creditLimit }, creditSum{ creditSum }{}
	void enter() override;
	void edit() override;
	void write(std::ostream& output) override;
	void read(std::istream& input) override;
	bool cardType(std::string promt = "");
	void addOperation(const Operation& value);

	void report();
	void dayReport(Date date);
	void weekReport(Date date);
	void monthReport(Date date);
	void addExp(const Operation& value);
	int dayC(Date date);
	void dayExp(Date date, bool replenish = false);
	void rateExpense();
	void weekRateExpense(Date date);
	void monthRateExpense(Date date);
	void rateCategory();
	void weekRateCategory(Date date);
	void monthRateCategory(Date date);
	std::vector<Operation> dayOpVec(Date date, bool replenish = false);
	void rateDisplay(std::vector<Date>& date);
	//friend struct compareDateReaderBook;
	//friend struct compareBookDateReader;
	friend class Cards;
	//friend class Logbook;
	
	friend struct compareCardsByNumber;
	friend struct compareCardsBySum;
	
	struct SumCompare
	{
		float value;
		SumCompare(float value) : value{ value } {};
		bool operator()(const std::pair<int, Item*>& two) const
		{
			return value == static_cast<Card*>(two.second)->sum;
		}
	};
};
