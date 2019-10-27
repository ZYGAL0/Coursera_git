#pragma once

#include <sstream>

using namespace std;

class Date {
public:

    // Constructor for Date
    Date(int new_year, int new_month, int new_day);

    [[nodiscard]] int GetYear() const;

    [[nodiscard]] int GetMonth() const;

    [[nodiscard]] int GetDay() const;

private:
    int year; // Can be less than zero
    int month;
    int day;
};

Date ParseDate(istringstream &stream);

ostream &operator<<(ostream &stream, const Date &date);

bool operator<(const Date &lhs, const Date &rhs);

bool operator<=(const Date &lhs, const Date &rhs);

bool operator==(const Date &lhs, const Date &rhs);

bool operator!=(const Date &lhs, const Date &rhs);

bool operator>=(const Date &lhs, const Date &rhs);

bool operator>(const Date &lhs, const Date &rhs);

