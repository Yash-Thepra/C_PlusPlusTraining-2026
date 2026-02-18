#include <iostream>

struct S
{
    int x;
    int y;
};

void print(const S &obj)
{
    std::cout << obj.x << " " << obj.y << "\n";
}
int main()
{
    S s{};
    std::cout << s.x << " " << s.y << "\n";
    S r;
    std::cout << r.x << " " << r.y << "\n";
    S q{10, 11};
    std::cout << q.x << " " << q.y << "\n";
    //S p(10, 33); error no matching function to call
    print(q);
    //print(S o{10, 11}); error
    print(S {});
    print(S {10, 40});
    print(S ());
    //print(S (10, 434)); no matching function to call error
    print({});//implicit conversion
    print({10});
    print({10, 40});
    return 0;
}