#ifndef INPUT_H
#define INPUT_H
#include "matrix.h"
#include "operation.h"
double getValidDouble();
int getValidInteger();
Operation getValidChoice();
void fillMatrix(Matrix &Matrix);
#endif
