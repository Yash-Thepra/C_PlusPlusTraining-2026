#include "matrix.h"

Matrix createMatrix(const int numberOfRows, const int numberOfColumns)
{
    Matrix matrix;
    matrix.numberOfRows = numberOfRows;
    matrix.numberOfColumns = numberOfColumns;

    matrix.values = new double *[numberOfColumns];
    for (int index = 0; index < numberOfRows; index++)
    {
        matrix.values[index] = new double[numberOfColumns];
    }

    return matrix;
}

void freeMatrix(Matrix &matrix)
{
    for (int index = 0; index < matrix.numberOfRows; index++)
    {
        delete[] matrix.values[index];
    }
    delete[] matrix.values;

    matrix.values = nullptr;
}
