#include <iostream>
#include <cstdlib>
#include <iomanip>

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int* WorkWithMatrix(int**& matrix, int& rows, int& cols, int A, int B, int C, int D) {
    int nrows = 2 + A;
    int ncols = 2 + B;

    int sA = matrix[0][0];
    int sB = matrix[0][1];
    int sC = matrix[1][0];
    int sD = matrix[1][1];

    matrix = (int**)std::realloc(matrix, nrows * sizeof(int*));

    for (int i = 0; i < nrows; i++) {
        if (i < rows) {
            matrix[i] = (int*)std::realloc(matrix[i], ncols * sizeof(int));
            for (int j = cols; j < ncols; j++) {
                matrix[i][j] = 0;
            }
        }
        else {
            matrix[i] = (int*)std::calloc(ncols, sizeof(int));
        }
    }

    rows = nrows;
    cols = ncols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * C + j * D;
        }
    }

    matrix[A][B] = sA;
    matrix[A][B + 1] = sB;
    matrix[A + 1][B] = sC;
    matrix[A + 1][B + 1] = sD;

    int zeroCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zeroCount++;
                break;
            }
        }
    }

    int* result = (int*)std::malloc((zeroCount + 1) * sizeof(int));
    result[0] = zeroCount;

    int resultIndex = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                result[resultIndex++] = i;
                break;
            }
        }
    }

    return result;
}

void removeRows(int**& matrix, int& rows, int& cols, int* rowsToRemove) {
    int removeCount = rowsToRemove[0];
    if (removeCount == 0) return;

    for (int k = 1; k <= removeCount; k++) {
        int rowToRemove = rowsToRemove[k];
        if (rowToRemove < rows && matrix[rowToRemove] != NULL) {
            std::free(matrix[rowToRemove]);
            matrix[rowToRemove] = NULL;
        }
    }

    int newIndex = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            if (newIndex != i) {
                matrix[newIndex] = matrix[i];
                matrix[i] = NULL;
            }
            newIndex++;
        }
    }

    if (newIndex > 0) {
        int** temp = (int**)std::realloc(matrix, newIndex * sizeof(int*));
        if (temp != NULL) {
            matrix = temp;
        }
        rows = newIndex;
    }
    else {
        std::free(matrix);
        matrix = NULL;
        rows = 0;
    }
}

void Item2() {
    int a;
    int b;
    std::cin >> a >> b;

    int* pxa = &a;
    int* pxb = &b;
    *pxa = *pxa * 2;

    int* temp = new int;
    *temp = *pxa;
    *pxa = *pxb;
    *pxb = *temp;

    delete temp;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int A;
    int B;
    int C;
    int D;
    do {
        std::cin >> A;
        if (A < 0) {
            std::cout << "А должен быть неотрицательным, повторите ввод"  << std::endl;
        }
    } while (A < 0);

    do {
        std::cin >> B;
        if (B < 0) {
            std::cout << "В должен быть неотрицательным, повторите ввод" << std::endl;
        }
    } while (B < 0);

    std::cin >> C;
    std::cin >> D;

    int rows = 2;
    int cols = 2;

    int** matrix = (int**)std::malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)std::malloc(cols * sizeof(int));
    }

    matrix[0][0] = A;
    matrix[0][1] = B;
    matrix[1][0] = C;
    matrix[1][1] = D;

    std::cout << "Исходная матрица 2x2:" << std::endl;
    printMatrix(matrix, rows, cols);

    int* zeroRows = WorkWithMatrix(matrix, rows, cols, A, B, C, D);

    std::cout << "Матрица после увеличения и заполнения" << std::endl;
    printMatrix(matrix, rows, cols);

    removeRows(matrix, rows, cols, zeroRows);

    std::cout << "Матрица после удаления строк с нулями" << std::endl;
    printMatrix(matrix, rows, cols);

    std::free(zeroRows);

    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i] != NULL) {
                std::free(matrix[i]);
            }
        }
        std::free(matrix);
    }

    Item2();
    
    return 0;
}