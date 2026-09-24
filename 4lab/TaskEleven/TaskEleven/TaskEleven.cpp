#include <iostream>
#include <algorithm> // Для функции max()

using namespace std;

void addFirstColumnWithMaxRow(int** array, int N);

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

    // Вызов функции для сложения первого столбца со строкой, содержащей максимальный элемент
    addFirstColumnWithMaxRow(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для сложения первого столбца со строкой, содержащей максимальный элемент
void addFirstColumnWithMaxRow(int** array, int N) {
    int maxElement = array[0][0];
    int maxRow = 0;

    // Находим строку, содержащую максимальный элемент
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (array[i][j] > maxElement) {
                maxElement = array[i][j];
                maxRow = i;
            }
        }
    }

    // Сложение первого столбца со строкой, содержащей максимальный элемент
    for (int i = 0; i < N; i++) {
        array[i][0] += array[maxRow][i];
    }

    // Вывод изменённой матрицы
    cout << "Массив после сложения первого столбца со строкой, содержащей максимальный элемент:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
