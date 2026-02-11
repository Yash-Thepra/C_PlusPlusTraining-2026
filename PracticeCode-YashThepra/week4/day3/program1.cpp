#include <iostream>

class boss
{
    int age;
    int id;
    public:
    boss(int age, int id)
    {
        this->age = age;
        this->id = id;
    }
    ~boss()
    {
        std::cout << "Destructor called\n";
    }
    void print()
    {
        std::cout << age << "\n";
        std::cout << id << "\n";
    }
};
int main()
{
    //boss yash; default constructor dead after the mannual implementation
    boss yash(22, 3796);
    yash.print();//automatic call for memory deallocation via destructor for non-dynamically allocated object.

    boss *thepra = new boss(22, 3796);
    //thepra.print(); invalid
    (*thepra).print();//correct way
    thepra->print();
    delete thepra;
    return 0;
}