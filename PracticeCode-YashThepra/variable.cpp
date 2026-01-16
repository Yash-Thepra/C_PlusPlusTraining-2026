#include<iostream>

int main() {
    //int a, int b; it is wront when declaring multiple variable with same data type.
    //int a, b; right but considered bad practice because new variable should appear on new statement

    int exampleVariableOne;
    int exampleVariableTwo;

    //variable initialization
    int copyInitializedVariable = 5; //copy initialization, copies value from right side to left side variable
    int listInitializedVaraible {10};//list initialization
    std::cout << copyInitializedVariable << " " << listInitializedVaraible;
    return 0;
}
