#include <iostream>

/*class empty
{
public:
    void print()
    {
        std::cout << "I have no data members\n";
    }
};*/
class con
{
public:
    int x;
    con()
    {
        x = 10;
    }
    con(int val)
    {
        x = val;
    }
    void print()
    {
        std::cout << x << "\n";
    }
    void printt() const
    {
        std::cout << "hi\n";
    }
    void print2() const
    {
        std::cout << "I print constant x: " << x << "\n";
        //print(); error
        printt();
        //x++;
    }
    /*void print3(const int& x)
    {
        print2();
    }*/
};
void print3(const con &ob)
{
    //ob.print();
    ob.print2();
}

int main()
{
    /*empty emp;
    emp.print();
    std::cout << sizeof(empty) << "\n";
    std::cout << sizeof(emp) << "\n";*/

    const con obj;
    con ob;
    // obj.print(); can't call non const mem functions
    obj.print2();
    //obj.print3(ob);
    print3(ob);

    return 0;
}