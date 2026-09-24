#include <iostream>

using namespace std;

void addDiagonalToEvenElementsInLastColumn(int** array, int N);

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

    // Вызов функции для изменения последнего столбца
    addDiagonalToEvenElementsInLastColumn(array, N);

    // Вывод изменённого массива
    cout << "Массив после прибавления элементов главной диагонали к чётным элементам последнего столбца:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для добавления элементов главной диагонали к чётным элементам последнего столбца
void addDiagonalToEvenElementsInLastColumn(int** array, int N) {
    for (int i = 0; i < N; i++) {
        // Проверка, является ли элемент в последнем столбце чётным
        if (array[i][N - 1] % 2 == 0) {
            // Прибавляем к элементу главной диагонали в той же строке
            array[i][N - 1] += array[i][i];
        }
    }
}
