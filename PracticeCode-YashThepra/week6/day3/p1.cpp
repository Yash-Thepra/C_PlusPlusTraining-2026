#include <iostream>

int fact(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * fact(n - 1);
}
int main()
{
    std::cout << "Factorial of 5 is: " << fact(5) << "\n";
    return 0;
}

//used gdb on this program, and the key thing is that we can use up and down in case of recursive fn calls, because suppose program is being recursively called 1 lakh, 2 lakh or more time so, to exactly debug that where's the error the n(next) command is not optimal so what can we do, we can use up number_of_stackFrames/vice-versa for the down which show us that paritcual recursive call so we can easily found where's the bug and also add the break point and also using f frame_number we can also go to that particular frame.