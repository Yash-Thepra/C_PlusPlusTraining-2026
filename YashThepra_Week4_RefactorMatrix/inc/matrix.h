#pragma once

enum Operation
{
    ADDITION = 1,
    MULTIPLICATION = 2
};

enum ProgramEnd
{
    CONTINUE = 1,
    EXIT = 2
};

class Matrix
{
private:
    int numberOfRows;
    int numberOfColumns;
    double **values;

    void allocateMemory();

    void freeMemory();

public:
    Matrix(const int &numberOfColumns, const int &numberOfRows);

    ~Matrix();

    Matrix(const Matrix &other);

    Matrix &operator=(const Matrix &other);

    Matrix(Matrix &&other) noexcept;

    Matrix &operator=(Matrix &&other) noexcept;

    void fillMatrix();

    void displayMatrix() const;

    Matrix operator+(const Matrix &secondMatrix) const;

    Matrix operator*(const Matrix &secondMatrix) const;

    int getRows() const;
    
    int getColumns() const;
};
