#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// L1d Cache:   32768 B = 32 KB = 8192 int (n =  90)
// L2 Cache:  1048576 B =  1 MB = 262144 int (n = 512) 
// L3 Cache: 16777216 B = 16 MB = 4,194,304 int (n = 2048)

void trivial(int** mat, int* vec, size_t n) {
    int *result = new int[n]();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            result[i] += mat[j][i] * vec[j];
        }
    }
    delete[] result;
}

void cacheOptimize(int** mat, int* vec, size_t n) {
    int *result = new int[n]();
    for (size_t j = 0; j < n; j++) {
        for (size_t i = 0; i < n; i++) {
            result[i] += mat[j][i] * vec[j];
        }
    }
    delete[] result;
}

void init(int** mat, int* vec, size_t n) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            mat[i][j] = i + j;
        }
        vec[i] = i;
    }
}

int main() {
    vector<size_t> sizes = {20, 40, 60, 80, 100, 200, 400, 500, 750, 1000, 1500, 2000, 2500, 5000, 7500, 10000, 20000, 30000};
    ofstream csvout("matrix_mul_results.csv");
    csvout << "n,repeat,trivial_time,trivial_avg_time,optimized_time,optimized_avg_time\n";
    for (size_t n : sizes) {
        cout << "Matrix size: " << n << " x " << n << endl;
        
        int** mat = new int*[n];
        for (size_t i = 0; i < n; i++) {
            mat[i] = new int[n];
        }
        int* vec = new int[n];
        init(mat, vec, n);

        size_t repeat = max(1ull, 100000000 / (n * n));

        auto start_time = steady_clock::now();
        for (size_t i = 0; i < repeat; i++) {
            trivial(mat, vec, n);
        }
        auto end_time = steady_clock::now();
        double trivial_time = duration<double>(end_time - start_time).count();
        double trivial_average_time = trivial_time / repeat;

        start_time = steady_clock::now();
        for (size_t i = 0; i < repeat; i++) {
            cacheOptimize(mat, vec, n);
        }
        end_time = steady_clock::now();
        double optimized_time = duration<double>(end_time - start_time).count();
        double optimized_average_time = optimized_time / repeat;

        cout << "  Trivial Algorithm Time: " << trivial_time << " s ";
        cout << "(Average: " << trivial_average_time << " s)" << endl;
        cout << "  Cache Optimized Algorithm Time: " << optimized_time << " s ";
        cout << "(Average: " << optimized_average_time << " s)" << endl;
        cout << "  Ratio: " << optimized_time / trivial_time << endl;

        csvout << n << "," << repeat << ","
               << trivial_time << "," << trivial_average_time << ","
               << optimized_time << "," << optimized_average_time << "\n";
        
        for (size_t i = 0; i < n; i++) {
            delete[] mat[i];
        }
        delete[] mat;
        delete[] vec;
    }
    csvout.close();
    return 0;
}