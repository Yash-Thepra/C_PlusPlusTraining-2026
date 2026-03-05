#include <iostream>

int main()
{
    try {
        int age = 19/*15*/;

        if(age < 18)
            throw age;

        std::cout << "Access granted\n";
    }
    catch(int x) {
        std::cout << "Access denied. Age = " << x << "\n";
    }
}