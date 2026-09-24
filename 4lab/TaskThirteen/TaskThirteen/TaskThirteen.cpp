#include <iostream>
#include <cmath> // Для функции sqrt()

using namespace std;


void computeGeometricMeanAndStoreInLastColumn(int** array, int N);

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

    // Вызов функции для записи среднего геометрического элементов главной и побочной диагонали в последний столбец
    computeGeometricMeanAndStoreInLastColumn(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для записи среднего геометрического элементов главной и побочной диагонали в последний столбец
void computeGeometricMeanAndStoreInLastColumn(int** array, int N) {
    for (int i = 0; i < N; i++) {
        // Элементы главной диагонали: array[i][i]
        // Элементы побочной диагонали: array[i][N-i-1]
        double geometricMean = sqrt(array[i][i] * array[i][N - i - 1]);

        // Записываем среднее геометрическое в последний столбец
        array[i][N - 1] = geometricMean;
    }

    // Выводим изменённую матрицу
    cout << "Массив после записи среднего геометрического элементов главной и побочной диагонали в последний столбец:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
