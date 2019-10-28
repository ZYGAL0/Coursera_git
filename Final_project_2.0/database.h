#pragma once

#include "date.h"

#include <algorithm>
#include <map>
#include <vector>


class Database {
public:
    void Add(const Date &date, const std::string &event);

    [[nodiscard]] std::pair<Date, std::string> Last(const Date &date) const;

    void Print(std::ostream &stream) const;

    template<class Func>
    int RemoveIf(Func func) {
        int del = 0;
        for (auto &x : db) {
            auto it = stable_partition(x.second.begin(), x.second.end(), [func, &x](const std::string& ev){
                return !func(x.first, ev);
            });
            del += distance(it, x.second.end());
            db[x.first].erase(it, x.second.end());

//            for (auto it = x.second.begin(); it != x.second.end();) {
//                if (func(x.first, *it)) {
//                    del++;
//                    db[x.first].erase(it);
//                } else {
//                    it++;
//                }
//            }
            if (db[x.first].empty()) {
                db.erase(x.first);
            }
        }
        return del;
    }

    template<class Func>
    std::vector<std::pair<Date, std::string>> FindIf(Func func) const {
        std::vector<std::pair<Date, std::string>> res;
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
    std::map<Date, std::vector<std::string>> db;
};