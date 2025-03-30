#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;
typedef long long LL;

const size_t MAXN = 4200000;
LL a[MAXN];

void trivial(size_t n) {
    LL sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += a[i];
    }
}

void multilink2(size_t n) {
    LL sum1 = 0, sum2 = 0;
    for (size_t i = 0; i < n; i += 2) {
        sum1 += a[i];
        sum2 += a[i + 1];
    }
    LL sum = sum1 + sum2;
}

void multilink4(size_t n) {
    LL sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    for (size_t i = 0; i < n; i += 4) {
        sum1 += a[i];
        sum2 += a[i + 1];
        sum3 += a[i + 2];
        sum4 += a[i + 3];
    }
    LL sum = sum1 + sum2 + sum3 + sum4;
}

void logRecursion(size_t n) {
    if (n == 1) {
        return;
    } else {
        for (size_t i = 0; i < (n >> 1); i++) {
            a[i] += a[n - i - 1];
        }
        logRecursion(n >> 1);
    }
}

void logLoop(size_t n) {
    for (size_t m = n; m > 1; m >>= 1) {
        for (size_t i = 0; i < (m >> 1); i++) {
            a[i] = a[i << 1] + a[(i << 1) + 1];
        }
    }
}

void init(size_t n) {
    for (size_t i = 0; i < n; i++) {
        a[i] = i;
    }
}

int main() {
    vector<size_t> sizes = {32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304};
    ofstream csvout("sum_results.csv");
    csvout << "n,repeat,trivial_time,trivial_avg_time,multilink2_time,multilink2_avg_time,"
              "multilink4_time,multilink4_avg_time,logRecursion_time,logRecursion_avg_time,"
              "logLoop_time,logLoop_avg_time\n";

    for (size_t n : sizes) {
        cout << "Size: " << n << endl;

        init(n);

        size_t repeat = max(1ull, 10000000 / n);

        // Trivial Algorithm
        auto start_time = steady_clock::now();
        for (size_t i = 0; i < repeat; i++) {
            trivial(n);
        }
        auto end_time = steady_clock::now();
        double trivial_time = duration<double>(end_time - start_time).count();
        double trivial_average_time = trivial_time / repeat;

        // Multilink2 Algorithm
        start_time = steady_clock::now();
        for (size_t i = 0; i < repeat; i++) {
            multilink2(n);
        }
        end_time = steady_clock::now();
        double multilink2_time = duration<double>(end_time - start_time).count();
        double multilink2_average_time = multilink2_time / repeat;

        // Multilink4 Algorithm
        start_time = steady_clock::now();
        for (size_t i = 0; i < repeat; i++) {
            multilink4(n);
        }
        end_time = steady_clock::now();
        double multilink4_time = duration<double>(end_time - start_time).count();
        double multilink4_average_time = multilink4_time / repeat;

        // LogRecursion Algorithm
        start_time = steady_clock::now();
        for (size_t i = 0; i < repeat; i++) {
            logRecursion(n);
        }
        end_time = steady_clock::now();
        double logRecursion_time = duration<double>(end_time - start_time).count();
        double logRecursion_average_time = logRecursion_time / repeat;

        // LogLoop Algorithm
        start_time = steady_clock::now();
        for (size_t i = 0; i < repeat; i++) {
            logLoop(n);
        }
        end_time = steady_clock::now();
        double logLoop_time = duration<double>(end_time - start_time).count();
        double logLoop_average_time = logLoop_time / repeat;

        // Output to console
        cout << "  Trivial Algorithm Time: " << trivial_time << " s ";
        cout << "(Average: " << trivial_average_time << " s)" << endl;
        cout << "  Multilink2 Algorithm Time: " << multilink2_time << " s ";
        cout << "(Average: " << multilink2_average_time << " s)" << endl;
        cout << "  Multilink4 Algorithm Time: " << multilink4_time << " s ";
        cout << "(Average: " << multilink4_average_time << " s)" << endl;
        cout << "  LogRecursion Algorithm Time: " << logRecursion_time << " s ";
        cout << "(Average: " << logRecursion_average_time << " s)" << endl;
        cout << "  LogLoop Algorithm Time: " << logLoop_time << " s ";
        cout << "(Average: " << logLoop_average_time << " s)" << endl;

        // Output to CSV
        csvout << n << "," << repeat << ","
               << trivial_time << "," << trivial_average_time << ","
               << multilink2_time << "," << multilink2_average_time << ","
               << multilink4_time << "," << multilink4_average_time << ","
               << logRecursion_time << "," << logRecursion_average_time << ","
               << logLoop_time << "," << logLoop_average_time << "\n";
    }

    csvout.close();
    return 0;
}