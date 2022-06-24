#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "Wallet.h"

using namespace std;

void Wallet::enter()
{
    cout << "\nДобавить счёт" << endl;
    getValue("Номер счёта: ", num);
    getValue("Сумма: ", sum);
}

void Wallet::edit()
{
    cout << "\nИзменить счёт" << endl;
    std::stringstream ss;
    std::string str;
    ss << num;
    ss >> str;
    editLine("Номер счёта: ", str);
    num = stol(str);
}

void Wallet::write(ostream& output)
{
    output << num << endl << sum << endl << endl;
}

void Wallet::read(istream& input)
{
    input >> num;
    input.ignore(1);
    input >> sum;
    string endLine;
    getline(input, endLine);
}

void Wallet::addOperation(const Operation& value)
{
    float operationSum = value.sum;
    size_t c = 0;
    if (value.expenditure)
    {
        if (sum >= operationSum)
        {
            sum -= operationSum;
            history.push_back(value);
        }
        else
            if (sum < operationSum) {
                cout << "На счету " << num << " недостаточно средств для оплаты.\n";
            }
    }
    else
        if (!value.expenditure) {
            sum += operationSum;
            history.push_back(value);
            cout << "Личные средства счёта " << num << " пополнены на " << operationSum << ".\n";
        }
}

void Wallet::report()
{
    int reportChoise = 0;
    Date reportDate;
    std::cout << "Отчет по затратам за...\n";
    cout << "[" << (int)ReportCommand::dayReport << "] "
        << "день.\n";
    cout << "[" << (int)ReportCommand::weekReport << "] "
        << "неделю.\n";
    cout << "[" << (int)ReportCommand::monthReport << "] "
        << "месяц.\n";
    while (reportChoise < (int)ReportCommand::dayReport ||
        reportChoise >(int)ReportCommand::monthReport) {
        getValue("[->] ", reportChoise);
    }
    cin >> reportDate;
    switch (reportChoise) {
    case (int)ReportCommand::dayReport:
        Wallet::dayReport(reportDate);
        break;
    case (int)ReportCommand::weekReport:
        Wallet::weekReport(reportDate);
        break;
    case (int)ReportCommand::monthReport:
        Wallet::monthReport(reportDate);
        break;
    default:
        break;
    }
    std::cout << std::endl;
}

void Wallet::dayReport(Date date)
{
    cout << "Затраты по счёту " << num << " за " << date << endl;
    dayRep(date);
    cout << "\n";
}

void Wallet::weekReport(Date date)
{
    Date startDate = date - dayC(date);
    std::vector<Date> week;
    for (size_t j = 1; j < 7; ++j)
    {
        week.push_back(startDate++);
    }
    cout << "Затраты по счёту " << num << " c " << week[0] << " по " << week[6] << ":" << endl;
    for (size_t i = 0; i < 7; ++i)
    {
        dayRep(week[i],false);
    }
    cout << "\n";
}

void Wallet::monthReport(Date date)
{
    Date startDate = firstMonthDay(date);
    Date endDate = lastMonthDay(date);
    Date x = startDate;
    std::vector<Date> month;
    for (int i = startDate.getDay(); i < endDate.getDay(); ++i)
    {
        month.push_back(x++);
    }
    cout << "Затраты по счёту " << num << " c " << startDate << " по " << endDate << ":" << endl;
    for (size_t i = 0; i < month.size(); ++i)
    {
        dayRep(month[i],false);
    }
}

int Wallet::dayC(Date date)
{
    int c[7] = { 6,0,1,2,3,4,5 };
    int i = date.weekDay();
    return c[i];
}

void Wallet::dayRep(Date date, bool replenish)
{
    for (size_t i = 0; i < history.size(); ++i)
    {
        if (history[i].getDate() == date) {

            if (replenish) {
                history[i].write(cout);
            }else
                if (!replenish) {
                    if (!history[i].expenditure)
                    {
                        history[i].write(cout);
                    }
                }
        }
    }
    cout << "\n";
}

void  Wallet::rateExpense()
{
    int reportChoise = 0;
    Date reportDate;
    std::cout << "Формирование рейтингов по максимальным суммам затрат за...\n";

    cout << "[" << (int)RateCommand::weekRate << "] "
        << "неделю.\n";
    cout << "[" << (int)RateCommand::monthRate << "] "
        << "месяц.\n";
    while (reportChoise < (int)RateCommand::weekRate ||
        reportChoise >(int)RateCommand::monthRate) {
        getValue("[->] ", reportChoise);
    }
    cin >> reportDate;
    switch (reportChoise) {
    case (int)RateCommand::weekRate:
        Wallet::weekRateExpense(reportDate);
        break;
    case (int)ReportCommand::monthReport:
        Wallet::monthRateExpense(reportDate);
        break;
    default:
        break;
    }
    std::cout << std::endl;
}

void Wallet::weekRateExpense(Date date)
{
    vector<Operation> op;
    Date startDate = date - dayC(date);
    std::vector<Date> week;
    for (size_t j = 1; j < 7; ++j)
    {
        week.push_back(startDate++);
    }
    cout << "ТОП-3 затрат за неделю по счёту " << num << " c " << week[0] << " по " << week[6] << ":" << endl;
    for (size_t i = 0; i < 7; ++i)
    {
        vector<Operation> tmp = dayOpVec(week[i], false);
        for (size_t j = 0; j < tmp.size(); j++)
        {
            op.push_back(tmp[j]);
        }
    }

    sort(op.begin(), op.end(), Operation::CompareOperationsBySum());
    for (size_t i = 0; i < 3; ++i)
    {
        if (i < op.size())
        {
            op[i].write(cout);
        }
    }
    cout << "\n";
}

void Wallet::monthRateExpense(Date date)
{
    vector<Operation> op;
    Date startDate = firstMonthDay(date);
    Date endDate = lastMonthDay(date);
    Date x = startDate;
    std::vector<Date> month;
    for (int i = startDate.getDay(); i < endDate.getDay(); ++i)
    {
        month.push_back(x++);
    }
    cout << "ТОП-3 затрат за месяц по счёту " << num << " c " << startDate << " по " << endDate << ":" << endl;
    for (size_t i = 0; i < month.size(); ++i)
    {
        vector<Operation> tmp = dayOpVec(month[i], false);
        for (size_t j = 0; j < tmp.size(); j++)
        {
            op.push_back(tmp[j]);
        }
    }
    sort(op.begin(), op.end(), Operation::CompareOperationsBySum());
    for (size_t i = 0; i < 3; ++i)
    {
        if (i < op.size())
        {
            op[i].write(cout);
        }
    }
    cout << "\n";
}

void Wallet::rateCategory()
{
    int reportChoise = 0;
    Date reportDate;
    std::cout << "Формирование рейтингов по категориям максимальных затрат за...\n";

    cout << "[" << (int)RateCommand::weekRate << "] "
        << "неделю.\n";
    cout << "[" << (int)RateCommand::monthRate << "] "
        << "месяц.\n";
    while (reportChoise < (int)RateCommand::weekRate ||
        reportChoise >(int)RateCommand::monthRate) {
        getValue("[->] ", reportChoise);
    }

    getValue("[->] ", reportDate);
    //cin >> reportDate;
    switch (reportChoise) {
    case (int)RateCommand::weekRate:
        Wallet::weekRateCategory(reportDate);
        break;
    case (int)ReportCommand::monthReport:
        Wallet::monthRateCategory(reportDate);
        break;
    default:
        break;
    }
}

void Wallet::weekRateCategory(Date date)
{
    Date startDate = date - dayC(date);
    std::vector<Date> week;
    for (size_t j = 1; j < 7; ++j)
    {
        week.push_back(startDate++);
    }
    cout << "ТОП-3 затрат за неделю по счёту " << num << " c " << week[0] << " по " << week[6] << ":" << endl;
    rateDisplay(week);
}

void Wallet::monthRateCategory(Date date)
{
    Date startDate = firstMonthDay(date);
    Date endDate = lastMonthDay(date);
    Date x = startDate;
    std::vector<Date> month;
    for (int i = startDate.getDay(); i < endDate.getDay(); ++i)
    {
        month.push_back(x++);
    }
    cout << "ТОП-3 затрат за месяц по счёту " << num << " c " << startDate << " по " << endDate << ":" << endl;
    rateDisplay(month);
}

std::vector<Operation> Wallet::dayOpVec(Date date, bool replenish)
{
    std::vector<Operation> op;
    for (size_t i = 0; i < history.size(); ++i)
    {
        if (history[i].getDate() == date) {
            if (!replenish)
            {
                if (!history[i].expenditure)
                {
                    op.push_back(history[i]);
                }
            }else
            if (replenish) {
                op.push_back(history[i]);
            }
        }
    }
    return op;
}

void Wallet::rateDisplay(vector<Date>& date)
{
    struct CatSum
    {
        string c;
        float s;
    };
    vector<Operation> op;
    vector<CatSum> x;
    vector<string> cat;
    struct CompareCatSum
    {
        bool operator()
            (const CatSum& prev, const CatSum& next)
        {
            if (prev.s != next.s)
            {
                return prev.s > next.s;
            }
        }
    };
    for (size_t i = 0; i < 7; ++i)
    {
        vector<Operation> tmp = dayOpVec(date[i]);
        for (size_t j = 0; j < tmp.size(); j++)
        {
            op.push_back(tmp[j]);
        }
    }
    for (size_t i = 0; i < op.size(); ++i)
    {
        cat.push_back(op[i].Operation::getCategory());
    }
    sort(cat.begin(), cat.end());
    cat.erase(unique(cat.begin(), cat.end()), cat.end());
    for (size_t i = 0; i < cat.size(); ++i)
    {
        x.push_back(CatSum{ cat[i], (float)0 });
    }

    for (size_t j = 0; j < x.size(); ++j)
    {
        for (size_t i = 0; i < op.size(); ++i)
        {
            if (x[j].c == op[i].getCategory())
            {
                x[j].s += op[i].getSum();
            }
        }
    }
    sort(x.begin(), x.end(), CompareCatSum());
    for (size_t i = 0; i < 3; ++i)
    {
        if (i < x.size())
        {
            cout << "[" << i << "] " << x[i].c << ": " << x[i].s << endl;
        }
    }
    cout << "\n";
}