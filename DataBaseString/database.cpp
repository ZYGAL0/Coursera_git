#include "database.h"

#include <iostream>

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
        for (const auto &j : i.second) {
            stream << i.first << ' ' << j << std::endl;
        }
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

void GetFromFile(std::ifstream &input, Database &db) {
    for (std::string OldEvent; getline(input, OldEvent);) {
        if (OldEvent.empty()) {
            std::cout << "No events." << std::endl;
            break;
        } else {
            std::istringstream old(OldEvent);
            const auto date = ParseDate(old);
            const auto event = ParseEvent(old);
            db.Add(date, event);
        }
    }
    input.close();
}
