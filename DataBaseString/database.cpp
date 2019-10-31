#include "database.h"

#include <iostream>
#include <utility>

Database::Database(std::string Path) : PathName(std::move(Path)) {}

std::string ParseEvent(std::istream &is) {
    while (is.peek() == ' ') {
        is.get();
    }
    std::string event;
    getline(is, event);
    return event;
}

void Database::Add(const std::string &date, const std::string &event) {
    if (!event.empty()) {
        try {
            if (EventBaseSet.at(date).count(event) == 0) {
                EventBase[date].push_back(event);
                EventBaseSet[date].insert(event);
            }
        } catch (...) {
            EventBase[date].push_back(event);
            EventBaseSet[date].insert(event);
        }
    }
}

void Database::Print(std::ostream &stream) const {
    for (const auto &i : EventBase) {
        stream << "Date is " << i.first << std::endl;
        for (const auto &j : i.second) {
            stream << '-' << j << std::endl;
        }
        stream << std::endl;
    }
}

std::string Database::Last(const std::string &date) const {
    if (EventBase.empty()) {
        throw std::invalid_argument("");
    }
    if (date < EventBase.begin()->first) {
        throw std::invalid_argument("");
    }
    auto res = EventBase.upper_bound(date);
    return prev(res)->first + ' ' + prev(res)->second.back();
}

void Database::GetFromFile() {
    std::ifstream input;
    input.open(PathName, std::ios::in);

    if (!input) {
        std::ofstream creation(PathName);
        creation.close();
    } else {
        if (input.is_open()) {
            for (std::string OldEvent; getline(input, OldEvent);) {
                if (OldEvent.empty()) {
                    std::cout << "No events now" << std::endl;
                    break;
                } else {
                    std::istringstream old(OldEvent);
                    const auto date = ParseDate(old);
                    const auto event = ParseEvent(old);
                    Add(date, event);
                }
            }
            input.close();

        } else {
            throw std::runtime_error("ERROR: saved base was not opened");
        }
    }
}

void Database::PutIntoFile() {
    std::ofstream output;
    output.open(PathName, std::ios::out);

    if (output.is_open()) {
        for (const auto &i : EventBase) {
            for (const auto &j : i.second) {
                output << i.first << ' ' << j << std::endl;
            }
        }
    } else {
        throw std::runtime_error("ERROR: database was not saved");
    }
    output.close();
}
