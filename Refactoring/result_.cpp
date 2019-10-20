#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Human {
public:

	Human(const string & name, const string & occupation):
		Name(name), Occupation(occupation) {
    }
    
	string PrintMe() const
	{
		return Occupation + ": " + Name;
	}

	virtual void Walk(const string & destination) const {
        cout << PrintMe() << " walks to: " << destination << endl;
    }
    
    string GetName() const {
        return Name;
    }
    
    string GetOccupation() const {
        return Occupation;
    }

private:
	const string Name;
	const string Occupation;
};

class Student: public Human {
public:

    Student(const string & name, const string & favouriteSong)
		: Human(name, "Student"), FavouriteSong(favouriteSong) {
    }

    void Learn() const {
        cout << PrintMe() << " learns" << endl;
    }
	
    void SingSong() const {
        cout << PrintMe() << " sings a song: " << FavouriteSong << endl;
    }

    void Walk(const string & destination) const override {
        Human::Walk(destination);
        SingSong();
    }

private:
    const string FavouriteSong;
};


class Teacher: public Human {
public:

    Teacher(const string & name, const string & subject):
		Human(name, "Teacher"), Subject(subject) {
    }

    void Teach() const {
        cout << PrintMe() << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman: public Human {
public:

    Policeman(const string & name):
		Human(name, "Policeman") {
    }

    void Check(const Human & h) {
        cout << PrintMe() << " checks " << h.GetOccupation() << ". "
			 << h.GetOccupation() << "'s name is: " << h.GetName() << endl;
    }
};


void VisitPlaces(Human & h, const vector<string> & places) {
    for (auto p : places) {
        h.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}

