#include <iostream>
#include <iomanip>
#include <ctime>
#include "Date.h"
using namespace std;

const std::array<int, 13> Date::daysInMonths
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const int Date::firstYear{ 1900 };
const int Date::lastYear{ 2100 };

Date::Date(int year, int month, int day)
{
    if (!isCorrectDate(year, month, day))
    {
        year = firstYear;
        month = 1;
        day = 1;
    }
    setDate(year, month, day);
}

void Date::setDate(int year, int month, int day)
{
    if (isCorrectDate(year, month, day))
    {
        this->year = year;
        this->month = month;
        this->day = day;
    }
}

bool Date::isCorrectDate(int year,
    int month, int day)
{
    return isCorrectYear(year) &&
        isCorrectMonth(month) &&
        isCorrectDay(year, month, day);
}

bool Date::isCorrectYear(int year)
{
    if (year < firstYear || year > lastYear)
    {
        yearErrorMsg();
        return false;
    }

    return true;
}

bool Date::isCorrectMonth(int month)
{
    if (month < 1 || month > 12)
    {
        cout << "ћес€ц должент быть в пределах 1-12." << endl;
        return false;
    }

    return true;
}

bool Date::isCorrectDay(int year,
    int month, int day)
{
    if ((day < 1) ||
        (day > Date::daysInMonths[month]))
    {
        if (!(month == 2 && isLeapYear(year) && day == 29))
        {
            cout << "Ќе существует дн€ дл€ такой комбинации года и мес€ца!" << endl;
            return false;
        }
    }

    return true;
}

int Date::getYear() const
{
    return year;
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

bool Date::isLeapYear(int year)
{
    return (year % 400 == 0 ||
        (year % 100 != 0 && year % 4 == 0));
}

bool Date::isEndOfMonth(int day) const
{
    if (month == 2 && isLeapYear(year))
    {
        return day == 29;
    }
    else
    {
        return day == daysInMonths[month];
    }
}

void Date::nextDay()
{
    if (!isEndOfMonth(day))
    {
        day++;
    }
    else
    {
        if (month < 12)
        {
            month++;
            day = 1;
        }
        else
            if (year < lastYear)
            {
                year++;
                month = 1;
                day = 1;
            }
            else
            {
                yearErrorMsg();
            }
    }
}

void Date::prevDay()
{
    if (day > 1)
    {
        day--;
    }
    else
        if (month > 1)
        {
            month--;
            if (month == 2 && isLeapYear(year))
            {
                day = 29;
            }
            else
            {
                day = daysInMonths[month];
            }
        }
        else
            if (year > firstYear)
            {
                year--;
                month = 12;
                day = 31;
            }
            else
            {
                yearErrorMsg();
            }
}

Date& Date::operator++()
{
    nextDay();
    return *this;
}

Date Date::operator++(int) 
{
    Date temp{ *this };
    nextDay();

    return temp;
}

Date& Date::operator--()
{
    prevDay();
    return *this;
}

Date Date::operator--(int)
{
    Date temp{ *this };
    prevDay();

    return temp;
}

Date& Date::operator+=(int days)
{
    if (days < 0)
    {
        *this -= -days;
        //return operator-=(-days);
    }

    for (int i = 0; i < days; i++) 
    {
        nextDay();
    }

    return *this;
}

Date& Date::operator-=(int days)
{
    if (days < 0)
    {
        *this += -days;
    }

    for (int i = 0; i < days; i++)
    {
        prevDay();
    }

    return *this;
}

const Date operator+(const Date& date, int days)
{
    Date result = date;
    result += days;
    return result;
}

const Date operator+(int days, const Date& date)
{
    return date + days;
}

const Date operator-(const Date& date, int days)
{
    Date result = date;
    result -= days;
    return result;
}

int operator-(const Date& date1, const Date& date2)
{
    bool negative = false;
    Date largerDate = date1;
    Date lesserDate = date2;

    if (largerDate < lesserDate)
    {
        swap(largerDate, lesserDate);
        negative = true;
    }
    int count = 0;
    while (lesserDate < largerDate)
    {
        lesserDate++;
        count++;
    }

    return negative ? -count : count;
}

bool operator==(const Date& date1,const Date& date2)
{
    return date1.year == date2.year &&
        date1.month == date2.month &&
        date1.day == date2.day;
}

bool operator!=(const Date& date1, const Date& date2)
{
    return !(date1 == date2);
}

bool operator<(const Date& date1, const Date& date2)
{
    return 
        date1.year < date2.year ? true :
        date1.year > date2.year ? false :
        date1.month < date2.month ? true :
        date1.month > date2.month ? false :
        date1.day < date2.day ? true : false;
}

bool operator>(const Date& date1, const Date& date2)
{
    return
        date1.year > date2.year ? true :
        date1.year < date2.year ? false :
        date1.month > date2.month ? true :
        date1.month < date2.month ? false :
        date1.day > date2.day ? true : false;
}

ostream& operator<<(ostream& output, const Date& date)
{
    output << setfill('0') << setw(2) << date.day << "." << 
        setw(2) << date.month << "." << date.year;
    output << setfill(' ');
    return output;
}

istream& operator>>(istream& input, Date& date)
{
    int year;
    int month;
    int day;

    input >> day;
    input.ignore(1);
    input >> month;
    input.ignore(1);
    input >> year;

    if (Date::isCorrectDate(year, month, day))
    {
        date.setDate(year, month, day);
    }
    else
    {
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

void Date::yearErrorMsg()
{
    cout << "√од должен быть >= " << firstYear <<
        " и <= " << lastYear << endl;
}

Date Date::getCurrentDate()
{
    time_t tSpecial = time(nullptr);
    struct tm aTime;
    if (localtime_s(&aTime, &tSpecial) == 0)
    {
        int day = aTime.tm_mday;
        int month = aTime.tm_mon + 1;
        int year = 1900 + aTime.tm_year;
        return Date(year, month, day);
    }
    return Date();
}


//#include <ctime>
//struct tm {
//        tm_sec,                         /* секунды 0..59 */
//        tm_min,                         /* минуты  0..59 */
//        tm_hour,                        /* час дн€ 0..23 */
//        tm_mday,                    /* день мес€ца 1..31 */
//        tm_mon,                           /* мес€ц 0..11 */
//        tm_year,                       /* год после 1900 */
//        tm_wday,         /* день недели, 0..6 (Sun..Sat) */
//        tm_yday,                    /* день года, 0..365 */
//        tm_isdst;        /* >0, если есть поправка на сдвиг,
//                            =0, если нет поправки,
//                            <0, если неизвестно */

int Date::weekDay()
{
    int weekDay[7] = { 0,1,2,3,4,5,6 };
    return weekDay[(7000 + (day + year / 4 - year / 100 + year / 400 + (31 * month) / 12)) % 7];
}

Date firstMonthDay(Date value)
{
    return Date(value.year, value.month, 1);
}

Date lastMonthDay(Date value)
{
    return Date(value.year, value.month, Date::daysInMonths[value.month]);
}