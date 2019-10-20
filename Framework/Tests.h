#include <string>

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