#include <iostream>

int main()
{
    int **ptr = new int*[5];
    for (int i = 0; i < 5; i++)
    {
        ptr[i] = new int[2];
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            ptr[i][j] = 0;
        }
    }

    //delete ptr; undefined behaviour
    //delete[] ptr;
    //std::cout << ptr[0][1] << "\n";
   
    for(int i = 0; i < 5; i++)
    {
        delete[] ptr[i];
    }

    //std::cout << ptr[0] << "\n";
    //std::cout << ptr[0][3] << "\n";
    return 0;
}