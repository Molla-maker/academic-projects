#include <iostream>

using namespace std;

// функция для поиска и замены минимального и максимального элемента местами
void swapMinMax(int** array, int N) {
    int minVal = array[0][0], maxVal = array[0][0];
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;

    // поиск минимального и максимального элементов
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (array[i][j] < minVal) {
                minVal = array[i][j];
                minRow = i;
                minCol = j;
            }
            if (array[i][j] > maxVal) {
                maxVal = array[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }

    // замена минимального и максимального элементов местами
    int temp = array[minRow][minCol];
    array[minRow][minCol] = array[maxRow][maxCol];
    array[maxRow][maxCol] = temp;

    // Вывод массива после замены
    cout << "Массив после замены минимального и максимального элементов:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int N;

    cout << "Введите размер массива (N): ";
    cin >> N;

    // создание динамического двумерного массива NxN
    int** array = new int* [N];
    for (int i = 0; i < N; i++) {
        array[i] = new int[N];
    }

    cout << "Заполните массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "array[" << i << "][" << j << "] = ";
            cin >> array[i][j];
        }
    }

    // вывод массива 
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Вызов функции для замены минимального и максимального элемента
    swapMinMax(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}
