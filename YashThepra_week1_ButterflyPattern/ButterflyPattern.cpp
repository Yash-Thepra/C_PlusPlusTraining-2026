#include <iostream>

using std::cout;
using std::cin;

int main() {
    int numberOfRows;
    cout << "Enter the size (Row length should be odd) of the pattern: ";
    cin >> numberOfRows;
    cout << "\n";
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
}