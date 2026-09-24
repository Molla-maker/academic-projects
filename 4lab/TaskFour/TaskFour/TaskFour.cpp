#include <iostream>
#include <algorithm> // Для функции swap()

using namespace std;

void swapRowWithMaxElement(int** array, int N);

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

    // Вывод массива до перестановки строк
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Вызов функции для перестановки строки с максимальным элементом
    swapRowWithMaxElement(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для перестановки строки с максимальным элементом с первой строкой
void swapRowWithMaxElement(int** array, int N) {
    int maxElement = array[0][0];
    int maxRow = 0;

    // Поиск строки с максимальным элементом
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (array[i][j] > maxElement) {
                maxElement = array[i][j];
                maxRow = i;
            }
        }
    }

    // Переставляем строки
    if (maxRow != 0) { // Если строка с максимальным элементом не первая
        swap(array[0], array[maxRow]); // Меняем местами первую строку с найденной
    }

    // Вывод массива после перестановки строк
    cout << "Массив после перестановки строки с максимальным элементом:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
