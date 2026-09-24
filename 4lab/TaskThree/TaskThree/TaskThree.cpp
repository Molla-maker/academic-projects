#include <iostream>
#include <algorithm> // Для функции sort()

using namespace std;

void sortLastRow(int** array, int N);

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

    // Вывод массива до сортировки
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Вызов функции для сортировки последней строки
    sortLastRow(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для сортировки последней строки
void sortLastRow(int** array, int N) {
    // Проверка первого элемента последней строки
    int firstElement = array[N - 1][0];

    if (firstElement > 0) {
        // Если первый элемент положительный, сортируем по убыванию
        sort(array[N - 1], array[N - 1] + N, greater<int>());
        cout << "Сортировка последней строки по убыванию (первый элемент положительный):" << endl;
    }
    else {
        // Если первый элемент отрицательный или равен нулю, сортируем по возрастанию
        sort(array[N - 1], array[N - 1] + N);
        cout << "Сортировка последней строки по возрастанию (первый элемент неположительный):" << endl;
    }

    // Вывод массива после сортировки
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
