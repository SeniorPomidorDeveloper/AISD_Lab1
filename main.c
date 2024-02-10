#include <stdio.h>

#include "libs/int_matrix.h"
#include "libs/gets.h"

intLine InputIntLine();
intMatrix InputIntMatrix();
intMatrix Process(intMatrix matirx);
void PrintMatrix(intMatrix matirx);

enum PROGRAM_STATUS
{
ERROR = 1,
SUCCESSFULLY = 0
};

int main()
{
    intMatrix matrix = InputIntMatrix();
    if (!matrix.lines) {
        return ERROR;
    }
    // intMatrix newMatrix = Process(matrix);
    // if (!newMatrix.lines) {
    //     return ERROR;
    // }
    PrintMatrix(matrix);
    // PrintMatrix(newMatrix);
    FreeMatrix(&matrix);
    // FreeMatrix(&newMatrix);
    return SUCCESSFULLY;
}

intLine InputIntLine()
{
    intLine line = {0, NULL};
    size_t len;
    if (GetSize_t(&len, "Введите кол-во элементов в строке: ", StandatrCheckSize_t) == EOF) {
        return line;
    }
    line.line = (long long int *) malloc(len * sizeof(long long int));
    if (!line.line) {
        return line;
    }
    for (size_t i = 0; i < len; ++i) {
        long long int num;
        if (GetLLInt(&num, "Введите целое число: ", StandartCheckLLInt) == EOF) {
            free(line.line);
            line.line = NULL;
            return line;
        }
        line.line[i] = num; 
    }
    line.len = len;
    return line;
}

intMatrix InputIntMatrix()
{
    intMatrix matrix = {0, 0, NULL};
    size_t countLines;
    if (GetSize_t(&countLines, "Введите кол-во строк в матрице: ", StandatrCheckSize_t) == EOF) {
        return matrix;
    } 
    MatrixInit(&matrix, countLines);
    if (!matrix.lines && countLines != 0) {
        return matrix;
    } 
    for (size_t i = 0; i < countLines; ++i) {
        intLine line = InputIntLine();
        if (!line.line) {
            FreeMatrix(&matrix);
            return matrix;
        }
        if (!AddLine(&matrix, line, i)) {
            FreeMatrix(&matrix);
            return matrix;
        }
    }
    return matrix;
}
    
void PrintMatrix(intMatrix matrix)
{
    for (size_t i = 0; i < matrix.len; ++i) {
        if (matrix.lines[i].len != 0) {
            printf("%lld", matrix.lines[i].line[0]);
            for (size_t j = 1; j < matrix.lines[i].len; ++j) {
                printf(" %lld", matrix.lines[i].line[j]);
            }
        }
        printf("\n");
    }
}