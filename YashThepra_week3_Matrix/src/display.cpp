#include <iostream>

#include "display.h"

void displayMatrix(const Matrix &matrix)
{
    for (int row = 0; row < matrix.numberOfRows; row++)
    {
        for (int column = 0; column < matrix.numberOfColumns; column++)
        {
            std::cout << "Result(" << row << "," << column << "): " << matrix.values[row][column] << "    ";
        }
        std::cout << "\n";
    }
}
