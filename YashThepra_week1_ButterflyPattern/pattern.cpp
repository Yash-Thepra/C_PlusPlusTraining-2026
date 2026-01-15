#include <iostream>

void trimInputString(std::string &inputValue) {
    int startIndex = 0;

    while(startIndex < inputValue.length() && inputValue[startIndex] == ' ') {
        startIndex++;
    }
    int endIndex = inputValue.length() - 1;

    while(endIndex >= 0 && inputValue[endIndex] == ' ') {
        endIndex--;
    }
    
    int newIndex = 0;
    while (startIndex <= endIndex) {
        inputValue[newIndex++] = inputValue[startIndex++];
    }
    inputValue.resize(newIndex);
}

bool isValidInput(std::string inputValue) {
    if (inputValue.length() == 0 || inputValue[0] == '0') {
        return 0;
    }

    for(int index = 0; index < inputValue.length(); index++) {
        if (inputValue[index] < '0' || inputValue[index] > '9') {
            return 0;
        }
    }
    return 1;
}

int convertStringToNumber(std::string inputValue) {
    int resultantNumber = 0;
    for(int index = 0; index < inputValue.length(); index++) {
        resultantNumber = (10 * resultantNumber) + (inputValue[index] - '0');
    }
    return resultantNumber;
}

void printPattern(int totalNumberOfRows) {
    int halfNumberOfRows = totalNumberOfRows / 2;

    for(int rowIndex = 1; rowIndex <= halfNumberOfRows;  rowIndex++) {
        int flag = 1;
        int columnIndex = 1;

        while (columnIndex <= rowIndex) {
            std::cout << flag;
            if (flag) {
                flag = 0;
            }
            else {
                flag = 1;
            }
            columnIndex++;
        }
        while (columnIndex <= totalNumberOfRows - rowIndex) {
            std::cout << " ";
            columnIndex++;
        }

        flag = 1;
        while (columnIndex <= totalNumberOfRows) {
            std::cout << flag;
            if (flag) {
                flag = 0;
            }
            else {
                flag = 1;
            }
            columnIndex++;
        }
        std::cout << "\n";
    }

    for(int rowIndex = halfNumberOfRows + 1; rowIndex <= totalNumberOfRows; rowIndex++) {
        int flag = 1;
        int columnIndex = 1;
        while (columnIndex <= (totalNumberOfRows + 1) - rowIndex) {
            std::cout << flag;
            if (flag) {
                flag = 0;
            }
            else {
                flag = 1;
            }
            columnIndex++;
        }
        if (columnIndex < rowIndex) {
            flag = 1;
            while (columnIndex < rowIndex) {
            std::cout << " ";
            columnIndex++;
            }
        }
        while (columnIndex <= totalNumberOfRows) {
            std::cout << flag;
            if (flag) {
                flag = 0;
            }
            else {
                flag = 1;
            }
            columnIndex++;
        }
        std::cout << "\n";
    }
}

int main() {
    std::string valueToFindPatternSize = "";
    std::cout << "NOTE: The total number of rows in the pattern are determined by the formula:- (2n - 1.)\nPlease Enter the value of n accordingly for pattern print: ";
    while (1) {
        getline(std::cin, valueToFindPatternSize);
        trimInputString(valueToFindPatternSize);
        if (isValidInput(valueToFindPatternSize)) {
            break;
        }
        else {
            std::cout << "\nInvalid Input! Try Again: ";
        }
    }
    
    int totalNumberOfRows = (2 * convertStringToNumber(valueToFindPatternSize)) - 1;
    printPattern(totalNumberOfRows);
    return 0;
}
