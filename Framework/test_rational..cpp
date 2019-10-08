#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
//        integer = 0;
    }

    Rational(int numerator, int denominator) {
//        if (numerator / denominator != 0) {
//            integer = numerator / denominator;
//            numerator = numerator % denominator;
//        }
        if (denominator == 0) {
            throw invalid_argument("Invalid argument");
        }
        if (numerator == 0) {
            num = 0;
            den = 1;
        } else {
            if (numerator > 0 && denominator > 0) {
                num = numerator;
                den = denominator;
            } else if (numerator < 0 && denominator > 0) {
                num = numerator;
                den = denominator;
                numerator *= -1;
            } else if (numerator > 0 && denominator < 0) {
                num = -numerator;
                den = -denominator;
                denominator *= -1;
            } else {
                num = -numerator;
                den = -denominator;
                denominator *= -1;
                numerator *= -1;
            }
            while (numerator > 0 && denominator > 0) {
                if (numerator > denominator) {
                    numerator %= denominator;
                } else {
                    denominator %= numerator;
                }
            }
            int NOD = numerator + denominator;
            num /= NOD;
            den /= NOD;
        }
    }

    [[nodiscard]] int Numerator() const {
        return num;
    }

    [[nodiscard]] int Denominator() const {
        return den;
    }

private:
    int num;
    int den;
//    int integer;
};

bool operator==(const Rational& lol, const Rational& kek) {
    if (lol.Numerator() == kek.Numerator()) {
        return lol.Denominator() == kek. Denominator();
    } else {
        return lol.Numerator() == kek.Numerator();
    }
}

bool operator>(const Rational& lol, const Rational& kek) {
    return lol.Numerator() * kek.Denominator() > kek.Numerator() * lol.Denominator();
}

bool operator<(const Rational& lol, const Rational& kek) {
    return lol.Numerator() * kek.Denominator() < kek.Numerator() * lol.Denominator();
}

Rational operator+(const Rational& lol, const Rational& kek) {
    int res_den = lol.Denominator() * kek.Denominator();
    int res_num = lol.Numerator() * kek.Denominator() + kek.Numerator() * lol.Denominator();
    return {res_num, res_den};
}

Rational operator-(const Rational& lol, const Rational& kek) {
    int res_den = lol.Denominator() * kek.Denominator();
    int res_num = lol.Numerator() * kek.Denominator() - kek.Numerator() * lol.Denominator();
    return {res_num, res_den};
}

Rational operator*(const Rational& lol, const Rational& kek) {
    int res_den = lol.Denominator() * kek.Denominator();
    int res_num = lol.Numerator() * kek.Numerator();
    return {res_num, res_den};
}

Rational operator/(const Rational& lol, const Rational& kek) {
    if (kek.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    int res_den = lol.Denominator() * kek.Numerator();
    int res_num = lol.Numerator() * kek.Denominator();
    return {res_num, res_den};
}

istream& operator>>(istream& stream, Rational& drob) {
    if (stream) {
        int num = drob.Numerator();
        int den = drob.Denominator();
        stream >> num;
        stream.ignore(1);
        stream >> den;
        Rational res(num, den);
        drob = res;

    }
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& drob) {
    if (stream) {
        stream << drob.Numerator() << '/' << drob.Denominator();
    }
    return stream;
}

Rational Calculate(const Rational& frac1, const Rational& frac2, const char& op) {
    if (op == '+') {
        return (frac1 + frac2);
    } else if (op == '-') {
        return (frac1 - frac2);
    } else if (op == '*') {
        return (frac1 * frac2);
    } else {
        return (frac1 / frac2);
    }
}

void AssertRational(Rational number, int num, unsigned den, const string& hint) {
    AssertEqual(number.Numerator(), num, hint + "Num");
    AssertEqual(number.Denominator(), den, hint + "Den");
}

void TestDefaultConstructor () {
    Rational number;
    AssertRational(number, 0, 1, "Loh1");
}

void TestReduction () {
    Rational number1 (4, 10);
    AssertRational(number1, 2, 5, "Loh2");
    Rational number2 (4, 9);
    AssertRational(number2, 4, 9, "Loh3");
    Rational number3 (0, 9);
    AssertRational(number3, 0, 1, "Loh4");
}

void TestNegativeValues () {
    Rational number1 (-4, 10);
    AssertRational(number1, -2, 5, "Loh5");
    Rational number2 (-0, 10);
    AssertRational(number2, 0, 1, "Loh6");
    Rational number3 (4, -10);
    AssertRational(number3, -2, 5, "Loh7");
    Rational number4 (-4, -10);
    AssertRational(number4, 2, 5, "Loh8");
}

void TestAll () {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestReduction, "TestReduction");
    runner.RunTest(TestNegativeValues, "TestNegativeValues");
}

int main() {
//    TestRunner runner;
    TestAll();
    return 0;
}

