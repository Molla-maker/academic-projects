#include <iostream>
#include <algorithm> // Для функции sort()

using namespace std;

void sortEvenColumns(int** array, int N);

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

    // Вызов функции для сортировки чётных столбцов
    sortEvenColumns(array, N);

    // Вывод изменённого массива
    cout << "Массив после сортировки чётных столбцов по возрастанию:" << endl;
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

// Функция для сортировки чётных столбцов по возрастанию
void sortEvenColumns(int** array, int N) {
    for (int j = 1; j < N; j += 2) {  // Индексы чётных столбцов: 1, 3, 5, ...
        int* column = new int[N];      // Временный массив для хранения столбца

        // Копируем столбец в временный массив
        for (int i = 0; i < N; i++) {
            column[i] = array[i][j];
        }

        // Сортируем временный массив (столбец)
        sort(column, column + N);

        // Возвращаем отсортированный столбец обратно в массив
        for (int i = 0; i < N; i++) {
            array[i][j] = column[i];
        }

        // Освобождаем временный массив
        delete[] column;
    }
}
