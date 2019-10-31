#include "tests.h"
#include "database.h"

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
//    tr.RunTest(TestParseCondition, "TestParseCondition");
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

