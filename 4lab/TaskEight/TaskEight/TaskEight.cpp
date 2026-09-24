#include <iostream>

using namespace std;

void multiplyMatrixByLastColumn(int** array, int N);

int main() {
    setlocale(LC_ALL, "Russian");

    int N;

    // Ввод размера массива
    cout << "Введите размер массива (N): ";
    cin >> N;

    // Создание динамического двумерного массива NxN
    int** array = new int* [N];
    for (int i = 0; i < N; i++) {
        array[i] = new int[N];
    }

    // Заполнение массива
    cout << "Заполните массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "array[" << i << "][" << j << "] = ";
            cin >> array[i][j];
        }
    }

    // Вывод исходного массива
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Вызов функции для умножения матрицы на вектор последнего столбца
    multiplyMatrixByLastColumn(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для умножения матрицы на вектор последнего столбца
void multiplyMatrixByLastColumn(int** array, int N) {
    // Создание временного вектора для хранения элементов последнего столбца
    int* lastColumn = new int[N];

    // Заполнение вектора последнего столбца
    for (int i = 0; i < N; i++) {
        lastColumn[i] = array[i][N - 1];
    }

    // Умножаем каждую строку на элемент последнего столбца
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] *= lastColumn[i];
        }
    }

    // Вывод массива после умножения
    cout << "Массив после умножения на вектор последнего столбца:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Освобождение памяти вектора
    delete[] lastColumn;
}
