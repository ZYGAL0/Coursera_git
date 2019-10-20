#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    explicit Human(const string &type, const string &name)
            : Type(type), Name(name) {}

    void DoAction(const string &action) const {
        cout << Type << ": " << Name << " " << action;
    }

    virtual void Walk(const string &destination) const {
        DoAction("walks to: ");
        cout << destination << endl;
    }

    const string Type = "Pearson";
    const string Name = "";
};

class Student : public Human {
public:

    Student(const string &name, const string &favouriteSong)
            : Human("Student", name), FavouriteSong(favouriteSong) {}

    void Learn() const {
        DoAction("learns\n");
    }

    void Walk(const string &destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        DoAction("sings a song: ");
        cout << FavouriteSong << endl;
    }

private:
    string FavouriteSong;
};


class Teacher : public Human {
public:

    explicit Teacher(const string &name, const string &subject)
            : Human("Teacher", name), Subject(subject) {}

    void Teach() const {
        DoAction("teaches: ");
        cout << Subject << endl;
    }

private:
    string Subject;
};


class Policeman : public Human {
public:
    explicit Policeman(const string &name)
            : Human("Policeman", name) {}

    void Check(const Human &p) const {
        DoAction("checks ");
        cout << p.Type << ". " << p.Type
             << "'s name is: " << p.Name << endl;
    }
};

void VisitPlaces(Human &p, const vector<string> &places) {
    for (const auto &item : places) {
        p.Walk(item);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    s.Learn();
    t.Teach();
    return 0;
}
