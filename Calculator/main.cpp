#include <iostream>
#include <set>


using namespace std;



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

    int Numerator() const {
        return num;
    }

    int Denominator() const {
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

int main() {
    try {
        char op = 0;
        Rational fraction1;
        Rational fraction2;
        cin >> fraction1;
        cin.ignore(1);
        cin >> op;
        cin.ignore(1);
        cin >> fraction2;
        Rational res =Calculate(fraction1, fraction2, op);
        cout << res;
    } catch (exception& ex) {
        cout << ex.what() << endl;
    }
    return 0;
}