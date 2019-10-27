#pragma once

#include "date.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Database {
public:
    void Add(const Date &date, const string &event);

    [[nodiscard]] pair<Date, string> Last(const Date &date) const;

    void Print(ostream &stream) const;

    template<class Func>
    int RemoveIf(Func func) {
        int del = 0;
        for (const auto &x : db) {
            for (auto it = x.second.begin(); it < x.second.end();) {
                if (func(x.first, *it)) {
                    del++;
                    db[x.first].erase(it);
                } else {
                    it++;
                }
            }
            if (db[x.first].empty()) {
                db.erase(x.first);
            }
        }
        return del;
    }

    template<class Func>
    vector<pair<Date, string>> FindIf(Func func) {
        vector<pair<Date, string>> res;
        for (const auto &x : db) {
            for (const auto &e : x.second) {
                if (func(x.first, e)) {
                    res.emplace_back(x.first, e);
                }
            }
        }
        return res;
    }

private:
    map<Date, vector<string>> db;
};