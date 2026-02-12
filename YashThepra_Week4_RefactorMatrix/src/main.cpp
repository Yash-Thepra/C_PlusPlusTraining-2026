#include <iostream>

#include "input.h"
#include "matrix.h"

static void performAddition()
{
    int numberOfRows, numberOfColumns;
    while (true)
    {
        std::cout << "\nEnter Number Of Rows(single time) since dimension of both matrix are same for addition: ";
        numberOfRows = Input::getValidInteger();

        std::cout << "\nEnter Number Of columns(single time) since dimension of both matrix are same for addition: ";
        numberOfColumns = Input::getValidInteger();

        if (numberOfColumns != 0 && numberOfRows != 0)
        {
            break;
        }
        std::cout << "\nInvalid Input! Please try again.\n";
    }

    Matrix matrixFirst(numberOfColumns, numberOfRows);
    Matrix matrixSecond(numberOfColumns, numberOfRows);

    std::cout << "\nEnter values of first Matrix:\n";
    matrixFirst.fillMatrix();

    std::cout << "Enter values of second Matrix:\n";
    matrixSecond.fillMatrix();

    Matrix result = matrixFirst + matrixSecond;

    std::cout << "Result:\n";
    result.displayMatrix();
}

static void performMultiplication()
{
    int rowsMatrixFirst, columnsMatrixFirst, rowsMatrixSecond, columnsMatrixSecond;

    while (true)
    {
        std::cout << "Enter Number of rows for Matrix First: ";
        rowsMatrixFirst = Input::getValidInteger();

        std::cout << "\nEnter Number Of columns for Matrix first: ";
        columnsMatrixFirst = Input::getValidInteger();

        std::cout << "\nEnter Number of rows for Matrix Second: ";
        rowsMatrixSecond = Input::getValidInteger();

        std::cout << "\nEnter Number of Columns for Matrix Second: ";
        columnsMatrixSecond = Input::getValidInteger();

        if (columnsMatrixFirst == rowsMatrixSecond && rowsMatrixFirst != 0 && columnsMatrixFirst != 0 && rowsMatrixSecond != 0 && columnsMatrixSecond != 0)
        {
            break;
        }
        std::cout << "\nInvalid dimensions. Try again.\n";
    }

    Matrix matrixFirst(columnsMatrixFirst, rowsMatrixFirst);
    Matrix matrixSecond(columnsMatrixSecond, rowsMatrixSecond);

    std::cout << "\nEnter values of Matrix first:\n";
    matrixFirst.fillMatrix();

    std::cout << "\nEnter values of Matrix second:\n";
    matrixSecond.fillMatrix();

    Matrix result = matrixFirst * matrixSecond;

    std::cout << "\nResult:\n\n";
    result.displayMatrix();
}

int main()
{
    while (true)
    {
        std::cout << "Please follow the below instructions:\n1. Press 1 for Addition\n2. Press 2 for Multiplication\n\nEnter: ";
        Operation operationChoice = Input::getValidChoice();

        if (operationChoice == ADDITION)
        {
            performAddition();
        }
        else
        {
            performMultiplication();
        }

        std::cout << "\nPlease Note:\na. Press 1 to continue.\nb. Press 2 to exit.\n: ";
        ProgramEnd preference = Input::getValidPreference();

        if (preference == EXIT)
        {
            std::cout << "\n\nProgram Ending...\n";
            break;
        }
    }
    return 0;
}
