#include <iostream>
#include <algorithm> // Для функции sort()

using namespace std;

void sortOrReverseFirstRow(int** array, int N);

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

    // Вызов функции для сортировки или зеркалирования первой строки
    sortOrReverseFirstRow(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для сортировки или зеркалирования первой строки
void sortOrReverseFirstRow(int** array, int N) {
    // Проверка последнего элемента первой строки
    if (array[0][N - 1] > 0) {
        // Если последний элемент положителен, сортируем по возрастанию
        sort(array[0], array[0] + N);
        cout << "Первая строка отсортирована по возрастанию:" << endl;
    }
    else {
        // Если последний элемент не положителен, отзеркаливаем строку
        reverse(array[0], array[0] + N);
        cout << "Первая строка отзеркалена:" << endl;
    }

    // Вывод модифицированной матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
