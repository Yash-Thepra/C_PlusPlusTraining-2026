#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class IDatabase {
public:
    virtual int fetchSalary(int id) = 0;
    virtual ~IDatabase() = default;
};


class RealDatabase : public IDatabase {
public:
    int fetchSalary(int id) override {
        std::cout << "Fetching from real DB\n";
        return 1000;
    }
};

class SalaryService {
    IDatabase* db;

public:
    SalaryService(IDatabase* db) : db(db) {}

    int getSalary(int id) {
        if (id <= 0) return -1;
        return db->fetchSalary(id);
    }
};

class MockDatabase : public IDatabase {
public:
    MOCK_METHOD(int, fetchSalary, (int id), (override));
};

TEST(SalaryServiceTest, ValidId_ReturnsSalary)
{
    //MockDatabase mockDb;
    testing::NiceMock<MockDatabase> mockDb;
    /*
    EXPECT_CALL(mockDb, fetchSalary(10))
        .Times(1)
        .WillOnce(testing::Return(5000));*/
    
    ON_CALL(mockDb, fetchSalary(testing::_))
        .WillByDefault(/*testing::Return(5000)*/testing::Invoke([] (int id)
    {
        if (id == 10) return 5000;
        else return 4000;
    }));

    SalaryService service(&mockDb);

    int result = service.getSalary(10);
    EXPECT_EQ(result, 5000);
    result = service.getSalary(20);
    EXPECT_EQ(result, 4000);
}
