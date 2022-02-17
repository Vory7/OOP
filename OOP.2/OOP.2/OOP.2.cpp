#include <iostream>
#include <iomanip>

int** genRandMatrix(int size, int maxValue);
int** genRandMatrix2(int size, int maxValue, int* arr);
void printM(int** matrix, int size);
void printM2(int** matrix, int size, int* arr);
int* genArrayA(int size, int** matrix);
int* genArrayB(int size, int** matrix);
int* genArrayС(int size, int** matrix);
int* genArrayD(int size, int** matrix);
void printA(int* arr, int size);

int main()
{
    srand(time(NULL));
    int size = 6;
    int maxValue = 100;
    int** matrix = genRandMatrix(size, maxValue);
    printM(matrix, size);

    int* arrA = genArrayA(size, matrix);
    std::cout << "A:";
    printA(arrA, size);
    delete[] arrA;

    int* arrB = genArrayB(size, matrix);
    std::cout << "B:";
    printA(arrB, size);
    delete[] arrB;

    int* arrC = genArrayС(size, matrix);
    std::cout << "C:";
    printA(arrC, size);

    int* arrD = genArrayD(size, matrix);
    std::cout << "D:";
    printA(arrD, size);
    delete[] arrD;
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    std::cout << std::endl;

    int* arr2 = new int[size];
    int** matrix2 = genRandMatrix2(size, maxValue, arr2);
    printM2(matrix2, size, arr2);
    delete[] arr2;
    for (int i = 0; i < size; ++i) {
        delete[] matrix2[i];
    }
    delete[] matrix2;
}

int** genRandMatrix(int size, int maxValue) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) matrix[i][j] = rand() % maxValue;
    }
    return matrix;
}

int** genRandMatrix2(int size, int maxValue, int* arr) {
    int** matrix = new int* [size];
    int p;
    for (int i = 0; i < size; ++i) {
        p = (rand() % size) + 1;
        matrix[i] = new int[p];
        arr[i] = p;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < arr[i]; ++j) matrix[i][j] = rand() % maxValue;
    }
    return matrix;
}

void printM(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(3) << matrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printM2(int** matrix, int size, int* arr) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < arr[i]; ++j) {
            std::cout << std::setw(3) << matrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int* genArrayA(int size, int** matrix) {
    int p = size * size;
    int h = 0;
    int* arr = new int[p];
    for (int i = size - 1; i >= 0; --i) {
        int i1 = i;
        for (int j = 0; j < size - i; ++j) {
            arr[h] = matrix[j][i1];
            ++h;
            ++i1;
        }
    }

    for (int i = 1; i < size; ++i) {
        int i1 = i;
        for (int j = 0; j < size - i; ++j) {
            arr[h] = matrix[i1][j];
            ++h;
            ++i1;
        }
    }

    return arr;
}

int* genArrayB(int size, int** matrix) {
    int p = size * size;
    int h = 0;
    int* arr = new int[p];
    for (int i = 0; i < size; ++i) {
        int i1 = i;
        for (int j = 0; j <= i; ++j) {
            arr[h] = matrix[j][i1];
            ++h;
            --i1;
        }
    }

    for (int i = 1; i < size; ++i) {
        int i1 = i;
        for (int j = size - 1; j >= i; --j) {
            arr[h] = matrix[i1][j];
            ++h;
            ++i1;
        }
    }

    return arr;
}

int* genArrayС(int size, int** matrix) {
    int p = size * size, k = 1, n = 1, m = -1, i1, j1; // n - шаг, m - знак, k - счетчик массива, i1 и j1 - координаты в матрице
    int* arr = new int[p];
    int h = trunc(size / 2);
    if (size % 2 == 0)--h;
    i1 = h;
    j1 = h;
    arr[0] = matrix[h][h];

    for (n; n <= size; ++n) {
        m *= -1;
        if (m > 0) {
            for (int j = j1 + 1; j <= j1 + n; ++j) {
                if (j < size) {
                    arr[k] = matrix[i1][j];
                    k++;
                }
                else break;
            }
            j1 += n;
            if (j1 >= size)break;
            for (int i = i1 + 1; i <= i1 + n; ++i) {
                if (i < size) {
                    arr[k] = matrix[i][j1];
                    k++;
                }
                else break;
            }
            i1 += n;
            if (i1 >= size)break;
        }
        if (m < 0) {
            for (int j = j1 - 1; j >= j - n; --j) {
                if (j >= 0) {
                    arr[k] = matrix[i1][j];
                    k++;
                }
                else break;
            }
            j1 -= n;
            if (j1 < 0)break;
            for (int i = i1 - 1; i >= i1 - n; --i) {
                if (i >= 0) {
                    arr[k] = matrix[i][j1];
                    k++;
                }
                else break;
            }
            i1 -= n;
            if (i1 < 0)break;
        }
    }

    return arr;
}

int* genArrayD(int size, int** matrix) {
    int p = size * size;
    int* arr = new int[p];
    int k = 0;
    for (int i = 0; i < (size / 2); ++i) {
        for (int j = i; j < (size - i); ++j) {
            arr[k] = matrix[i][j];
            ++k;
        }
        for (int j = 1; j < (size - i - i); ++j) {
            arr[k] = matrix[(j + i)][(size - i) - 1];
            ++k;
        }
        for (int j = (size - 2) - i; j >= i; --j) {
            arr[k] = matrix[(size - i) - 1][(j)];
            ++k;
        }
        for (int j = ((size - i) - 2); j > i; --j) {
            arr[k] = matrix[j][i];
            ++k;
        }
    }
    if (size % 2 != 0) {
        arr[p - 1] = matrix[size / 2][size / 2];
    }
    return arr;
}



void printA(int* arr, int size) {
    for (int i = 0; i < (size * size); ++i) {
        std::cout << std::setw(3) << arr[i];
    }
    std::cout << std::endl;
}