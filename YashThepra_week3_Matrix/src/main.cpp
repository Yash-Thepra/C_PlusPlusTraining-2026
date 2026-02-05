#include <iostream>
#include "add.h"
#include "multiply.h"
#include "display.h"
#include "operation.h"
#include "input.h"
#include "matrix.h"

int main()
{
    std::cout << "Please follow the below instructions:\n1. Press 1 for Addition\n2. Press 2 for Multiplication\nEnter: ";
    Operation operationChoice = getValidChoice();

    if (operationChoice == ADDITION )
    {
        int numberOfRows, numberOfColumns;
        std::cout << "\nEnter Number Of Rows(single time) since dimension of both matrix are same for addition: ";
        numberOfRows = getValidInteger();
        std::cout << "\nEnter Number Of columns(single time) since dimension of both matrix are same for addition: ";
        numberOfColumns = getValidInteger();
        Matrix matrixFirst = createMatrix(numberOfRows, numberOfColumns);
        Matrix matrixSecond = createMatrix(numberOfRows, numberOfColumns);
        std::cout << "\nEnter values of first Matrix:\n";
        fillMatrix(matrixFirst);
        std::cout << "Enter values of second Matrix:\n";
        fillMatrix(matrixSecond);
        Matrix result = addTwoMatrices(matrixFirst, matrixSecond);
        std::cout << "Result: ";
        displayMatrix(result);
        freeMatrix(matrixFirst);
        freeMatrix(matrixSecond);
        freeMatrix(result);
    }
    else if (operationChoice == MULTIPLICATION)
    {
        int numberOfRowsMatrixFirst, numberOfColumnsMatrixFirst, numberOfRowsMatrixSecond, numberOfColumnsMatrixSecond;
        while (true)
        {
            std::cout << "Enter Number of rows for Matrix First: ";
            numberOfRowsMatrixFirst = getValidInteger();
            std::cout << "\nEnter Number Of columns for Matrix second: ";
            numberOfColumnsMatrixFirst = getValidInteger();
            std::cout << "\nEnter Number of rows for Matrix Second: ";
            numberOfRowsMatrixSecond = getValidInteger();
            std::cout << "\nEnter Number of Columns for Matrix Second: ";
            numberOfColumnsMatrixSecond = getValidInteger();
            if (numberOfColumnsMatrixFirst == numberOfRowsMatrixSecond)
            {
                break;
            }
            std::cout << "\nInvalid dimensions. Try again.\n";
        }

        Matrix matrixFirst = createMatrix(numberOfRowsMatrixFirst, numberOfColumnsMatrixFirst);
        Matrix matrixSecond = createMatrix(numberOfRowsMatrixSecond, numberOfColumnsMatrixSecond);
        std::cout << "\nEnter values of Matrix first:\n";
        fillMatrix(matrixFirst);
        std::cout << "\nEnter values of Matrix second:\n";
        fillMatrix(matrixSecond);
        Matrix resultantMatrix = multiplyTwoMatrices(matrixFirst, matrixSecond);
        std::cout << "Result: ";
        displayMatrix(resultantMatrix);
        freeMatrix(matrixFirst);
        freeMatrix(matrixSecond);
        freeMatrix(resultantMatrix);
    }
    return 0;
}
