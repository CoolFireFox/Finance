#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "Card.h"

using namespace std;
enum class ReportCommand
{
    dayReport = 1, weekReport = 2, monthReport = 3
};

enum class RateCommand
{
    weekRate = 1, monthRate = 2
};

void Card::enter()
{
    cout << "\nДобавить карту" << endl;
    getValue("Номер карты: ", num);
    getValue("Сумма: ", sum);
    credit = cardType("Тип карты:\n[1] Дебитная;\n[2] Кредитная;\n");
    if (credit) {
        editValue("Кредитный лимит: ", creditLimit);
        creditSum = creditLimit;
    };
}

void Card::edit()
{
    cout << "\nИзменить карту" << endl;
    std::stringstream ss;
    std::string str;
    ss << num;
    ss >> str;
    editLine("Номер карты: ", str);
    num = stol(str);
    bool editCardType = cardType("Редактировать тип карты?\n[1] Нет;\n[2] Да;\n");
    if (editCardType) {
        credit = cardType("Тип карты:\n[1] Дебитная;\n[2] Кредитная;\n");
        if (credit) {
            editValue("Кредитный лимит: ", creditLimit);
            editValue("Остаток кредитных средств на карте: ", creditSum);
        };
    }
}

void Card::write(ostream& output)
{
    output << num << endl << sum << endl << credit << endl
         << creditLimit << endl << creditSum << endl;
}

void Card::read(istream& input)
{
    std::string n;
    std::string s;
    std::string c;
    std::string cl;
    std::string cs;
    getline(input, n);
    getline(input, s);
    getline(input, c);
    getline(input, cl);
    getline(input, cs);
    num = stol(n);
    sum = stof(s);
    credit = stoi(s);
    creditLimit = stof(cl);
    creditSum = stof(cs);
}

bool Card::cardType(std::string prompt)
{
    size_t value;
    bool choise = true;
    std::cout << prompt;
    std::cin >> value;

    while (std::cin.fail() || value < 1 || value > 2)
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Выберите из двух доступных вариантов." << std::endl;

        std::cout << prompt;
        std::cin >> value;
    }
    if (value == 1)
    {
        choise == false;
    }else
        if (value == 2)
        {
            choise == true;
        }
    
    return choise;
}

void Card::addOperation(const Operation& value) // добавление новой затраты
{
    float operationSum = value.sum;
    size_t c = 0;
    if (value.expenditure) 
    {
        if (!credit)
        {
            if (sum >= operationSum)
            {
                sum -= operationSum;
                history.push_back(value);
            }
            else
                if (sum < operationSum) {
                    cout << "На карте " << num << " недостаточно средств для оплаты.\n";
                }
        }
        else
            if (credit)
            {
                cout << "Расчитаться:\n" << "[1] Личными;\n"
                    << "[2] Кредитными;\n;";
                while (c < 1 || c > 2) {
                    cout << "\n[->] ";
                    cin >> c;
                }

                if (c == 1) {
                    if (sum >= operationSum)
                    {
                        sum -= operationSum;
                        history.push_back(value);
                    }
                    else
                        if (sum < operationSum) {
                            cout << "Недостаточно средств для оплаты.\n";
                        }
                }
                else
                    if (c == 2) {
                        if (creditSum >= operationSum)
                        {
                            creditSum -= operationSum;
                            history.push_back(value);
                        }
                        else
                            if (creditSum < operationSum) {
                                cout << "Недостаточно средств для оплаты.\n";
                            }
                    }
            }
    }else
        if (!value.expenditure) {
            if (credit)
            {
                cout << "Пополнить:\n" << "[1] Личные средства;\n"
                    << "[2] Кредитный балланс;\n;";
                while (c < 1 || c > 2) {
                    cout << "\n[->] ";
                    cin >> c;
                }

                if (c == 1) {
                    sum += operationSum;
                    history.push_back(value);
                    cout << "Личные средства карты " << num << " пополнены на " << operationSum << ".\n";
                }
                else
                    if (c == 2) {
                        if (creditLimit - creditSum >= operationSum)
                        {
                            creditSum += operationSum;
                            creditHistory.push_back(value);
                            cout << "Кредитные средства карты " << num << " пополнены на " << operationSum << ".\n";
                        }
                        else
                            if (creditSum < operationSum) {
                                cout << "Недостаточно средств для оплаты.\n";
                            }
                    }
            }
        }
}

void Card::report()
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
        Card::dayReport(reportDate);
        break;
    case (int)ReportCommand::weekReport:
        Card::weekReport(reportDate);
        break;
    case (int)ReportCommand::monthReport:
        Card::monthReport(reportDate);
        break;
    default:
        break;
    }
    std::cout << std::endl;
}

void Card::dayReport(Date date)
{
    cout << "Затраты по карте " << num << " за " << date << endl;
    dayExp(date);
    cout << "\n";
}

void Card::weekReport(Date date)
{
    Date startDate = date - dayC(date);
    std::vector<Date> week;
    for (size_t j = 1; j < 7; ++j)
    {
        week.push_back(startDate++);
    }
    cout << "Затраты по карте " << num << " c " << week[0] << " по " << week[6] << ":" << endl;
    for (size_t i = 0; i < 7; ++i)
    {
        dayExp(week[i]);
    }
    cout << "\n";
}

void Card::monthReport(Date date)
{
    Date startDate = firstMonthDay(date);
    Date endDate = lastMonthDay(date);
    Date x = startDate;
    std::vector<Date> month;
    for (int i = startDate.getDay(); i < endDate.getDay(); ++i)
    {
        month.push_back(x++);
    }
    cout << "Затраты по карте " << num << " c " << startDate << " по " << endDate << ":" << endl;
    for (size_t i = 0; i < month.size(); ++i)
    {
        dayExp(month[i]);
    }
}

int Card::dayC(Date date) // определение сколько дней нужно отнять от даты, чтобы вернуться на начало недели
{
    int c[7] = { 6,0,1,2,3,4,5 };
    int i = date.weekDay();
    return c[i];
}

void Card::dayExp(Date date, bool replenish)
{
    for (size_t i = 0; i < history.size(); ++i)
    {
        if (history[i].getDate() == date) {

            if (replenish) {
                history[i].write(cout);
            }
            else 
            if(!replenish){
                if (!history[i].expenditure) {
                    history[i].write(cout);
                }
            }
        }
    }
    cout << "\n";
}

void  Card::rateExpense()
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
        Card::weekRateExpense(reportDate);
        break;
    case (int)ReportCommand::monthReport:
        Card::monthRateExpense(reportDate);
        break;
    default:
        break;
    }
    std::cout << std::endl;
}

void Card::weekRateExpense(Date date)
{
    vector<Operation> op;
    Date startDate = date - dayC(date);
    std::vector<Date> week;
    for (size_t j = 1; j < 7; ++j)
    {
        week.push_back(startDate++);
    }
    cout << "ТОП-3 затрат за неделю по карте " << num << " c " << week[0] << " по " << week[6] << ":" << endl;
    for (size_t i = 0; i < 7; ++i)
    {
        vector<Operation> tmp = dayOpVec(week[i]);
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

void Card::monthRateExpense(Date date)
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
    cout << "ТОП-3 затрат за месяц по карте " << num << " c " << startDate << " по " << endDate << ":" << endl;
    for (size_t i = 0; i < month.size(); ++i)
    {
        vector<Operation> tmp = dayOpVec(month[i]);
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

void Card::rateCategory()// формирование рейтингов по самой популярной категории затрат за неделю, месяц
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
    cin >> reportDate;
    switch (reportChoise) {
    case (int)RateCommand::weekRate:
        Card::weekRateCategory(reportDate);
        break;
    case (int)ReportCommand::monthReport:
        Card::monthRateCategory(reportDate);
        break;
    default:
        break;
    }
}

void Card::weekRateCategory(Date date)
{
    Date startDate = date - dayC(date);    
    std::vector<Date> week;
    for (size_t j = 1; j < 7; ++j)
    {
        week.push_back(startDate++);
    }
    cout << "ТОП-3 затрат за неделю по карте " << num << " c " << week[0] << " по " << week[6] << ":" << endl;
    rateDisplay(week);
}

void Card::monthRateCategory(Date date)
{
    Date startDate = firstMonthDay(date);
    Date endDate = lastMonthDay(date);
    Date x = startDate;
    std::vector<Date> month;
    for (int i = startDate.getDay(); i < endDate.getDay(); ++i)
    {
        month.push_back(x++);
    }
    cout << "ТОП-3 затрат за месяц по карте " << num << " c " << startDate << " по " << endDate << ":" << endl;
    rateDisplay(month);
}

std::vector<Operation> Card::dayOpVec(Date date, bool replenish)// вектор операций по карте за указанный день
{
    std::vector<Operation> op;
    for (size_t i = 0; i < history.size(); ++i)
    {
        if (history[i].getDate() == date) {

            if (replenish) {
                op.push_back(history[i]);
            }
            else
                if (!replenish) {
                    if (!history[i].expenditure) {
                        op.push_back(history[i]);
                    }
                }
        }
    }
    for (size_t i = 0; i < creditHistory.size(); ++i)
    {
        if (creditHistory[i].getDate() == date) {

            if (replenish) {
                op.push_back(creditHistory[i]);
            }
            else
                if (!replenish) {
                    if (!creditHistory[i].expenditure) {
                        op.push_back(creditHistory[i]);
                    }
                }
        }
    }
    return op;
}

void Card::rateDisplay(vector<Date>& date) // вывод рейтинга за указанный период
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