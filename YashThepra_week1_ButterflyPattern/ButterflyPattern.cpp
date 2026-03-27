#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

void trimInputString(string &inputValue) {
    int startIndex = 0;

    while(startIndex < inputValue.length() && inputValue[startIndex] == ' ') startIndex++;
    int endIndex = inputValue.length() - 1;

    while(endIndex >= 0 && inputValue[endIndex] == ' ') endIndex--;
    
    int newIndex = 0;
    while (startIndex <= endIndex) {
        inputValue[newIndex++] = inputValue[startIndex++];
    }
    inputValue.resize(newIndex);
}

int isValidInput(string inputValue) {
    if (inputValue.length() == 0) return 0;
    for(int index = 0; index < inputValue.length(); index++) {
        int temp = (int)(inputValue[index] - '0');
       
        if (temp < 0 || temp > 9)
            return 0;

        if (index == 0 && temp == 0)
            return 0;
    }
    return 1;
}

int stringToNum(string inputValue) {
    int num = 0;
    for(int index = 0; index < inputValue.length(); index++) {
        num = (10 * num) + (int)(inputValue[index] - '0');
    }
    return num;
}

int main() {
    string numColumnsOfSingleSide = "";
    cout << "Enter the number of Columns for the Single side of the pattern: ";
    while (1) {
        cin >> numColumnsOfSingleSide;
        cout << '\n';
        trimInputString(numColumnsOfSingleSide);
        if (isValidInput(numColumnsOfSingleSide)) break;
        else {
            cout << "Invalid Input! Try Again.\n";
            getchar();
        }
    }

    int numOfOneSideColumns = stringToNum(numColumnsOfSingleSide);
    
    int numberOfRows = (2 * numOfOneSideColumns) - 1;

    int halfNumberOfRows = numberOfRows / 2;

    for(int rowIndex = 1; rowIndex <= halfNumberOfRows;  rowIndex++) {
        int flag = 1;
        int columnIndex = 1;

        while (columnIndex <= rowIndex) {
            cout << flag;
            if (flag) flag = 0;
            else flag = 1;
            columnIndex++;
        }
        while (columnIndex <= numberOfRows - rowIndex) {
            cout << " ";
            columnIndex++;
        }

        flag = 1;
        while (columnIndex <= numberOfRows) {
            cout << flag;
            if (flag) flag = 0;
            else flag = 1;
            columnIndex++;
        }
        cout << "\n";
    }

    for(int rowIndex = halfNumberOfRows + 1; rowIndex <= numberOfRows; rowIndex++) {
        int flag = 1;
        int columnIndex = 1;
        while (columnIndex <= (numberOfRows + 1) - rowIndex) {
            cout << flag;
            if (flag) flag = 0;
            else flag = 1;
            columnIndex++;
        }
        if (columnIndex < rowIndex) {
            flag = 1;
            while (columnIndex < rowIndex) {
            cout << " ";
            columnIndex++;
            }
        }
        while (columnIndex <= numberOfRows) {
            cout << flag;
            if (flag) flag = 0;
            else flag = 1;
            columnIndex++;
        }
        cout << "\n";
    }
    return 0;
    return 0;
}