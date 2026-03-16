#include <gtest/gtest.h>
#include <sstream>

#include "input.h"

static void simulateInput(const std::string &data)
{
    static std::istringstream *stream = nullptr;
    delete stream;
    stream = new std::istringstream(data);
    std::cin.rdbuf(stream->rdbuf());
}

TEST(TrimTest, TrimsLeadingSpaces)
{
    std::string s = "   hello";
    Input::trimInputData(s);
    EXPECT_EQ(s, "hello");
}

TEST(TrimTest, TrimsTrailingSpaces)
{
    std::string s = "hello   ";
    Input::trimInputData(s);
    EXPECT_EQ(s, "hello");
}

TEST(TrimTest, TrimsBothSides)
{
    std::string s = "  hello  ";
    Input::trimInputData(s);
    EXPECT_EQ(s, "hello");
}

TEST(TrimTest, EmptyStringRemainsEmpty)
{
    std::string s = "";
    Input::trimInputData(s);
    EXPECT_EQ(s, "");
}

TEST(TrimTest, OnlySpacesBecomesEmpty)
{
    std::string s = "   ";
    Input::trimInputData(s);
    EXPECT_EQ(s, "");
}

TEST(TrimTest, StringWithNoSpacesIsUnchanged)
{
    std::string s = "hello";
    Input::trimInputData(s);
    EXPECT_EQ(s, "hello");
}

TEST(TrimTest, InternalSpacesArePreserved)
{
    std::string s = "  hello world  ";
    Input::trimInputData(s);
    EXPECT_EQ(s, "hello world");
}

class ReadValidDoubleTest : public ::testing::Test {};

TEST_F(ReadValidDoubleTest, AcceptsPositiveDecimal)
{
    simulateInput("123.45\n");
    EXPECT_DOUBLE_EQ(Input::readValidDouble(), 123.45);
}

TEST_F(ReadValidDoubleTest, AcceptsWholeNumber)
{
    simulateInput("100\n");
    EXPECT_DOUBLE_EQ(Input::readValidDouble(), 100.0);
}

TEST_F(ReadValidDoubleTest, AcceptsZero)
{
    simulateInput("0\n");
    EXPECT_DOUBLE_EQ(Input::readValidDouble(), 0.0);
}

TEST_F(ReadValidDoubleTest, AcceptsNegativeValue)
{
    simulateInput("-50.5\n");
    EXPECT_DOUBLE_EQ(Input::readValidDouble(), -50.5);
}

TEST_F(ReadValidDoubleTest, RejectsNonNumericThenAcceptsValid)
{
    simulateInput("abc\n100.0\n");
    EXPECT_DOUBLE_EQ(Input::readValidDouble(), 100.0);
}

TEST_F(ReadValidDoubleTest, RejectsEmptyLineThenAcceptsValid)
{
    simulateInput("\n50.0\n");
    EXPECT_DOUBLE_EQ(Input::readValidDouble(), 50.0);
}

TEST_F(ReadValidDoubleTest, RejectsDoubleDecimalThenAcceptsValid)
{
    simulateInput("1.2.3\n99.0\n");
    EXPECT_DOUBLE_EQ(Input::readValidDouble(), 99.0);
}

class ReadNonEmptyStringTest : public ::testing::Test {};

TEST_F(ReadNonEmptyStringTest, ReturnsValidString)
{
    simulateInput("hello\n");
    EXPECT_EQ(Input::readNonEmptyString(), "hello");
}

TEST_F(ReadNonEmptyStringTest, RejectsEmptyLineThenAcceptsValid)
{
    simulateInput("\nhello\n");
    EXPECT_EQ(Input::readNonEmptyString(), "hello");
}

TEST_F(ReadNonEmptyStringTest, TrimsLeadingAndTrailingSpaces)
{
    simulateInput("  hello  \n");
    EXPECT_EQ(Input::readNonEmptyString(), "hello");
}

TEST_F(ReadNonEmptyStringTest, RejectsSpacesOnlyThenAcceptsValid)
{
    simulateInput("   \nhello\n");
    EXPECT_EQ(Input::readNonEmptyString(), "hello");
}

class ValidMobileTest : public ::testing::TestWithParam<std::string> {};

TEST_P(ValidMobileTest, ValidMobileIsAccepted)
{
    simulateInput(GetParam() + "\n");
    EXPECT_EQ(Input::readValidMobile(), GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    ValidMobiles,
    ValidMobileTest,
    ::testing::Values(
        "9876543210",
        "1234567890",
        "0000000000"
    )
);

class InvalidMobileTest : public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(InvalidMobileTest, InvalidMobileTriggersRetryAndAcceptsValid)
{
    auto [invalid, valid] = GetParam();
    simulateInput(invalid + "\n" + valid + "\n");
    EXPECT_EQ(Input::readValidMobile(), valid);
}

INSTANTIATE_TEST_SUITE_P(
    InvalidMobiles,
    InvalidMobileTest,
    ::testing::Values(
        std::make_pair("123",        "9876543210"),
        std::make_pair("abcdefghij", "9876543210"),
        std::make_pair("",           "9876543210"),
        std::make_pair("987654321a", "9876543210"),
        std::make_pair("98765432100","9876543210") 
    )
);

class ValidPasswordTest : public ::testing::TestWithParam<std::string> {};

TEST_P(ValidPasswordTest, ValidPasswordIsAccepted)
{
    simulateInput(GetParam() + "\n");
    EXPECT_EQ(Input::readValidPassword(), GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    ValidPasswords,
    ValidPasswordTest,
    ::testing::Values(
        "pass",
        "pass1234",
        "abcd",
        "P@ssword1"
    )
);

class InvalidPasswordTest : public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(InvalidPasswordTest, ShortPasswordTriggersRetryAndAcceptsValid)
{
    auto [invalid, valid] = GetParam();
    simulateInput(invalid + "\n" + valid + "\n");
    EXPECT_EQ(Input::readValidPassword(), valid);
}

INSTANTIATE_TEST_SUITE_P(
    InvalidPasswords,
    InvalidPasswordTest,
    ::testing::Values(
        std::make_pair("",    "pass1234"),
        std::make_pair("ab",  "pass1234"),
        std::make_pair("abc", "pass1234")
    )
);
