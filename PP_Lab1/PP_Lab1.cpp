#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <direct.h>

using namespace std;
using namespace std::chrono;


void writeMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    ofstream file(filename);
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            file << element << " ";
        }
        file << "\n";
    }
    file.close();
}


vector<vector<int>> generateMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(-100, 100);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = distrib(gen);
        }
    }

    return matrix;
}


vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    setlocale(LC_ALL, "RU");
    _mkdir("data");

    ofstream resultFile("data/ResultExperiment.txt");

    vector<int> sizes = { 10, 50, 100, 500, 600, 800, 900, 1000, 1500 };

    for (int size : sizes) {
        auto A = generateMatrix(size);
        auto B = generateMatrix(size);

        writeMatrixToFile(A, "data/matrix1.txt");
        writeMatrixToFile(B, "data/matrix2.txt");

        auto start = high_resolution_clock::now();
        cout << "Выполняются расчеты для матриц размером" << size << "X" << size<<endl;
        auto C = multiplyMatrices(A, B);
        auto stop = high_resolution_clock::now();

        writeMatrixToFile(C, "data/matrixRes.txt");

        auto duration = duration_cast<milliseconds>(stop - start);
        resultFile << "For matrix size" << size << "x" << size << " time -  " << duration.count() << " ms" << endl;
        cout << "Для матрицы размером" << size << "x" << size << " расчесты выполнены " << endl;
    }

    resultFile.close();
    return 0;
}
