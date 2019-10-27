#include <iostream>
#include <algorithm>
#include "database.h"
#include "date.h"

void Database::Add(const Date &date, const string &event) {
    if (!event.empty()) {
        db[date].push_back(event);
        int res = count(db[date].begin(), db[date].end(), event);
        if (res != 1) {
            auto it = find(db[date].begin(), db[date].end(), event);
            db[date].erase(it);
        }
    }
}

void Database::Print(ostream &stream) const {
    for (const auto &i : db) {
        for (const auto &j : i.second) {
            stream << i.first << ' ' << j << endl;
        }
    }
}

pair<Date, string> Database::Last(const Date &date) const {
    if (date < db.begin()->first) {
        throw invalid_argument("");
    }
    auto res = db.upper_bound(date);
    return {prev(res)->first, prev(res)->second.back()};
}
