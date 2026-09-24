#include <iostream>

using namespace std;

void calculateAverageOfPositiveEvenInDiagonal(int** array, int N);

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

    // Вызов функции для вычисления среднего значения четных положительных элементов главной диагонали
    calculateAverageOfPositiveEvenInDiagonal(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для вычисления среднего значения четных положительных элементов главной диагонали
void calculateAverageOfPositiveEvenInDiagonal(int** array, int N) {
    int sum = 0;
    int count = 0;

    // Проходим по главной диагонали (где i == j)
    for (int i = 0; i < N; i++) {
        if (array[i][i] > 0 && array[i][i] % 2 == 0) {  // Проверяем, что элемент положительный и четный
            sum += array[i][i];
            count++;
        }
    }

    // Если есть хотя бы один четный положительный элемент, вычисляем среднее
    if (count > 0) {
        double average = static_cast<double>(sum) / count;
        cout << "Среднее значение четных положительных элементов главной диагонали: " << average << endl;
    }
    else {
        cout << "Нет четных положительных элементов на главной диагонали." << endl;
    }
}
