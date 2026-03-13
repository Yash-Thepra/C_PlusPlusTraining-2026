#include <iostream>
#include <gtest/gtest.h>

class ex
{
    int x;

public:
    ex(int val) : x(val) {}
    int getX()
    {
        return x;
    }
    int increment()
    {
        return ++x;
    }
    int decrement()
    {
        return --x;
    }
};

class arrange : public testing::Test
{
public:
    ex *e;
    void SetUp()
    {
        std::cout << "currently in Setup.\n";
        e = new ex(10);
    }
    void TearDown()
    {
        std::cout << "currently in TearDown.\n";
        delete e;
    }
};

TEST_F(arrange, incremennt)
{
    EXPECT_EQ(e->increment() - 1, e->getX());
}


TEST_F(arrange, decrement)
{
    //EXPECT_EQ(e->decrement(), e->getX() - 1);
    EXPECT_EQ(e->getX() - 1, e->decrement());   
}