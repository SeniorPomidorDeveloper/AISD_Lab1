#ifndef INT_MATRIX_H
#define INT_MATRIX_H

#include "stddef.h"
#include "stdlib.h"
#include "stdbool.h"

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
intMatrix *AddLine(intMatrix *matrix, const intLine line, const size_t index);
long long int *FindMinInIntLine(const intLine line);
intLine CopyIntLine(const intLine line);
void FreeMatrix(intMatrix *matrix);

#endif