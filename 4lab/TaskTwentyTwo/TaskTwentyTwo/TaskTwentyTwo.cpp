#include <iostream>

using namespace std;

void reflectMatrixAcrossAntiDiagonal(int** array, int N);

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

    // Вызов функции для отражения матрицы относительно побочной диагонали
    reflectMatrixAcrossAntiDiagonal(array, N);

    // Вывод изменённого массива
    cout << "Массив после отражения относительно побочной диагонали:" << endl;
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

// Функция для отражения матрицы относительно побочной диагонали
void reflectMatrixAcrossAntiDiagonal(int** array, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {  // Начинаем с j = i + 1, чтобы не менять элементы дважды
            // Меняем местами элементы array[i][j] и array[j][i]
            int temp = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = temp;
        }
    }
}
