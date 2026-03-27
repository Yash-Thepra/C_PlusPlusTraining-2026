#include "add.h"

Matrix addTwoMatrices(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    Matrix resultantMatrix = createMatrix(firstMatrix.numberOfColumns, firstMatrix.numberOfRows);
    for (int row = 0; row < firstMatrix.numberOfRows; row++)
    {
        for (int column = 0; column < firstMatrix.numberOfColumns; column++)
        {
            resultantMatrix.values[row][column] = firstMatrix.values[row][column] + secondMatrix.values[row][column];
        }
    }
    return resultantMatrix;
}
