#pragma once
#include <iostream>
#include <array>

class Date
{
    static const std::array<int, 13> daysInMonths;

    static const int firstYear;
    static const int lastYear;

    int year;
    int month;
    int day;

    static void yearErrorMsg();
public:
    Date(int year = firstYear, int month = 1, int day = 1);
    //Date(const Date& date) 
    //    : Date(date.year, date.month, date.day)
    //{}
    void setDate(int year, int month, int day);
    
    static bool isCorrectDate(int year, int month, int day);
    static bool isCorrectYear(int year);
    static bool isCorrectMonth(int month);
    static bool isCorrectDay(int year, int month, int day);

    int getYear() const;
    int getMonth() const;
    int getDay() const; 
    
    static bool isLeapYear(int year);
    static Date getCurrentDate();
    bool isEndOfMonth(int day) const;

    void nextDay();
    void prevDay();

    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    Date& operator+=(int days);
    Date& operator-=(int days);

    friend const Date operator+(const Date& date,
        int days);
    friend const Date operator+(int days, 
        const Date& date);
    friend const Date operator-(const Date& date1,
        int days);
    friend int operator-(const Date& date1,
        const Date& date2);

    friend bool operator==(const Date& date1,
        const Date& date2);
    friend bool operator!=(const Date& date1,
        const Date& date2);
    friend bool operator<(const Date& date1,
        const Date& date2);
    friend bool operator>(const Date& date1,
        const Date& date2);

    friend std::ostream& operator<<(std::ostream&, 
        const Date& date);
    friend std::istream& operator>>(std::istream&, Date& date);

    int weekDay();
    friend Date firstMonthDay(Date value);
    friend Date lastMonthDay(Date value);
};

