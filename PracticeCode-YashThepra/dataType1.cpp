#include <iostream>
using namespace std;

typedef struct userDefined
{
    int integer;
    char character;
}userDefined;


int main() {
    //Size of Basic data types according to 64 bit architechture

    cout << "Size of Integer data type: " << sizeof(int) << endl;
    cout << "Size of Character data type: " << sizeof(char) << endl;
    cout << "Size of Float data type: " << sizeof(float) << endl;
    cout << "Size of Double data type: " << sizeof(double) << endl;

    char randomCharacter = 'A';
    cout << "random character: " << randomCharacter << endl;
    
    //data type conversion
    cout << "random character to integer: " << (int)randomCharacter << endl;

    //user defined data type

    userDefined variable;
    variable.integer = 10;
    variable.character = 'Y';

    cout << "structure Integer: " << variable.integer << endl;
    cout << "structure Integer: " << variable.character << endl;

    //derived data type and iterative statements
    int arrayOfIntegers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //iteration
    for(int index = 0; index < 10; index++) {
        cout << "value at index " << index << " is: " << arrayOfIntegers[index] << endl;
    }
}