#pragma once

#include "date.h"

#include <algorithm>
#include <map>
#include <vector>
#include <set>

class Database {
public:
    void Add(const std::string &date, const std::string &event);

    [[nodiscard]] std::string Last(const std::string &date) const;

    void Print(std::ostream &stream) const;

    template<class Func>
    int RemoveIf(Func func) {
        int counter = 0;
        for (auto x = EventBase.begin(); x != EventBase.end();) {
            auto it = stable_partition(x->second.begin(), x->second.end(), [func, x](const std::string &ev) {
                return !func(x->first, ev);
            });
            counter += distance(it, x->second.end());
            if (it == x->second.begin()) {
                EventBaseSet.erase(x->first);
                x = EventBase.erase(x);
            } else {
                for (auto i = x->second.end() - 1; i >= it;) {
                    EventBaseSet[x->first].erase(*i);
                    --i;
                    EventBase[x->first].pop_back(); // end
                }
                x++;
            }
        }
        return counter;
    }

    template<class Func>
    std::vector<std::string> FindIf(Func func) const {
        std::vector<std::string> res;
        for (const auto &x : EventBase) {
            for (const auto &e : x.second) {
                if (func(x.first, e)) {
                    res.emplace_back(x.first + ' ' + e);
                }
            }
        }
        return res;
    }

private:
    std::map<std::string, std::vector<std::string>> EventBase;
    std::map<std::string, std::set<std::string>> EventBaseSet;
};