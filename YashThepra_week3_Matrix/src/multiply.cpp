#include "multiply.h"
Matrix multiplyTwoMatrices(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    Matrix resultantMatrix = createMatrix(firstMatrix.numberOfRows, secondMatrix.numberOfColumns);
    for (int rowIndex = 0; rowIndex < firstMatrix.numberOfRows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < secondMatrix.numberOfColumns; columnIndex++)
        {
            double sumOfSingleCell = 0;
            for (int index = 0; index < firstMatrix.numberOfColumns; index++)
            {
                sumOfSingleCell += firstMatrix.values[rowIndex][index] * secondMatrix.values[index][columnIndex];
            }
            resultantMatrix.values[rowIndex][columnIndex] = sumOfSingleCell;
        }
    }
    return resultantMatrix;
}
