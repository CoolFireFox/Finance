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
    cout << "\n�������� �����" << endl;
    getValue("����� �����: ", num);
    getValue("�����: ", sum);
    credit = cardType("��� �����:\n[1] ��������;\n[2] ���������;\n");
    if (credit) {
        editValue("��������� �����: ", creditLimit);
        creditSum = creditLimit;
    };
}

void Card::edit()
{
    cout << "\n�������� �����" << endl;
    std::stringstream ss;
    std::string str;
    ss << num;
    ss >> str;
    editLine("����� �����: ", str);
    num = stol(str);
    bool editCardType = cardType("������������� ��� �����?\n[1] ���;\n[2] ��;\n");
    if (editCardType) {
        credit = cardType("��� �����:\n[1] ��������;\n[2] ���������;\n");
        if (credit) {
            editValue("��������� �����: ", creditLimit);
            editValue("������� ��������� ������� �� �����: ", creditSum);
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
        std::cout << "�������� �� ���� ��������� ���������." << std::endl;

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

void Card::addOperation(const Operation& value) // ���������� ����� �������
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
                    cout << "�� ����� " << num << " ������������ ������� ��� ������.\n";
                }
        }
        else
            if (credit)
            {
                cout << "�����������:\n" << "[1] �������;\n"
                    << "[2] ����������;\n;";
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
                            cout << "������������ ������� ��� ������.\n";
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
                                cout << "������������ ������� ��� ������.\n";
                            }
                    }
            }
    }else
        if (!value.expenditure) {
            if (credit)
            {
                cout << "���������:\n" << "[1] ������ ��������;\n"
                    << "[2] ��������� �������;\n;";
                while (c < 1 || c > 2) {
                    cout << "\n[->] ";
                    cin >> c;
                }

                if (c == 1) {
                    sum += operationSum;
                    history.push_back(value);
                    cout << "������ �������� ����� " << num << " ��������� �� " << operationSum << ".\n";
                }
                else
                    if (c == 2) {
                        if (creditLimit - creditSum >= operationSum)
                        {
                            creditSum += operationSum;
                            creditHistory.push_back(value);
                            cout << "��������� �������� ����� " << num << " ��������� �� " << operationSum << ".\n";
                        }
                        else
                            if (creditSum < operationSum) {
                                cout << "������������ ������� ��� ������.\n";
                            }
                    }
            }
        }
}

void Card::report()
{
    int reportChoise = 0;
    Date reportDate;
    std::cout << "����� �� �������� ��...\n";
    cout << "[" << (int)ReportCommand::dayReport << "] "
        << "����.\n";
    cout << "[" << (int)ReportCommand::weekReport << "] "
        << "������.\n";
    cout << "[" << (int)ReportCommand::monthReport << "] "
        << "�����.\n";
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
    cout << "������� �� ����� " << num << " �� " << date << endl;
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
    cout << "������� �� ����� " << num << " c " << week[0] << " �� " << week[6] << ":" << endl;
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
    cout << "������� �� ����� " << num << " c " << startDate << " �� " << endDate << ":" << endl;
    for (size_t i = 0; i < month.size(); ++i)
    {
        dayExp(month[i]);
    }
}

int Card::dayC(Date date) // ����������� ������� ���� ����� ������ �� ����, ����� ��������� �� ������ ������
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
    std::cout << "������������ ��������� �� ������������ ������ ������ ��...\n";

    cout << "[" << (int)RateCommand::weekRate << "] "
        << "������.\n";
    cout << "[" << (int)RateCommand::monthRate << "] "
        << "�����.\n";
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
    cout << "���-3 ������ �� ������ �� ����� " << num << " c " << week[0] << " �� " << week[6] << ":" << endl;
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
    cout << "���-3 ������ �� ����� �� ����� " << num << " c " << startDate << " �� " << endDate << ":" << endl;
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

void Card::rateCategory()// ������������ ��������� �� ����� ���������� ��������� ������ �� ������, �����
{
    int reportChoise = 0;
    Date reportDate;
    std::cout << "������������ ��������� �� ���������� ������������ ������ ��...\n";

    cout << "[" << (int)RateCommand::weekRate << "] "
        << "������.\n";
    cout << "[" << (int)RateCommand::monthRate << "] "
        << "�����.\n";
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
    cout << "���-3 ������ �� ������ �� ����� " << num << " c " << week[0] << " �� " << week[6] << ":" << endl;
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
    cout << "���-3 ������ �� ����� �� ����� " << num << " c " << startDate << " �� " << endDate << ":" << endl;
    rateDisplay(month);
}

std::vector<Operation> Card::dayOpVec(Date date, bool replenish)// ������ �������� �� ����� �� ��������� ����
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

void Card::rateDisplay(vector<Date>& date) // ����� �������� �� ��������� ������
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