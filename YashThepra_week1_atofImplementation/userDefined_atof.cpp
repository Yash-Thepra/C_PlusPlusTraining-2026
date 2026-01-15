#include<iostream>

void trimLeadingAndTrailingSpaces(std::string &inputString) {
    int startIndex = 0;

    while(startIndex < inputString.length() && inputString[startIndex] == ' ') {
        startIndex++;
    }

    int endIndex = inputString.length() - 1;

    while(endIndex >= 0 && inputString[endIndex] == ' ') {
        endIndex--;
    }

    int newIndex = 0;
    while (startIndex <= endIndex) {
        inputString[newIndex++] = inputString[startIndex++];
    }
    inputString.resize(newIndex);
}

bool isValidInput(std::string inputString) {
    if (inputString.length() == 0 || inputString[inputString.length() - 1] == '.' || inputString[0] == '0') {
        return 0;
    }
    
    int decimalCount = 0;
    for(int index = 0; index < inputString.length(); index++) {
        if (((inputString[index] < '0' || inputString[index] > '9') && inputString[index] != '.') || decimalCount > 1 ) {
            return 0;
        }

        if (inputString[index] == '.') {
            decimalCount++;
        }
    }
    return 1;
}

double convertStringToDouble(std::string inputString) {
    double floatingPointNumber = 0.0;
    bool flagForFractionCheck = 0;
    double decimalFactor = 0.1;

    for(int index = 0; index < inputString.length(); index++) {
        if (inputString[index] == '.') {
            flagForFractionCheck = 1;
        }
        else {
            int number = inputString[index] - '0';
            if (!flagForFractionCheck) {
                floatingPointNumber = (10 * floatingPointNumber) + number;
            }
            else {
                floatingPointNumber += number * decimalFactor;
                decimalFactor /= 10;
            }
        }
    }
    return floatingPointNumber;
}

int main() {
    std::string floatingPointNumber;
    std::cout << "Please Enter the the floating point Number in the string form which is to be converted into double: ";

    while(1) {
        getline(std::cin, floatingPointNumber);

        trimLeadingAndTrailingSpaces(floatingPointNumber);
        if (isValidInput(floatingPointNumber)) break;
        else {
            std::cout << "\nInvalid Input! Try Again: ";
        }
    }

    double resultAfterConversion = convertStringToDouble(floatingPointNumber);
    std::cout << "String of size(" << sizeof(floatingPointNumber) << ") converted to double: " << resultAfterConversion << " of Size(" << sizeof(resultAfterConversion) << ").";
    return 0;
}