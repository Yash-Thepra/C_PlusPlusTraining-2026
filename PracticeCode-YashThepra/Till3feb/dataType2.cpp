#include<iostream>

using namespace std;

int main() {
    //operator precedence, bitwise operations, and conditional statements
    int variableA = 5;
    int variableB = 7;
    
    int userChoice;
    cout << "a. Enter 1 for bitwise or\nb. Enter 2 for bitwise xor\nc. Enter 3 for bitwise and\nd. Enter 4 for bitwise nor\n";
    cin >> userChoice;
    
    if (userChoice == 1) {
        cout << "variable A | variable B: " << (variableA | variableB) << endl; 
    }
    else if (userChoice == 2) {
        cout << "variable A ^ variable B: " << (variableA ^ variableB) << endl;
    }
    else if (userChoice == 3) {
        cout << "variable A & variable B: " << (variableA & variableB) << endl;
    }
    else if (userChoice == 4) {
        cout << "~variable A: " << (~variableA) << endl;
    }
    else {
        cout << "Invalid choice! ending program..." << endl;
    }

    //operator precedence
    int sum1 = variableA + variableB * variableA / variableB;
    int sum2 = (variableA + variableB) + variableA / variableB;

    cout << "sum1: " << sum1 << endl;
    cout << "sum2: " << sum2 << endl;
    //bit shifting
    cout << "Right shift of variable A by 1: " << (variableA >> 1) << endl; //divides by 2
    cout << "Left shift of variable A by 1: " << (variableA << 1) << endl;//multiply by 2 
}