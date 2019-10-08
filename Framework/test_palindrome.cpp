#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
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

bool IsPalindrom(const string &str) {
    for (size_t i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;

}

void TestEmpty () {
    Assert(IsPalindrom(""), "Loh1");
}

void TestSingle () {
    Assert(IsPalindrom("a"), "Loh2");
    Assert(IsPalindrom(" "), "Loh3");
}

void TestDefault () {
    Assert(IsPalindrom("madam"), "Loh4");
    Assert(IsPalindrom("level"), "Loh5");
    Assert(IsPalindrom("lohhol"), "Loh6");
}

void TestWithSpaces () {
    Assert(IsPalindrom(" madam "), "Loh6");
    Assert(IsPalindrom("m ada m"), "Loh7");
    Assert(!IsPalindrom(" madam"), "Loh8");
    Assert(!IsPalindrom("madam "), "Loh9");
    Assert(!IsPalindrom("ma dam"), "Loh10");
    Assert(IsPalindrom("  "), "Loh11");
}
void TestAdditional () {
    Assert(!IsPalindrom("Madam"), "Loh12");
    Assert(IsPalindrom("mad   dam"), "Loh13");
    Assert(!IsPalindrom("777778"), "Loh14");
    Assert(IsPalindrom("777777"), "Loh15");
}


void TestAll () {
    TestRunner runner;
    runner.RunTest(TestEmpty, "TestEmpty");
    runner.RunTest(TestSingle, "TestSingle");
    runner.RunTest(TestDefault, "TestDefault");
    runner.RunTest(TestWithSpaces, "TestWithSpaces");
    runner.RunTest(TestAdditional, "TestAdditional");
}

int main() {
//    TestRunner runner;
    TestAll ();
    return 0;
}