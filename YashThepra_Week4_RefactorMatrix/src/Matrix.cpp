#include <iostream>

#include "Input.h"
#include "Matrix.h"

void Matrix::allocateMemory()
{
    values = new double *[numberOfRows];
    for (int index = 0; index < numberOfRows; index++)
    {
        values[index] = new double[numberOfColumns];
    }
}

void Matrix::freeMemory()
{
    for (int index = 0; index < numberOfRows; index++)
    {
        delete[] values[index];
    }
    delete[] values;
    values = nullptr;
}

Matrix::Matrix(const int &numberOfColumns, const int &numberOfRows)
    : numberOfRows(numberOfRows), numberOfColumns(numberOfColumns)
{
    allocateMemory();
}

Matrix::~Matrix()
{
    freeMemory();
}

Matrix::Matrix(const Matrix &other)
    : numberOfRows(other.numberOfRows), numberOfColumns(other.numberOfColumns)
{
    allocateMemory();
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < numberOfColumns; column++)
        {
            values[row][column] = other.values[row][column];
        }
    }
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        freeMemory();
        numberOfRows = other.numberOfRows;
        numberOfColumns = other.numberOfColumns;
        allocateMemory();
        for (int row = 0; row < numberOfRows; row++)
        {
            for (int column = 0; column < numberOfColumns; column++)
            {
                values[row][column] = other.values[row][column];
            }
        }
    }
    return *this;
}

void Matrix::fillMatrix()
{
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < numberOfColumns; column++)
        {
            std::cout << "\nEnter Value for cell(" << row << "," << column << "): ";
            values[row][column] = Input::readValidDouble();
        }
    }
}

Matrix Matrix::operator+(const Matrix &secondMatrix) const
{
    Matrix resultantMatrix(numberOfColumns, numberOfRows);
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < numberOfColumns; column++)
        {
            resultantMatrix.values[row][column] = values[row][column] + secondMatrix.values[row][column];
        }
    }
    return resultantMatrix;
}

Matrix Matrix::operator*(const Matrix &secondMatrix) const
{
    Matrix resultantMatrix(secondMatrix.numberOfColumns, numberOfRows);
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < secondMatrix.numberOfColumns; column++)
        {
            double sum = 0;
            for (int index = 0; index < numberOfColumns; index++)
            {
                sum += values[row][index] * secondMatrix.values[index][column];
            }
            resultantMatrix.values[row][column] = sum;
        }
    }
    return resultantMatrix;
}

int Matrix::getMatrixColumns() const
{
    return numberOfColumns;
}

int Matrix::getMatrixRows() const
{
    return numberOfRows;
}

double Matrix::getMatrixValue(const int& rowIndex, const int& columnIndex) const
{
    return values[rowIndex][columnIndex];
}
