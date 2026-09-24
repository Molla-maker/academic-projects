#include <iostream>

using namespace std;

void sumRowsWithNext(int** array, int N);

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

    // Вызов функции для замены строк путём сложения со следующей
    sumRowsWithNext(array, N);

    // Вывод изменённого массива
    cout << "Массив после замены строк путём сложения со следующей строкой:" << endl;
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

// Функция для замены строк путём сложения со следующей
void sumRowsWithNext(int** array, int N) {
    for (int i = 0; i < N - 1; i++) {  // Перебираем все строки, кроме последней
        for (int j = 0; j < N; j++) {
            // Складываем строку с следующей
            array[i][j] += array[i + 1][j];
        }
    }
}
