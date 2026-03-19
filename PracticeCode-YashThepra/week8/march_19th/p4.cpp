#include <iostream>
#include <vector>

template <class T>
void func()
{
    /*typename*/ T:: value_type x; // it will give error since the typename here is must, because other wise how'd compiler would get to know that it is of type or value.
}
int main()
{
    func <std::vector<int>> ();
    return 0;
}