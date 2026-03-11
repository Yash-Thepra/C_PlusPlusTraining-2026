#include <iostream>

class A
{
public:
    A(int x)
    {
        this->x = x;
    }
    int getX() const
    {
        return x;
    }
    void setX(int value)
    {
        x = value;
    }
private:
    int x;
};

int main()
{
    A a(10);
    A b(9);
    //copy assignmnet normally
    /*a = b;*/
    b.operator=(a);
    std::cout << "value of x in a: " << a.getX() << "\nvalue of x in b: " << b.getX() << "\n";
    a.operator=(b);
    std::cout << "value of x in a: " << a.getX() << "\nvalue of x in b: " << b.getX() << "\n";
    a.setX(15);
    b.setX(25);
    std::cout << "value of x in a: " << a.getX() << "\nvalue of x in b: " << b.getX() << "\n";
    b.operator=(a);
    std::cout << "value of x in a: " << a.getX() << "\nvalue of x in b: " << b.getX() << "\n";
    int arr[3] = {1, 3, 20};
    /*std::cout << arr[0] << "\n";
    std::cout << arr[10] << "\n";
    std::cout << arr[500] << "\n";*/
    //std::cout << arr[5000] << "\n";
    return 0;
}