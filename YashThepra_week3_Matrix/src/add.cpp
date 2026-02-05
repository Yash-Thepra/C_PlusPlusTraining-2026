#include "add.h"
Matrix addTwoMatrices(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    Matrix resultantMatrix = createMatrix(firstMatrix.numberOfRows, firstMatrix.numberOfColumns);
    for (int rowIndex = 0; rowIndex < firstMatrix.numberOfRows; rowIndex++)
        for (int columnIndex = 0; columnIndex < firstMatrix.numberOfColumns; columnIndex++)
        {
            resultantMatrix.values[rowIndex][columnIndex] = firstMatrix.values[rowIndex][columnIndex] + secondMatrix.values[rowIndex][columnIndex];
        }
    return resultantMatrix;
}
