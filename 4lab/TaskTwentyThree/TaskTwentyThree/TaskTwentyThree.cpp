#include <iostream>

using namespace std;

// Прототип функции
void setFirstElementToZeroIfRowAverageLessThanN(int** array, int N);

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

    // Вызов функции для замены первого элемента строки на 0, если среднее арифметическое строки меньше N
    setFirstElementToZeroIfRowAverageLessThanN(array, N);

    // Вывод изменённого массива
    cout << "Массив после выполнения операции:" << endl;
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

// Функция для записи 0 в первый элемент строки, если среднее арифметическое её элементов меньше N
void setFirstElementToZeroIfRowAverageLessThanN(int** array, int N) {
    for (int i = 0; i < N; i++) {
        // Вычисляем среднее арифметическое строки
        int sum = 0;
        for (int j = 0; j < N; j++) {
            sum += array[i][j];
        }
        double rowAverage = static_cast<double>(sum) / N;

        // Если среднее арифметическое строки меньше N, заменяем первый элемент на 0
        if (rowAverage < N) {
            array[i][0] = 0;
        }
    }
}
