#include <iostream>

using namespace std;

void zeroRowsWithMoreThanTwoNegativeElements(int** array, int N);

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

    // Вызов функции для обнуления строк с более чем 2-мя отрицательными элементами
    zeroRowsWithMoreThanTwoNegativeElements(array, N);

    // Вывод изменённого массива
    cout << "Массив после обнуления строк с более чем 2-мя отрицательными элементами:" << endl;
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

// Функция для обнуления строк с более чем 2-мя отрицательными элементами
void zeroRowsWithMoreThanTwoNegativeElements(int** array, int N) {
    for (int i = 0; i < N; i++) {
        int negativeCount = 0;

        // Подсчёт количества отрицательных элементов в строке
        for (int j = 0; j < N; j++) {
            if (array[i][j] < 0) {
                negativeCount++;
            }
        }

        // Если в строке более 2-х отрицательных элементов, обнуляем её
        if (negativeCount > 2) {
            for (int j = 0; j < N; j++) {
                array[i][j] = 0;
            }
        }
    }
}
