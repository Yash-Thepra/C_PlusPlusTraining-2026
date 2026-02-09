#include "multiply.h"

Matrix multiplyTwoMatrices(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    Matrix resultantMatrix = createMatrix(secondMatrix.numberOfColumns, firstMatrix.numberOfRows);
    for (int row = 0; row < firstMatrix.numberOfRows; row++)
    {
        for (int column = 0; column < secondMatrix.numberOfColumns; column++)
        {
            double sum = 0;
            for (int index = 0; index < firstMatrix.numberOfColumns; index++)
            {
                sum += firstMatrix.values[row][index] * secondMatrix.values[index][column];
            }
            resultantMatrix.values[row][column] = sum;
        }
    }
    return resultantMatrix;
}
