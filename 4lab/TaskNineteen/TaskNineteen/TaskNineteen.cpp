#include <iostream>

using namespace std;

void multiplyAntiDiagonalByFirstRowAndWriteInLastColumn(int** array, int N);

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

    // Вызов функции для выполнения операции
    multiplyAntiDiagonalByFirstRowAndWriteInLastColumn(array, N);

    // Вывод изменённого массива
    cout << "Массив после умножения элементов побочной диагонали на первую строку и записи в последний столбец:" << endl;
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

// Функция для умножения побочной диагонали на первую строку и записи в последний столбец
void multiplyAntiDiagonalByFirstRowAndWriteInLastColumn(int** array, int N) {
    for (int i = 0; i < N; i++) {
        // Элемент побочной диагонали: array[i][N-1-i]
        // Умножаем его на соответствующий элемент первой строки: array[0][i]
        array[i][N - 1] = array[i][N - 1 - i] * array[0][i];
    }
}
