#include <iostream>

int* genRandArray(int size, int maxValue);
void print(int* arr);

int** genRandMatrix(int size, int maxValue);
void printM(int** matrix);


int main() {

    srand(time(NULL));

    int size = (rand() % 6) + 5;
    int maxValue = 100;
    int* arr = genRandArray(size, maxValue);
    print(arr);
    delete[] arr; //очистка выделенной памяти
    
    int sizeM = (rand() % 6) + 5;
    int maxValueM = 100;
    int** matrix = genRandMatrix(sizeM, maxValueM);
    printM(matrix);
    for (int i = 0; i <= sizeM; i++) delete[] matrix[i]; //очистка памяти
    delete[] matrix;
}

int* genRandArray(int size, int maxValue) {

    int* arr = new int[size + 1]{ size };

    for (int i = 1; i <= size; ++i) {
        arr[i] = rand() % maxValue;
    }

    return arr;
}

void print(int* arr) {

    std::cout << arr[0] << ": ";

    for (int i = 1; i <= arr[0]; ++i) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl << std::endl;
}

int** genRandMatrix(int size, int maxValue) {
    int** matrix = new int*[size + 1];
    for (int i = 0; i <= size; ++i) {
        if (i == 0) {
            matrix[i] = new int[1];
            matrix[0][0] = size;
        }
        else {
            int r = rand() % 10 + 1;
            matrix[i] = new int[r + 1];
            matrix[i][0] = r;
        }
    }
    for (int i = 1; i <= size; ++i) {
        for (int j = 1; j <= matrix[i][0]; ++j) {
            matrix[i][j] = rand() % maxValue;
        }
    }
    return matrix;
}

void printM(int** matrix) {
    std::cout << matrix[0][0] << std::endl;
    for (int i = 1; i <= matrix[0][0]; ++i) {
        std::cout << matrix[i][0] << ": ";
        for (int j = 1; j <= matrix[i][0]; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}