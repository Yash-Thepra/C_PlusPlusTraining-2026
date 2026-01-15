#include<iostream>

int main() {
    const int constantNumber = 10;
    std::cout << "Value of constant number: " << constantNumber;
    //constantNumber = 11 will give compile time error because it's an constant number hence it's value can't be modified.

    //pointer to constant value
    int exampleOne = 10;
    const int *pointerToOne = &exampleOne;

    std::cout << "\nValue of number before: " << exampleOne;
    //*pointerToOne = 234; can modify but not through pointer deferencing
    exampleOne = 11;
    std::cout << "\nvalue of number after: " << exampleOne;

    //constant pointer here we can modify
    int exampleTwo = 15;
    int *const pointerToTwo = &exampleTwo;
    std::cout << "\nValue of number before: " << exampleTwo;
    *pointerToTwo = 20;
    std::cout << "\nvalue of number after: " << exampleTwo;
}