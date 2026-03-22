#include <gmock/gmock.h>
#include <gtest/gtest.h>

class Database {
public:
    int getData() { return 10; }
};

class Service {
private:
    Database db;   
public:
    int process() {
        return db.getData() * 2;
    }
};

/*class IDatabase {
public:
    virtual int getData() = 0;
    virtual ~IDatabase() = default;
};

class Service {
private:
    IDatabase* db;
public:
    Service(IDatabase* d) : db(d) {}

    int process() {
        return db->getData() * 2;
    }
};*/

class MockDatabase : public /*I*/Database {
public:
    MOCK_METHOD(int, getData, (), ());
};
