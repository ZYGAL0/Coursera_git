#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

template<typename Collection>
string Join(const Collection &c, char d);

template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p);

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &vi);

template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m);

template<typename Num>
Num Sqr(Num x);

template<typename T>
vector<T> operator*(const vector<T> &v1, const vector<T> &v2);

template<typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second> &p1, const pair<First, Second> &p2);

template<typename Key, typename Value>
map<Key, Value> operator*(const map<Key, Value> &m1, const map<Key, Value> &m2);

int main() {

    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    cout << Sqr(2.5) << endl;

    cout << Sqr(make_pair(2, 2.5)) << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    vector<double> vi = {1.4, 2, 3};
    cout << vi << endl;
    map<int, double> m = {{1, 2.5}, {3, 4}};
    cout << m << endl;
    vector<vector<int>> lol = {{1, 2}, {3, 4}};
    cout << lol << endl;
    return 0;
}

template<typename Collection>
string Join(const Collection &c, char d) {
    stringstream ss;
    bool first = true;
    for (const auto &i : c) {
        if (!first) {
            ss << d;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &vi) {
    return out << '[' << Join(vi, ',') << ']';
}

template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m) {
    return out << '{' << Join(m, ',') << '}';
}

template<typename Smh>
Smh Sqr(Smh x) {
    return x * x;
}

template<typename T>
vector<T> operator*(const vector<T> &v1, const vector<T> &v2) {
    vector<T> res = v1;
    for (int i = 0; i < static_cast<int>(v1.size()); i++) {
        res[i] = res[i] * v2[i];
    }
    return res;
}

template<typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second> &p1, const pair<First, Second> &p2) {
    return {p1.first * p2.first, p1.second * p2.second};
}

template<typename Key, typename Value>
map<Key, Value> operator*(const map<Key, Value> &m1, const map<Key, Value> &m2) {
    map<Key, Value> res = m1;
    for (const auto &[key_, value_] : m2) {
        res[key_] = res[key_] * value_;
    }
    return res;
}