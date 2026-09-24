#include <iostream>

using namespace std;

void divideFirstRowByLastColumnAndWriteInMainDiagonal(int** array, int N);

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

    // Вызов функции для разделения первой строки на последний столбец и записи в главную диагональ
    divideFirstRowByLastColumnAndWriteInMainDiagonal(array, N);

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

// Функция для разделения первой строки на последний столбец и записи в главную диагональ
void divideFirstRowByLastColumnAndWriteInMainDiagonal(int** array, int N) {
    for (int i = 0; i < N; i++) {
        if (array[i][N - 1] != 0) {  // Проверяем, что элемент последнего столбца не равен 0
            array[i][i] = static_cast<double>(array[0][i]) / array[i][N - 1];
        }
        else {
            cout << "Ошибка: элемент последнего столбца на позиции " << i << " равен нулю. Деление на ноль невозможно." << endl;
            return;
        }
    }
}
