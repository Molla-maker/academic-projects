#include <iostream>

using namespace std;

void zeroColumnsWithEvenSum(int** array, int N);

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

    // Вывод массива до обнуления столбцов с чётной суммой
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Вызов функции для обнуления столбцов с чётной суммой
    zeroColumnsWithEvenSum(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для обнуления столбцов с чётной суммой
void zeroColumnsWithEvenSum(int** array, int N) {
    for (int col = 0; col < N; col++) {
        int sum = 0;

        // Считаем сумму элементов в столбце
        for (int row = 0; row < N; row++) {
            sum += array[row][col];
        }

        // Если сумма столбца чётная, обнуляем его
        if (sum % 2 == 0) {
            for (int row = 0; row < N; row++) {
                array[row][col] = 0;
            }
        }
    }

    // Вывод массива после обнуления столбцов
    cout << "Массив после обнуления столбцов с чётной суммой:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
