// Даны целые положительные числа M и N. Сформировать целочисленную матрицу размера M × N, у которой все элементы I-й строки имеют значение 10·I (I = 1, …, M).
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

main()
{
    int M,N;

    cout << "Введите M: " << endl;
    cin >> M;
    cout << "Введите N: " << endl;
    cin >> N;

    int matrix[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 10 * (i + 1);  // I = 1,...,M
        }
    }
    
    cout << "Полученная матрица:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }



// Даны целые положительные числа M и N. Сформировать целочисленную матрицу размера M × N, у которой все элементы J-го столбца имеют значение 5·J (J = 1, …, N).

    int M2,N2;

    cout << "Введите M: " << endl;
    cin >> M2;
    cout << "Введите N: " << endl;
    cin >> N2;

    int matrix2[M2][N2];
    for (int i = 0; i < M2; i++) {
        for (int j = 0; j < N2; j++) {
            matrix2[i][j] = 5 * (j + 1);  // I = J,...,N
        }
    }
    
    cout << "Полученная матрица:" << endl;
    for (int i = 0; i < M2; i++) {
        for (int j = 0; j < N2; j++) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }

}