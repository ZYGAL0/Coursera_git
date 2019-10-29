#include "date.h"

std::string ParseDate(std::istream &stream) {
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

    // Checking for valid arguments (throw exception if it's false)
    if (month < 1 || month > 12) {
        throw std::logic_error("Month value is invalid: " + std::to_string(month));
    } else if (day < 1 || day > 31) {
        throw std::logic_error("Day value is invalid: " + std::to_string(day));
    }

    if (!ok) {
        throw std::logic_error("Wrong date format, try other");
    }
    std::string year_ = std::to_string(year);
    year_.insert(year_.begin(), 4 - year_.size(), '0');

    std::string month_ = std::to_string(month);
    month_.insert(month_.begin(), 2 - month_.size(), '0');

    std::string day_ = std::to_string(day);
    day_.insert(day_.begin(), 2 - day_.size(), '0');
    return year_ + '-' + month_ + '-' + day_;
}



