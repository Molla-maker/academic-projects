#include <iostream>
#include <algorithm> // Для функции swap()

using namespace std;

void swapMinColumnWithMaxRow(int** array, int N);

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

    // Вывод массива до замены
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Вызов функции для замены минимальных элементов столбцов с максимальными строк
    swapMinColumnWithMaxRow(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для замены минимальных элементов столбцов с максимальными строк
void swapMinColumnWithMaxRow(int** array, int N) {
    for (int col = 0; col < N; col++) {
        // Поиск минимального элемента в столбце
        int minInColumn = array[0][col];
        int minRowIndex = 0;
        for (int row = 1; row < N; row++) {
            if (array[row][col] < minInColumn) {
                minInColumn = array[row][col];
                minRowIndex = row;
            }
        }

        // Поиск максимального элемента в строке, соответствующей найденному столбцу
        int maxInRow = array[minRowIndex][0];
        int maxColIndex = 0;
        for (int j = 1; j < N; j++) {
            if (array[minRowIndex][j] > maxInRow) {
                maxInRow = array[minRowIndex][j];
                maxColIndex = j;
            }
        }

        // Меняем местами минимальный элемент столбца и максимальный элемент строки
        swap(array[minRowIndex][col], array[minRowIndex][maxColIndex]);
    }

    // Вывод массива после замены
    cout << "Массив после замены минимальных элементов столбцов с максимальными строк:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
