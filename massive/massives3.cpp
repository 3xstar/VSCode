#include <iostream>
using namespace std;

int main() {
    int matrix1[3][3] = {
        {12, 7, 33},
        {-9, 15, 26},
        {-18, -29, 4}
    };
    
    int matrix2[3][3] = {
        {10, 14, 21},
        {3, 1, 14},
        {-35, -31, 6}
    };
    
    int matrix3[3][3];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    int matrix4[3][3];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix4[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    
    cout << "Матрица 1:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\nМатрица 2:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\nМатрица 3 (сумма):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix3[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nМатрица 4 (вычитание):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix4[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}