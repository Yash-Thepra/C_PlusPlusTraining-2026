#include <iostream>

int divide(int a, int b)
{
    return a / b;
}

void print(int ans)
{
    std::cout << "answer: " << ans << "\n";
}
int main()
{
    int ans = divide(10, 20);
    //print(ans);
    std::cout << "answer: " << ans << "\n";
    return 0;
}

// debugged this program using dgb