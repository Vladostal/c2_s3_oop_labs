#include <sstream>
#include <utility>
#include <gtest/gtest.h>
#include "temperature_set.hpp"

TEST(TemperatureTest, KelvinFromCelsius) {
    Temperature t(0.0, Unit::Celsius);

    EXPECT_DOUBLE_EQ(t.kelvin(), 273.15);
}

TEST(TemperatureTest, KelvinFromFahrenheit) {
    Temperature t(32.0, Unit::Fahrenheit);

    EXPECT_DOUBLE_EQ(t.kelvin(), 273.15);
}

TEST(TemperatureTest, EqualInDifferentUnits) {
    Temperature c(0.0, Unit::Celsius);
    Temperature f(32.0, Unit::Fahrenheit);
    Temperature k(273.15, Unit::Kelvin);

    EXPECT_TRUE(c == f);
    EXPECT_TRUE(f == k);
    EXPECT_TRUE(c == k);
}

TEST(TemperatureTest, NotEqual) {
    Temperature a(10.0, Unit::Celsius);
    Temperature b(10.0, Unit::Kelvin);

    EXPECT_FALSE(a == b);
}

TEST(TemperatureTest_Fail, BelowAbsoluteZeroIsInvalid) {
    Temperature t(-300.0, Unit::Celsius);

    EXPECT_FALSE(t.is_valid());
}

TEST(TemperatureTest, Print) {
    Temperature t(36.6, Unit::Celsius);
    std::ostringstream out;
    out << t;

    EXPECT_EQ(out.str(), "36.6 C");
}

TEST(TemperatureSetCreateTest, EmptySet) {
    TemperatureSet s;

    EXPECT_EQ(s.size(), 0u);
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s.contains(Temperature(0.0, Unit::Celsius)));
}

TEST(TemperatureSetAddTest, AddNewAndDuplicate) {
    TemperatureSet s;

    EXPECT_TRUE(s.add(Temperature(20.0, Unit::Celsius)));
    EXPECT_FALSE(s.add(Temperature(20.0, Unit::Celsius)));
    EXPECT_EQ(s.size(), 1u);
}

TEST(TemperatureSetAddTest, DuplicateInOtherUnit) {
    TemperatureSet s;

    EXPECT_TRUE(s.add(Temperature(0.0, Unit::Celsius)));
    EXPECT_FALSE(s.add(Temperature(32.0, Unit::Fahrenheit)));
    EXPECT_FALSE(s.add(Temperature(273.15, Unit::Kelvin)));
    EXPECT_EQ(s.size(), 1u);
}

TEST(TemperatureSetAddTest_Fail, InvalidTemperature) {
    TemperatureSet s;

    EXPECT_FALSE(s.add(Temperature(-1.0, Unit::Kelvin)));
    EXPECT_TRUE(s.empty());
}

TEST(TemperatureSetRemoveTest, RemoveExisting) {
    TemperatureSet s;
    s.add(Temperature(1.0, Unit::Celsius));
    s.add(Temperature(2.0, Unit::Celsius));

    EXPECT_TRUE(s.remove(Temperature(1.0, Unit::Celsius)));
    EXPECT_EQ(s.size(), 1u);
    EXPECT_FALSE(s.contains(Temperature(1.0, Unit::Celsius)));
}

TEST(TemperatureSetRemoveTest_Fail, RemoveMissing) {
    TemperatureSet s;
    s.add(Temperature(1.0, Unit::Celsius));

    EXPECT_FALSE(s.remove(Temperature(5.0, Unit::Celsius)));
    EXPECT_EQ(s.size(), 1u);
}

TEST(TemperatureSetRemoveTest, RemoveKeepsOrder) {
    TemperatureSet s;
    s.add(Temperature(1.0, Unit::Celsius));
    s.add(Temperature(2.0, Unit::Celsius));
    s.add(Temperature(3.0, Unit::Celsius));
    s.remove(Temperature(1.0, Unit::Celsius));
    std::ostringstream out;
    out << s;

    EXPECT_EQ(out.str(), "{ 2 C, 3 C }");
}

TEST(TemperatureSetContainsTest, ContainsAndCallAgree) {
    TemperatureSet s;
    Temperature a(10.0, Unit::Celsius);
    Temperature b(50.0, Unit::Fahrenheit);
    Temperature c(99.0, Unit::Celsius);
    s.add(a);

    EXPECT_EQ(s.contains(a), s(a));
    EXPECT_EQ(s.contains(b), s(b));
    EXPECT_EQ(s.contains(c), s(c));
    EXPECT_TRUE(s(b));
    EXPECT_FALSE(s(c));
}

TEST(TemperatureSetOperatorTest, PlusMinusAssignChain) {
    TemperatureSet s;
    s += Temperature(1.0, Unit::Celsius);
    s += Temperature(2.0, Unit::Celsius);
    s -= Temperature(1.0, Unit::Celsius);

    EXPECT_EQ(s.size(), 1u);
    EXPECT_TRUE(s(Temperature(2.0, Unit::Celsius)));
}

TEST(TemperatureSetCopyTest, CopyIsIndependent) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    TemperatureSet b(a);
    b.add(Temperature(2.0, Unit::Celsius));

    EXPECT_EQ(a.size(), 1u);
    EXPECT_EQ(b.size(), 2u);
}

TEST(TemperatureSetCopyTest, CopyAssignment) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    TemperatureSet b;
    b.add(Temperature(5.0, Unit::Celsius));
    b = a;
    b.remove(Temperature(1.0, Unit::Celsius));

    EXPECT_EQ(a.size(), 1u);
    EXPECT_TRUE(b.empty());
}

TEST(TemperatureSetCopyTest, SelfAssignment) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    TemperatureSet &ref = a;
    a = ref;

    EXPECT_EQ(a.size(), 1u);
    EXPECT_TRUE(a(Temperature(1.0, Unit::Celsius)));
}

TEST(TemperatureSetMoveTest, MoveConstructorEmptiesSource) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    TemperatureSet b(std::move(a));

    EXPECT_EQ(b.size(), 1u);
    EXPECT_TRUE(a.empty());
}

TEST(TemperatureSetMoveTest, MoveAssignmentEmptiesSource) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    TemperatureSet b;
    b.add(Temperature(7.0, Unit::Celsius));
    b = std::move(a);

    EXPECT_EQ(b.size(), 1u);
    EXPECT_TRUE(b(Temperature(1.0, Unit::Celsius)));
    EXPECT_TRUE(a.empty());
}

TEST(TemperatureSetMoveTest, MoveFromEmpty) {
    TemperatureSet a;
    TemperatureSet b(std::move(a));

    EXPECT_TRUE(a.empty());
    EXPECT_TRUE(b.empty());
}

TEST(TemperatureSetOpsTest, Union) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    a.add(Temperature(2.0, Unit::Celsius));
    TemperatureSet b;
    b.add(Temperature(2.0, Unit::Celsius));
    b.add(Temperature(3.0, Unit::Celsius));
    TemperatureSet c = a | b;

    EXPECT_EQ(c.size(), 3u);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 2u);
}

TEST(TemperatureSetOpsTest, Intersection) {
    TemperatureSet a;
    a.add(Temperature(0.0, Unit::Celsius));
    a.add(Temperature(2.0, Unit::Celsius));
    TemperatureSet b;
    b.add(Temperature(32.0, Unit::Fahrenheit));
    b.add(Temperature(3.0, Unit::Celsius));
    TemperatureSet c = a & b;

    EXPECT_EQ(c.size(), 1u);
    EXPECT_TRUE(c(Temperature(0.0, Unit::Celsius)));
}

TEST(TemperatureSetOpsTest, Difference) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    a.add(Temperature(2.0, Unit::Celsius));
    TemperatureSet b;
    b.add(Temperature(2.0, Unit::Celsius));
    TemperatureSet c = a - b;

    EXPECT_EQ(c.size(), 1u);
    EXPECT_TRUE(c(Temperature(1.0, Unit::Celsius)));
    EXPECT_FALSE(c(Temperature(2.0, Unit::Celsius)));
}

TEST(TemperatureSetEqualTest, OrderDoesNotMatter) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    a.add(Temperature(2.0, Unit::Celsius));
    TemperatureSet b;
    b.add(Temperature(2.0, Unit::Celsius));
    b.add(Temperature(1.0, Unit::Celsius));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TemperatureSetEqualTest, DifferentSets) {
    TemperatureSet a;
    a.add(Temperature(1.0, Unit::Celsius));
    TemperatureSet b;
    b.add(Temperature(1.0, Unit::Celsius));
    b.add(Temperature(2.0, Unit::Celsius));

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TemperatureSetPrintTest, PrintEmpty) {
    TemperatureSet s;
    std::ostringstream out;
    out << s;

    EXPECT_EQ(out.str(), "{ }");
}

TEST(TemperatureSetPrintTest, PrintInInsertOrder) {
    TemperatureSet s;
    s.add(Temperature(10.0, Unit::Celsius));
    s.add(Temperature(50.0, Unit::Fahrenheit));
    s.add(Temperature(0.0, Unit::Kelvin));
    std::ostringstream out;
    out << s;

    EXPECT_EQ(out.str(), "{ 10 C, 0 K }");
}

TEST(TemperatureSetStressTest, ThousandAdds) {
    TemperatureSet s;
    for (int i = 0; i < 1000; ++i) {
        s.add(Temperature(i, Unit::Kelvin));
    }
    for (int i = 0; i < 1000; ++i) {
        s.add(Temperature(i, Unit::Kelvin));
    }

    EXPECT_EQ(s.size(), 1000u);
    EXPECT_TRUE(s(Temperature(999.0, Unit::Kelvin)));
}
