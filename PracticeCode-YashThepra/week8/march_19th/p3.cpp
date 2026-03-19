/*#include <iostream>
#include <array>

template <typename T, std::size_t N>
void printArray(const std::array<T, N>& arr) {
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << arr[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << "\n";// T=int, N=5
}

int main() {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    printArray(a);
}*/

#include <iostream>
#include <string>

// Generic template
template <typename T>
std::string describe(T x)
{
    return "generic: " + std::to_string(x);
}

// Overload for const char*
std::string describe(const char *s)
{
    return "C-string: " + std::string(s);
}

int main()
{
    std::string str = "hello";
    std::cout << describe(42) << "\n";
    std::cout << describe("hello") << "\n";
    std::cout << describe(3.14) << "\n";

    //std::cout << describe <> ('k') << "\n";
    //std::cout << describe(str) << "\n";
}