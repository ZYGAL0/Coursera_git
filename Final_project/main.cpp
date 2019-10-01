#include <iostream>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <vector>

using namespace std;

// Class Date for setting and saving date

class Date {
public:

    // Constructor for Date
    Date (int new_year, int new_month, int new_day) {
        // Checking for valid arguments (throw exception if it's false)
        if (new_month < 1 || new_month > 12) {
            throw logic_error("Month value is invalid: " + to_string(new_month));
        } else if (new_day < 1 || new_day > 31) {
            throw logic_error("Day value is invalid: " + to_string(new_day));
        }
        year = new_year;
        month = new_month;
        day = new_day;
    }

    [[nodiscard]] int GetYear() const {
        return year;
    };

    [[nodiscard]] int GetMonth() const {
        return month;
    };

    [[nodiscard]] int GetDay() const {
        return day;
    };

private:
    int year; // Can be less than zero
    int month;
    int day;
};

Date ParseDate(const string& date) {
    istringstream stream(date);
    bool ok = true;

    int year;
    ok = ok && (stream >> year);
    ok = ok && (stream.peek() == '-');
    stream.ignore(1);

    int month;
    ok = ok && (stream >> month);
    ok = ok && (stream.peek() == '-');
    stream.ignore(1);

    int day;
    ok = ok && (stream >> day);
    ok = ok && stream.eof();

    if (!ok) {
        throw logic_error("Wrong date format: " + date);
    }
    return Date(year, month, day);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return vector<int> {lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
        < vector<int> {rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

ostream& operator << (ostream& stream, const Date& date) {
    stream
    << setfill('0') << setw(4) << date.GetYear() << "-"
    << setfill('0') << setw(2) << date.GetMonth() << "-"
    << setfill('0') << setw(2) << date.GetDay();
    return stream;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        if (!event.empty()) {
            db[date].insert(event);
        }
    }

    bool DeleteEvent(const Date& date, const string& event) {
        try {
            if (db.at(date).count(event) != 0) {
                db.at(date).erase(event);
                return true;
            } else {
                return false;
            }
        } catch (exception &ex) {
            return false;
        }
    }

    int DeleteDate(const Date& date) {
        int N = db[date].size();
        db.erase(date);
        return N;
    }

    void Find(const Date& date) const {
        try {
            if (!db.at(date).empty()) {
                for (const auto& i : db.at(date)) {
                    cout << i << endl;
                }
            }
        } catch (exception &ex) {
            // Problem with tests on Coursera
            cout << "There are not any events on this date.";
        }
    }

    void Print() const {
        for (const auto& i : db) {
            for (const auto& j : i.second) {
                cout << i.first << ' ' << j << endl;
            }
        }
    }

private:
    map<Date, set<string>> db;
};

int main() {
    // Declaration DateBase
    Database db;

    string command;
    // Endless cycle for reading commands
    while (getline(cin, command)) {
        try {
            // Check empty command
            if (command.empty()) {
                continue;
            }

            istringstream cur_stream(command);
            string cur_com;
            cur_stream >> cur_com;

            if (cur_com == "Add") {
                // Add new event
                string etad, event;
                cur_stream >> etad;
                cur_stream >> event;
                db.AddEvent(ParseDate(etad), event);
            } else if (cur_com == "Del") {
                string date, event;
                cur_stream >> date >> event;
                if (event.empty()) {
                    // Delete all events on this date
                    cout << "Deleted " + to_string(db.DeleteDate(ParseDate(date)))
                    + " events" << endl;
                } else {
                    // Delete certain event
                    if (db.DeleteEvent(ParseDate(date), event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            } else if (cur_com == "Find") {
                // Searching for events on this date
                string etad;
                cur_stream >> etad;
                db.Find(ParseDate(etad));
            } else if (cur_com == "Print") {
                // Print all events
                db.Print();
            } else {
                // Check invalid command
                cout << "Unknown command: " + cur_com << endl;
            }
        } catch (exception &ex) {
            cout << ex.what() << endl;
        }
    }
    return 0;
}