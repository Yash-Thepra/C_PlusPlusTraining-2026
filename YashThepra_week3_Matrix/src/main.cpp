#include <iostream>

#include "add.h"
#include "multiply.h"
#include "display.h"
#include "input.h"
#include "matrix.h"

int main()
{
    while (true)
    {
        std::cout << "Please follow the below instructions:\n1. Press 1 for Addition\n2. Press 2 for Multiplication\n\nEnter: ";
        Operation operationChoice = getValidChoice();

        if (operationChoice == ADDITION)
        {
            int numberOfRows, numberOfColumns;
            while (true)
            {
                std::cout << "\nEnter Number Of Rows(single time) since dimension of both matrix are same for addition: ";
                numberOfRows = getValidInteger();

                std::cout << "\nEnter Number Of columns(single time) since dimension of both matrix are same for addition: ";
                numberOfColumns = getValidInteger();

                if (numberOfColumns != 0 && numberOfRows)
                {
                    break;
                }
                std::cout << "\nInvalid Input! Please try again.\n";
            }
            Matrix matrixFirst = createMatrix(numberOfColumns, numberOfRows);
            Matrix matrixSecond = createMatrix(numberOfColumns, numberOfRows);
            std::cout << "\nEnter values of first Matrix:\n";
            fillMatrix(matrixFirst);
            std::cout << "Enter values of second Matrix:\n";
            fillMatrix(matrixSecond);
            Matrix result = addTwoMatrices(matrixFirst, matrixSecond);
            std::cout << "Result:\n";
            displayMatrix(result);
            freeMatrix(matrixFirst);
            freeMatrix(matrixSecond);
            freeMatrix(result);
        }
        else
        {
            int numberOfRowsMatrixFirst, numberOfColumnsMatrixFirst, numberOfRowsMatrixSecond, numberOfColumnsMatrixSecond;
            while (true)
            {
                std::cout << "Enter Number of rows for Matrix First: ";
                numberOfRowsMatrixFirst = getValidInteger();

                std::cout << "\nEnter Number Of columns for Matrix first: ";
                numberOfColumnsMatrixFirst = getValidInteger();

                std::cout << "\nEnter Number of rows for Matrix Second: ";
                numberOfRowsMatrixSecond = getValidInteger();

                std::cout << "\nEnter Number of Columns for Matrix Second: ";
                numberOfColumnsMatrixSecond = getValidInteger();

                if (numberOfColumnsMatrixFirst == numberOfRowsMatrixSecond && numberOfRowsMatrixFirst != 0 && numberOfColumnsMatrixFirst != 0 && numberOfRowsMatrixSecond != 0 && numberOfColumnsMatrixSecond != 0)
                {
                    break;
                }
                std::cout << "\nInvalid dimensions. Try again.\n";
            }

            Matrix matrixFirst = createMatrix(numberOfColumnsMatrixFirst, numberOfRowsMatrixFirst);
            Matrix matrixSecond = createMatrix(numberOfColumnsMatrixSecond, numberOfRowsMatrixSecond);
            std::cout << "\nEnter values of Matrix first:\n";
            fillMatrix(matrixFirst);
            std::cout << "\nEnter values of Matrix second:\n";
            fillMatrix(matrixSecond);
            Matrix resultantMatrix = multiplyTwoMatrices(matrixFirst, matrixSecond);
            std::cout << "\nResult:\n\n";
            displayMatrix(resultantMatrix);
            freeMatrix(matrixFirst);
            freeMatrix(matrixSecond);
            freeMatrix(resultantMatrix);
        }


        std::cout << "\nPlease Note:\na. Press 1 to continue.\nb. Press 2 to exit.\n: ";
        ProgramEnd preference = getValidPreference();
        if (preference == EXIT)
        {
            std::cout << "\n\nProgram Ending...\n";
            break;
        }
    }
    return 0;
}
