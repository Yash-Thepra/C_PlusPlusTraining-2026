#include <iostream>

template <class example> 
example first(example a, example b)
{
    return a > b ? a : b;
}

int main()
{
    //int x, y;
    //double x, y;
    //char x, y;
    //std::cout << "Enter the value of the x and y: \n";
    //std::cin >> x;
    //std::cout << "\n";
    //std::cin >> y;
    //std::cout << "\n";
    //std::cout << "The greatest of the two numbers " << x << " and " << y << " is: " << first </*int*/> (x, y) << "\n";

    //std::cout << first(x, y) << "\n";
    //std::cout << first <double> (x,y) << "\n";
    //std::cout <<first <double> (10, 11.5) << "\n";
    //std::cout << first(2, 'a'); error
    //std::cout << first(5, 6.3) << "\n"; -> no instance matches.
    int x = 3;
    int y = 4.5;
    double y2 = 2.4;
    double x2 = 3;
    std::cout << first(5.6, 6.3) << "\n";
    std::cout << first(x, y) << "\n";
    //std::cout << first(x, y2) << "\n"; error
    //std::cout << first <> (x, y2) << "\n"; error
    std::cout << first <int> (x, y2) << "\n";
    std::cout << first <double> (x, y2) << "\n";
    std::cout << first <int> (x2, y2) << "\n";
    std::cout << first(x2, y2) << "\n";
    std::cout << first <double> (x2, y2) << "\n";
    return 0;
}
