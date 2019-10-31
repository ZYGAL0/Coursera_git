#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "test_runner.h"
#include "tests.h"

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
            } else if (command == "Exit") {
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