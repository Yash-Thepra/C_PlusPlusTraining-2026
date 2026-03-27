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

struct Matrix
{
    int numberOfRows;
    int numberOfColumns;
    double **values;
};

Matrix createMatrix(const int& numberOfColumns, const int& numberOfRows);
void freeMatrix(Matrix &matrix);
