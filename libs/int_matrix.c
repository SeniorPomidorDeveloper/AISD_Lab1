#include "int_matrix.h"

#include "string.h"

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

intMatrix *AddLine(intMatrix *matrix, const intLine *line, const size_t index)
{
    if (index < matrix->len) {
        *(matrix->lines + index) = *line;
        matrix->capacity++;
        return matrix;
    }
    return NULL;
}

long long int *FindMinInIntLine(const intLine *line)
{
    long long int *iter = NULL;
    if (line->len != 0) {
        iter = line->line;
        for (size_t i = 1; i < line->len; ++i) {
            if (*iter > line->line[i]) {
                iter = line->line + i;
            }
        }
    }
    return iter;
}

bool CopyIntLine(const intLine *line, intLine *newLine)
{
    newLine->len = line->len;
    newLine->line = line->line;
    if (newLine->len != 0) {
        newLine->line = (long long int *) malloc(newLine->len * sizeof(long long int));
        if (!newLine->line) {
            return false;
        }
        memcpy(newLine->line, line->line, line->len * sizeof(long long int));
    }
    return true;
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