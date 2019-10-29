#include "database.h"

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
