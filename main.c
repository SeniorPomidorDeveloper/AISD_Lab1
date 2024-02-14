#include <stdio.h>

#include "libs/int_matrix.h"
#include "libs/gets.h"
#include "libs/check.h"

bool InputIntLine(intLine *line);
bool InputIntMatrix(intMatrix *matrix);
void PrintMatrix(const intMatrix *matrix);

bool Process(const intMatrix *matrix, intMatrix *newMatrix);

enum PROGRAM_STATUS
{
ERROR = 1,
SUCCESSFULLY = 0
};

int main()
{
    intMatrix matrix;
    if (!InputIntMatrix(&matrix)) {
        return ERROR;
    }
    intMatrix newMatrix;
    if (!Process(&matrix, &newMatrix)) {
        FreeMatrix(&matrix);
        return ERROR;
    }
    printf("Исходная матрица:\n");
    PrintMatrix(&matrix);
    FreeMatrix(&matrix);
    printf("Результирующая матрица матрица:\n");
    PrintMatrix(&newMatrix);
    FreeMatrix(&newMatrix);
    return SUCCESSFULLY;
}

bool Process(const intMatrix *matrix, intMatrix *newMatrix)
{
    MatrixInit(newMatrix, matrix->len);
    if (!newMatrix->lines && matrix->len != 0) {
        printf("[ERROR] Не удалось выделить память!");
        return false;
    }
    for (size_t i = 0; i < newMatrix->len; ++i) {
        long long int *minLine = FindMinInIntLine(&(matrix->lines[i]));
        intLine line = {matrix->lines[i].len - (minLine - matrix->lines[i].line), minLine};
        intLine newLine;
        if (!CopyIntLine(&line, &newLine)) {
            printf("[ERROR] Не удалось выделить память!");
            FreeMatrix(newMatrix);
            return false;
        }
        if (!AddLine(newMatrix, &newLine, i)) {
            printf("[ERROR] Не удалось добавить новую строку!");
            FreeMatrix(newMatrix);
            return false;
        }
    }
    return true;
}

bool InputIntLine(intLine *line)
{
    long long int llilen;
    if (GetLLInt(&llilen, "Введите кол-во элементов в строке: ", CheckLLIntPol) == EOF) {
        return false;
    }
    size_t len = (size_t) llilen;
    line->line = (long long int *) malloc(len * sizeof(long long int));
    if (!line->line) {
        printf("[ERROR] Не удалось выделить память!");
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        long long int num;
        if (GetLLInt(&num, "Введите целое число: ", StandartCheckLLInt) == EOF) {
            free(line->line);
            line->line = NULL;
            return false;
        }
        line->line[i] = num; 
    }
    line->len = len;
    return true;
}

bool InputIntMatrix(intMatrix *matrix)
{
    long long int llicountLines;
    if (GetLLInt(&llicountLines, "Введите кол-во строк в матрице: ", CheckLLIntPol) == EOF) {
        return false;
    } 
    size_t countLines = (size_t) llicountLines;
    MatrixInit(matrix, countLines);
    if (!matrix->lines && countLines != 0) {
        printf("[ERROR] Не удалось выделить память!");
        return false;
    } 
    for (size_t i = 0; i < countLines; ++i) {
        intLine line = {0, NULL};
        if (!InputIntLine(&line)) {
            FreeMatrix(matrix);
            return false;
        }
        if (!AddLine(matrix, &line, i)) {
            printf("[ERROR] Не удалось добавить новую строку!");
            FreeMatrix(matrix);
            return false;
        }
    }
    return true;
}
    
void PrintMatrix(const intMatrix *matrix)
{
    for (size_t i = 0; i < matrix->len; ++i) {
        if (matrix->lines[i].len != 0) {
            printf("\t%lld", matrix->lines[i].line[0]);
            for (size_t j = 1; j < matrix->lines[i].len; ++j) {
                printf(" %lld", matrix->lines[i].line[j]);
            }
        }
        printf("\n");
    }
}