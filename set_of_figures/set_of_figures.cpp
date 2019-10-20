#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() = 0;

    virtual double Perimeter() = 0;

    virtual double Area() = 0;
};

class Triangle : public Figure {
public:
    explicit Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {}

    string Name() override { return "TRIANGLE"; }

    double Perimeter() override { return a_ + b_ + c_; }

    double Area() override {
        double p = static_cast<double>(a_ + b_ + c_) / 2;
        double res = sqrt(p * (p - a_) * (p - b_) * (p - c_));
        return res;
    }

private:
    int a_ = 0;
    int b_ = 0;
    int c_ = 0;
};

class Rect : public Figure {
public:
    explicit Rect(int w, int h) : w_(w), h_(h) {}

    string Name() override { return "RECT"; }

    double Perimeter() override { return 2 * (w_ + h_); }

    double Area() override { return w_ * h_; }

private:
    int w_ = 0;
    int h_ = 0;
};

class Circle : public Figure {
public:
    explicit Circle(int r) : r_(r) {}

    string Name() override { return "CIRCLE"; }

    double Perimeter() override { return 6.28 * r_; }

    double Area() override { return 3.14 * r_ * r_; }

private:
    int r_ = 0;
};

shared_ptr<Figure> CreateFigure(istream &is) {
    string name;
    is >> name;
    shared_ptr<Figure> res;
    if (name == "RECT") {
        int w = 0, h = 0;
        is >> w >> h;
        res = make_shared<Rect>(w, h);
        cout << "Creating of RECT is completed!" << endl;
    } else if (name == "TRIANGLE") {
        int a = 0, b = 0, c = 0;
        is >> a >> b >> c;
        res = make_shared<Triangle>(a, b, c);
        cout << "Creating of TRIANGLE is completed!" << endl;
    } else if (name == "CIRCLE") {
        int r = 0;
        is >> r;
        res = make_shared<Circle>(r);
        cout << "Creating of CIRCLE is completed!" << endl;
    } else {
        throw logic_error("Wrong figure!");
    }
    return res;
}

int main() {
    vector<shared_ptr<Figure>> figures;
    cout << "Enter commands like :\n"
         << " - ADD with name of figure and parameters\n"
         << " - PRINT for print all of figures and their perimeters and areas\n"
         << " - EXIT for to end the program\n";

    for (string line; getline(cin, line);) {
        istringstream is(line);
        string command;
        is >> command;
        if (command == "ADD") {
            try {
                figures.push_back(CreateFigure(is));
            } catch (exception &ex) {
                cout << ex.what() << endl;
            }
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        } else if (command == "EXIT") {
            cout << "Program is over!" << endl;
            return 0;
        } else {
            cout << "Wrong command!" << endl;
        }
    }
}