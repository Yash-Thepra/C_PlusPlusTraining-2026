#include <iostream>

int main()
{
    /*
    int arr[5];
    std::cout << arr[5000] << "\n";
    */
    int arr[5] = {1, 2, 3, 4, 5};
    try
    {
        throw arr[500/*0*/];
    }
    catch(const int)
    {
        std::cout << "Exception of type int is catched.\n";
    }
    catch(/*onst std::exception &exception, const std::runtime_error &exception,*/ std::bad_alloc &exception)
    {
        std::cout << "standard exception catched: " << exception.what() << "\n";
    }
    std::cout << "segmenation fault cannot be catched by try and catch(exception handling) since it's an OS operation not an program operation.\n";
    return 0;
}