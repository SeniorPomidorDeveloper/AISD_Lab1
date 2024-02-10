#include "int_matrix.h"

void MatrixInit(intMatrix *matrix, const size_t countLines)
{
    if (countLines != 0) {
        matrix->lines = (intLine *) malloc(countLines * sizeof(intLine));
        if (matrix->lines) {
            matrix->len = countLines;
            matrix->capacity = 0;
        }
    }
}

intMatrix *AddLine(intMatrix *matrix, intLine line, const size_t index)
{
    if (index < matrix->len) {
        *(matrix->lines + index) = line;
        matrix->capacity++;
        return matrix;
    }
    return NULL;
}

void FreeMatrix(intMatrix *matrix)
{
    for (size_t i = 0; i < matrix->capacity; ++i) {
        free(matrix->lines[i].line);
    }
    free(matrix->lines);
    matrix->lines = NULL;
    matrix->len = 0;
    matrix->capacity = 0;
}