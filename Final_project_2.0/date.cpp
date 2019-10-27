#include "date.h"

#include <vector>
#include <iomanip>
#include <iostream>

Date::Date(int new_year, int new_month, int new_day) {
    // Checking for valid arguments (throw exception if it's false)
    if (new_month < 1 || new_month > 12) {
        throw logic_error("Month value is invalid: " + to_string(new_month));
    } else if (new_day < 1 || new_day > 31) {
        throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    year = new_year;
    month = new_month;
    day = new_day;
}

[[nodiscard]] int Date::GetYear() const {
    return year;
}

[[nodiscard]] int Date::GetMonth() const {
    return month;
}

[[nodiscard]] int Date::GetDay() const {
    return day;
}

Date ParseDate(istringstream &stream) {
    bool ok = true;

    int year;
    ok = ok && (stream >> year);
    ok = ok && (stream.peek() == '-');
    stream.ignore(1);

    int month;
    ok = ok && (stream >> month);
    ok = ok && (stream.peek() == '-');
    stream.ignore(1);

    int day;
    ok = ok && (stream >> day);


    if (!ok) {
        throw logic_error("Wrong date format, try other");
    }
    return Date(year, month, day);
}

ostream &operator<<(ostream &stream, const Date &date) {
    stream
            << setfill('0') << setw(4) << date.GetYear() << "-"
            << setfill('0') << setw(2) << date.GetMonth() << "-"
            << setfill('0') << setw(2) << date.GetDay();

    return stream;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
           < vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
           <= vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator==(const Date &lhs, const Date &rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
           == vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
           != vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
           >= vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>(const Date &lhs, const Date &rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
           > vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}