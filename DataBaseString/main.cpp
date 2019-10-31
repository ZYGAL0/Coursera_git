#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "test_runner.h"

#include <fstream>

std::string ParseEvent(std::istream &is) {
    while (is.peek() == ' ') {
        is.get();
    }
    std::string event;
    getline(is, event);
    return event;
}

void TestParseEvent();

void GetFromFile(std::ifstream &input, Database &db);

void TestAll();

int main() {

    TestAll();

    Database EventBase;

    std::ifstream input("DataBase");

    if (input.is_open()) {
        GetFromFile(input, EventBase);
    } else {
        std::cout << "ERROR with open saved base!" << std::endl;
    }

    for (std::string line; getline(std::cin, line);) {
        try {
            std::istringstream is(line);

            std::string command;
            is >> command;
            if (command == "Add") {
                const auto date = ParseDate(is);
                const auto event = ParseEvent(is);
                EventBase.Add(date, event);
            } else if (command == "Print") {
                EventBase.Print(std::cout);
            } else if (command == "Del") {
                auto condition = ParseCondition(is);
                auto predicate = [condition](const std::string &date, const std::string &event) {
                    return condition->Evaluate(date, event);
                };
                int count = EventBase.RemoveIf(predicate);
                std::cout << "Removed " << count << " entries" << std::endl;
            } else if (command == "Find") {
                auto condition = ParseCondition(is);
                auto predicate = [condition](const std::string &date, const std::string &event) {
                    return condition->Evaluate(date, event);
                };

                const auto entries = EventBase.FindIf(predicate);
                for (const auto &entry : entries) {
                    std::cout << entry << std::endl;
                }
                std::cout << "Found " << entries.size() << " entries" << std::endl;
            } else if (command == "Last") {
                try {
                    std::cout << EventBase.Last(ParseDate(is)) << std::endl;
                } catch (std::invalid_argument &) {
                    std::cout << "No entries" << std::endl;
                }
            } else if (command.empty()) {
                continue;
            } else if (command == "EXIT") {
                break;
            } else {
                throw std::logic_error("Unknown command: " + command);
            }
        } catch (std::exception &ex) {
            std::cout << ex.what() << std::endl;
        }
    }

    std::ofstream output("DataBase");

    if (output.is_open()) {
        EventBase.Print(output);
    } else {
        std::cout << "ERROR with open file!" << std::endl;
    }
    output.close();

    return 0;
}

void GetFromFile(std::ifstream &input, Database &db) {
    for (std::string OldEvent; getline(input, OldEvent);) {
        if (OldEvent.empty()) {
            std::cout << "No events." << std::endl;
            break;
        } else {
            std::istringstream old(OldEvent);
            const auto date = ParseDate(old);
            const auto event = ParseEvent(old);
            db.Add(date, event);
        }
    }
    input.close();
}

void TestParseEvent() {
    {
        std::istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }

    {
        std::istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }

    {
        std::istringstream is("  first event  \n  second event");
        std::vector<std::string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, std::vector<std::string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
//    tr.RunTest(TestParseCondition, "TestParseCondition");
}