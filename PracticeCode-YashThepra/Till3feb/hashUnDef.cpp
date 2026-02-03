#include <iostream>
#define MUL(a, b) a * b
#define MULT(a, b) (a) * (b)

int main()
{
    std::cout << "multiplication of 3 and 11: " << MUL(3, 11);
    std::cout << "\nmultiplication of 5 - 2 and 7 + 4: " << MUL(5 - 2, 7 + 4);
    std::cout << "\nnow using another preprocessing directive multiplication of 3 and 11: " << MULT(3, 11);
    std::cout << "\nnow using another preprocessing directive multiplication of 5 - 2 and 7 + 4: " << MULT(5 - 2, 7 + 4);    
    return 0;

    #undef MUL
    //std::cout << "\nmultiplication of 3 and 11 after undefining preprocessor directive: " << MUL(3, 11);

   /* #ifndef MUL
        std::cout << "\n3 multiply by 11: " << MULT(3, 11);
    #endif
        std::cout << "\n3 multiply by 11: " << MUL(3, 11);*/
    return 0;
}
