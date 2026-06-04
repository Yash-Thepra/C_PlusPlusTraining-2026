#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class BankAccount
{
private:
    int balance;
    std::mutex mtx;

public:
    BankAccount(int amount)
        : balance(amount)
    {
    }

    void deposit(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx);

        balance += amount;
    }

    void withdraw(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx);

        if(balance >= amount)
        {
            balance -= amount;
        }
    }

    int getBalance()
    {
        std::lock_guard<std::mutex> lock(mtx);

        return balance;
    }
};

void worker(BankAccount& account)
{
    for(int i = 0; i < 1000; ++i)
    {
        account.deposit(10);
        account.withdraw(5);
    }
}

int main()
{
    BankAccount account(1000);

    std::vector<std::thread> threads;

    for(int i = 0; i < 5; ++i)
    {
        threads.emplace_back(worker, std::ref(account));
    }

    for(auto& t : threads)
    {
        t.join();
    }

    std::cout << account.getBalance();
    return 0;
}
