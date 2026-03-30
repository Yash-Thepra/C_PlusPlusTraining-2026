#pragma once

class Matrix
{
private:
    int numberOfColumns;
    int numberOfRows;
    double **values;

    void allocateMemory();

    void freeMemory();

public:
    Matrix(const int &numberOfColumns, const int &numberOfRows);

    ~Matrix();

    Matrix(const Matrix &other);

    Matrix &operator=(const Matrix &other);
    
    void fillMatrix();

    Matrix operator+(const Matrix &secondMatrix) const;

    Matrix operator*(const Matrix &secondMatrix) const;

    int getMatrixColumns() const;

    int getMatrixRows() const;

    double getMatrixValue(const int& rowIndex, const int& columnIndex) const;
};
