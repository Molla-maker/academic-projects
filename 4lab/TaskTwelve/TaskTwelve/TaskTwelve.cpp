#include <iostream>
#include <iomanip> // Для вывода с точностью

using namespace std;


void replaceFirstRowWithColumnAverages(int** array, int N);

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

    // Вызов функции для замены элементов первой строки на среднее арифметическое столбцов
    replaceFirstRowWithColumnAverages(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Функция для замены элементов первой строки на среднее арифметическое их столбцов
void replaceFirstRowWithColumnAverages(int** array, int N) {
    for (int j = 0; j < N; j++) {
        int sum = 0;
        // Считаем сумму всех элементов столбца j
        for (int i = 0; i < N; i++) {
            sum += array[i][j];
        }
        // Вычисляем среднее арифметическое столбца
        double average = static_cast<double>(sum) / N;
        // Заменяем элемент первой строки на среднее арифметическое столбца
        array[0][j] = static_cast<int>(average);
    }

    // Вывод изменённой матрицы
    cout << "Массив после замены элементов первой строки на среднее арифметическое столбцов:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
