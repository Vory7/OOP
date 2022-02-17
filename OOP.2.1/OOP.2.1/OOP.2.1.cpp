#include <iostream>
#include <time.h>
#include <math.h>

int A(int* D, int** arr, int s) {
    int x = 0, y = 0;
    int l = 0, j = 0;

    for (int i = 1; i < s + 1; ++i) {
        while (j != i) {
            x += j;
            y = y + ((s - i) + j);
            D[l] = arr[x][y];
            ++l;
            ++j;
            x = 0;
            y = 0;
        }
        j = 0;
    }

    x = 0, y = 0, j = 0;

    for (int i = s - 1; i >= 0; --i) {
        while (j != i) {
            x = x + ((s - i) + j);
            y += j;
            D[l] = arr[x][y];
            ++l;
            ++j;
            x = 0;
            y = 0;
        }
        j = 0;
    }
    return D, arr, s;
}

int B(int* D, int** arr, int s) {
    int x = 0, y = 0;
    int l = 0, j = 0;
    for (int i = 0; i < s; ++i) {
        while (j != i + 1) {
            x += j;
            y = y + (i - j);
            D[l] = arr[x][y];
            ++l;
            ++j;
            x = 0;
            y = 0;
        }
        j = 0;
    }

    x = 0, y = 0, j = 0;

    for (int i = s - 1; i > 0; --i) {
        while (j != i) {
            x = (s - i) + j;
            y = (s - 1) - j;
            D[l] = arr[x][y];
            ++l;
            ++j;
            x = 0;
            y = 0;
        }
        j = 0;
    }

    return D, arr, s;
}

int C(int* D, int** arr, int s) {
    int k = 1, n = 1, m = -1, i1, j1; // n - шаг, m - знак, k - счетчик массива, i1 и j1 - координаты в матрице
    int h = trunc(s / 2);
    if (s % 2 == 0)--h;
    i1 = h;
    j1 = h;
    D[0] = arr[h][h];

    for (n; n <= s; ++n) {
        m *= -1;
        if (m > 0) {
            for (int j = j1 + 1; j <= j1 + n; ++j) {
                if (j < s) {
                    D[k] = arr[i1][j];
                    k++;
                }
                else break;
            }
            j1 += n;
            if (j1 >= s) break;
            for (int i = i1 + 1; i <= i1 + n; ++i) {
                if (i < s) {
                    D[k] = arr[i][j1];
                    k++;
                }
                else break;
            }
            i1 += n;
            if (i1 >= s) break;
        }
        if (m < 0) {
            for (int j = j1 - 1; j >= j - n; --j) {
                if (j >= 0) {
                    D[k] = arr[i1][j];
                    k++;
                }
                else break;
            }
            j1 -= n;
            if (j1 < 0) break;
            for (int i = i1 - 1; i >= i1 - n; --i) {
                if (i >= 0) {
                    D[k] = arr[i][j1];
                    k++;
                }
                else break;
            }
            i1 -= n;
            if (i1 < 0) break;
        }
    }
    return D, arr, s;
}

int d(int* D, int** arr, int s) {
    int l = 0;
    if (s % 2 != 0) {
        D[(s * s) - 1] = arr[(s / 2)][(s / 2)];// если N - нечетное, то заполняем последний элемент массива D центральным элементом матрицы
    }
    for (int i = 0; i < (s / 2); ++i) {
        for (int j = i; j < (s - i); ++j) {   // (s - i) - чтоб с каждым разом сторона становилась меньше
            D[l] = arr[i][j];
            ++l;
        }
        for (int j = 1; j < (s - i - i); ++j) { // начинаем с первого эл. так-как нулевой уже записан
            D[l] = arr[(j + i)][(s - i) - 1];   // (s - i) - 1 - отнимаем 1 чтоб не выходило за рамки массива
            ++l;
        }
        for (int j = (s - 2) - i; j >= i; --j) {  // (s - 2) - i - отнимаем 1 чтоб не выходило за рамки массива и еще одну 1
            D[l] = arr[(s - i) - 1][(j)];          // предыдущий элемент уже заполнен.
            ++l;
        }
        for (int j = ((s - i) - 2); j > i; --j) {
            D[l] = arr[j][i];
            ++l;
        }
    }
    return D, arr, s;
}

int main()
{
    srand(time(NULL));
    int s = 50;
    int** arr = new int* [s];
    for (int i = 0; i < s; ++i)
    {
        arr[i] = new int[s];
    }

    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < s; ++j)
        {
            arr[i][j] = rand() % 10;
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << s << std::endl;

    int* D = new int[s * s];

    A(D, arr, s);
    std::cout << "a: ";

    for (int i = 0; i < s * s; ++i) {
        std::cout << D[i] << " ";
    }

    B(D, arr, s);
    std::cout << std::endl;
    std::cout << "b: ";

    for (int i = 0; i < s * s; ++i) {
        std::cout << D[i] << " ";
    }

    C(D, arr, s);
    std::cout << std::endl;
    std::cout << "c: ";

    for (int i = 0; i < s * s; ++i) {
        std::cout << D[i] << " ";
    }

    d(D, arr, s);
    std::cout << std::endl;
    std::cout << "d: ";

    for (int i = 0; i < s * s; ++i) {
        std::cout << D[i] << " ";
    }

    /*for (int i = 0; i < s; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] D;*/
    return 0;
}