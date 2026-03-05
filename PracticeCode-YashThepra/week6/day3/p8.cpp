#include <iostream>

/*void crash()
{
    int *ptr = nullptr;
    *ptr = 10;   // segmentation fault
}

int main()
{
    std::cout << "Program started\n";
    crash();
    std::cout << "Program ended\n";
}*/

#include <iostream>

int sum(int n)
{
    int s = 0;

    for(int i = 1; i <= n; i++)
    {
        s += i;
    }
    return s;
}

int main()
{
    int result = sum(5);
    std::cout << "Sum = " << result << std::endl;
}