#include <iostream>

using namespace std;

/*
здарова))
*/

void multiplyLastRowByFirstColumnAndWriteInAntiDiagonal(int** array, int N);

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

    // Вызов функции для умножения последней строки на первый столбец и записи в побочную диагональ
    multiplyLastRowByFirstColumnAndWriteInAntiDiagonal(array, N);

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

// Функция для умножения последней строки на первый столбец и записи в побочную диагональ
void multiplyLastRowByFirstColumnAndWriteInAntiDiagonal(int** array, int N) {
    for (int i = 0; i < N; i++) {
        array[i][N - i - 1] = array[N - 1][i] * array[i][0];  // Умножаем элементы последней строки на соответствующие элементы первого столбца и записываем в побочную диагональ
    }
}
