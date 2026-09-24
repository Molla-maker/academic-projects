#include <iostream>

using namespace std;

void zeroMainDiagonalIfGreaterThanRowAverage(int** array, int N);

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

    // Вызов функции для замены элементов главной диагонали
    zeroMainDiagonalIfGreaterThanRowAverage(array, N);

    // Вывод изменённого массива
    cout << "Массив после замены элементов главной диагонали:" << endl;
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

// Функция для замены элементов главной диагонали, если они больше среднего арифметического строки
void zeroMainDiagonalIfGreaterThanRowAverage(int** array, int N) {
    for (int i = 0; i < N; i++) {
        // Вычисляем среднее арифметическое строки i
        int sum = 0;
        for (int j = 0; j < N; j++) {
            sum += array[i][j];
        }
        double rowAverage = static_cast<double>(sum) / N;

        // Проверяем элемент главной диагонали
        if (array[i][i] > rowAverage) {
            array[i][i] = 0;  // Если элемент больше среднего арифметического, записываем 0
        }
    }
}
