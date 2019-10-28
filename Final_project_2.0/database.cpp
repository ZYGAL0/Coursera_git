#include "database.h"

void Database::Add(const Date &date, const std::string &event) {
    if (!event.empty()) {
        try {
            auto it = find(db.at(date).begin(), db.at(date).end(), event);
            if (it == db.at(date).end()) {
                db[date].push_back(event);
            }
        } catch (...) {
            db[date].push_back(event);
        }
    }
//    if (!event.empty()) {
//        try {
//
//            auto it = remove(db.at(date).begin(), db.at(date).end(), event);
//            if (it != db.at(date).end()) {
//                db.at(date).erase(it);
//            }
//
//        } catch (exception &ex) {
//        }
//        db[date].push_back(event);
//    }
//    if (!event.empty()) {
//        db[date].push_back(event);
//        int res = count(db[date].begin(), db[date].end(), event);
//        if (res != 1) {
//            auto it = find(db[date].begin(), db[date].end(), event);
//            db[date].erase(it);
//        }
//    }
}

void Database::Print(std::ostream &stream) const {
    for (const auto &i : db) {
        for (const auto &j : i.second) {
            stream << i.first << ' ' << j << std::endl;
        }
    }
}

std::pair<Date, std::string> Database::Last(const Date &date) const {
    if (db.empty()) {
        throw std::invalid_argument("");
    }
    if (date < db.begin()->first) {
        throw std::invalid_argument("");
    }
    auto res = db.upper_bound(date);
    return {prev(res)->first, prev(res)->second.back()};
}
