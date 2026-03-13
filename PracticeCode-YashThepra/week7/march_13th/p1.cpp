#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DB
{
public:
    virtual bool login(int id);
    virtual int getId();
    //implementation not necessary.
};

class myDB
{
    DB &mine;
public:
    myDB(DB &obj) : mine(obj) {}
    int init(int id)
    {
        if (mine.login(id) == true)
        {
            std::cout << "DB sucess.\n";
            return 1;
        }
        else 
        {
            std::cout << "DB failure.\n";
            return -1;
        }
    }
};

class mockDB : public DB
{
    MOCK_METHOD0(getId, int ());
    MOCK_METHOD1(login, bool (int id));
};

TEST(DBopr, login)
{
    //arrange
    mockDB mdb;
    myDB db(mdb);
    EXPECT_CALL(mdb, login(1));
    
    //act

    //assert
}