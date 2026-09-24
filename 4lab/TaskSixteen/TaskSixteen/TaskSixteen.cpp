#include <iostream>

using namespace std;

void multiplyFirstColumnByLastAndWriteToFirstRow(int** array, int N);

int main() {
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

    // Вызов функции для умножения первого столбца на последний и записи результата в первую строку
    multiplyFirstColumnByLastAndWriteToFirstRow(array, N);

    // Вывод изменённого массива
    cout << "Массив после умножения первого столбца на последний и записи результата в первую строку:" << endl;
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

// Функция для умножения первого столбца на последний и записи результата в первую строку
void multiplyFirstColumnByLastAndWriteToFirstRow(int** array, int N) {
    for (int i = 0; i < N; i++) {
        // Умножаем элемент первого столбца на элемент последнего столбца и записываем в первую строку
        array[0][i] = array[i][0] * array[i][N - 1];
    }
}
