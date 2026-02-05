#include <iostream>
#include "display.h"
void displayMatrix(const Matrix &matrix)
{
    for (int rowIndex = 0; rowIndex < matrix.numberOfRows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrix.numberOfColumns; columnIndex++)
        {
            std::cout << matrix.values[rowIndex][columnIndex] << " ";
        }
        std::cout << "\n";
    }
}
