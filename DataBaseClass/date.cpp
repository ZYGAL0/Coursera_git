#include "date.h"

#include <iomanip>
#include <tuple>

Date::Date(int new_year, int new_month, int new_day) {
    // Checking for valid arguments (throw exception if it's false)
    if (new_month < 1 || new_month > 12) {
        throw std::logic_error("Month value is invalid: " + std::to_string(new_month));
    } else if (new_day < 1 || new_day > 31) {
        throw std::logic_error("Day value is invalid: " + std::to_string(new_day));
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

Date ParseDate(std::istream &stream) {
    bool ok = true;

    int year = 0;
    ok = ok && (stream >> year);
    ok = ok && (stream.peek() == '-');
    stream.ignore(1);

    int month = 0;
    ok = ok && (stream >> month);
    ok = ok && (stream.peek() == '-');
    stream.ignore(1);

    int day = 0;
    ok = ok && (stream >> day);


    if (!ok) {
        throw std::logic_error("Wrong date format, try other");
    }

    return Date(year, month, day);
}

std::ostream &operator<<(std::ostream &stream, const Date &date) {
    stream
            << std::setfill('0') << std::setw(4) << date.GetYear() << "-"
            << std::setfill('0') << std::setw(2) << date.GetMonth() << "-"
            << std::setfill('0') << std::setw(2) << date.GetDay();

    return stream;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
           < std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
           <= std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator==(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
           == std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
           != std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
           >= std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())
           > std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}