#ifndef MATRIX_H
#define MATRIX_H
struct Matrix
{
    int numberOfRows;
    int numberOfColumns;
    double **values;
};
Matrix createMatrix(const int numberOfRows, const int numberOfColumns);
void freeMatrix(Matrix &matrix);
#endif
