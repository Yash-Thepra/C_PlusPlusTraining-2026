#include <iostream>

#include "constant.h"
#include "Input.h"
#include "Matrix.h"

void displayMatrix(const Matrix &matrix)
{
    for (int row = 0; row < matrix.getMatrixRows(); row++)
    {
        for (int column = 0; column < matrix.getMatrixColumns(); column++)
        {
            std::cout << "Value(" << row << "," << column << "): " << matrix.getMatrixValue(row, column) << "    ";
        }
        std::cout << "\n";
    }
}

void performAddition()
{
    int numberOfRows, numberOfColumns;
    while (true)
    {
        std::cout << "\nEnter Number Of Rows(single time) since dimension of both matrix are same for addition: ";
        numberOfRows = Input::readValidInteger();

        if (numberOfRows != 0)
        {
            std::cout << "\nEnter Number Of columns(single time) since dimension of both matrix are same for addition: ";
            numberOfColumns = Input::readValidInteger();
        }
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
    displayMatrix(result);
}

void performMultiplication()
{
    int rowsMatrixFirst, columnsMatrixFirst, rowsMatrixSecond, columnsMatrixSecond;
    while (true)
    {
        std::cout << "Enter Number of rows for Matrix First: ";
        rowsMatrixFirst = Input::readValidInteger();

        if (rowsMatrixFirst != 0)
        {
            std::cout << "\nEnter Number Of columns for Matrix first: ";
            columnsMatrixFirst = Input::readValidInteger();
        }
        if (rowsMatrixFirst != 0 && columnsMatrixFirst != 0)
        {
            break;
        }
        std::cout << "\nInvalid dimensions. Try again.\n";
    }
    while (true)
    {
        std::cout << "\nEnter Number of rows for Matrix Second: ";
        rowsMatrixSecond = Input::readValidInteger();

        if (rowsMatrixSecond != 0)
        {
            std::cout << "\nEnter Number of Columns for Matrix Second: ";
            columnsMatrixSecond = Input::readValidInteger();
        }
        if (rowsMatrixSecond != 0 && columnsMatrixSecond != 0 && columnsMatrixFirst == rowsMatrixSecond)
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
    displayMatrix(result);
}

int main()
{
    std::cout << "\nPlease Note:\na. Press " << Constant::CONTINUE_WITH_PROGRAM << " to continue with Program.\nb. Press "<< Constant::END_PROGRAM << " to exit.\n: ";
    bool programPreference = Input::readValidPreference();
    if (programPreference)
    {
        while (true)
        {
            std::cout << "Please follow the below instructions:\n1. Press " << Constant::ADD_OPERATION << " for Addition\n2. Press " << Constant::MULTIPLY_OPERATION << " for Multiplication\n\nEnter: ";
            Operation operationChoice = Input::readValidChoice();
            if (operationChoice == ADDITION)
            {
                performAddition();
            }
            else
            {
                performMultiplication();
            }
            std::cout << "\nPlease Note:\na. Press " << Constant::CONTINUE_WITH_PROGRAM << " to continue with Program.\nb. Press "<< Constant::END_PROGRAM << " to exit.\n: ";
            programPreference = Input::readValidPreference();
            if (!programPreference)
            {
                break;
            }
        }
    }
    std::cout << "\n\nProgram Ending...\n";
    return 0;
}
