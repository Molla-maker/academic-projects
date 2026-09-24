#include <iostream>
using namespace std;

void swapMaxEvenMainDiagonalWithMaxOddSecondaryDiagonal(int** array, int N);

int main() {
    setlocale(LC_ALL, "Russian");

    int N;


    cout << "Введите размер массива (N): ";
    cin >> N;

    // Создание динамического двумерного массива
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

    // Вывод массива до замены
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    // Вызов функции для замены максимального четного и максимального нечетного элементов
    swapMaxEvenMainDiagonalWithMaxOddSecondaryDiagonal(array, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

// Реализация функции
void swapMaxEvenMainDiagonalWithMaxOddSecondaryDiagonal(int** array, int N) {
    int maxEvenMainDiagonal = -1; // максимальный четный элемент главной диагонали
    int maxOddSecondaryDiagonal = -1; // максимальный нечетный элемент побочной диагонали
    int mainDiagIndex = -1; // индекс максимального четного элемента главной диагонали
    int secDiagIndex = -1; // индекс максимального нечетного элемента побочной диагонали

    // Поиск максимального четного на главной диагонали
    for (int i = 0; i < N; i++) {
        if (array[i][i] % 2 == 0) { // проверка на четность
            if (array[i][i] > maxEvenMainDiagonal) {
                maxEvenMainDiagonal = array[i][i];
                mainDiagIndex = i; // запоминаем индекс
            }
        }
    }

    // Поиск максимального нечетного на побочной диагонали
    for (int i = 0; i < N; i++) {
        if (array[i][N - 1 - i] % 2 != 0) { // проверка на нечетность
            if (array[i][N - 1 - i] > maxOddSecondaryDiagonal) {
                maxOddSecondaryDiagonal = array[i][N - 1 - i];
                secDiagIndex = i; // запоминаем индекс
            }
        }
    }

    // Если найдено и то, и другое, меняем их местами
    if (mainDiagIndex != -1 && secDiagIndex != -1) {
        int temp = array[mainDiagIndex][mainDiagIndex];
        array[mainDiagIndex][mainDiagIndex] = array[secDiagIndex][N - 1 - secDiagIndex];
        array[secDiagIndex][N - 1 - secDiagIndex] = temp;
    }
    else {
        cout << "Замена невозможна: не найдено подходящих элементов." << endl;
        return;
    }

    // Вывод массива после замены
    cout << "Массив после замены максимального четного элемента главной диагонали и максимального нечетного элемента побочной диагонали:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
