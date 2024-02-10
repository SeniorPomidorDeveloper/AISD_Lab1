#ifndef MATRIX_H
#define MATRIX_H

#include "stddef.h"
#include "stdlib.h"

typedef struct intLine
{
    size_t len;
    long long int *line;
} intLine;


typedef struct intMatrix
{
    size_t len;
    size_t capacity;
    intLine *lines;
} intMatrix;

void MatrixInit(intMatrix *matrix, const size_t countLines);
intMatrix *AddLine(intMatrix *matrix, intLine line, const size_t index);
void FreeMatrix(intMatrix *matrix);

#endif