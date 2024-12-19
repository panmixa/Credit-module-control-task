#include "sinh_calc.h"
#include <cmath>
#include <algorithm>
#include <chrono>

// Реалізація функції обчислення sinh(x)
double SinhCalculator::calculate(double x, double epsilon) {
    double term = x; // Початковий елемент ряду
    double sum = term;
    int n = 1;
    while (std::abs(term) > epsilon) {
        term *= x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        n++;
    }
    return sum;
}

// Реалізація функції генерації значень
std::vector<double> SinhCalculator::generate_values(double start, double end, double step, double epsilon) {
    std::vector<double> values;
    for (double x = start; x <= end; x += step) {
        values.push_back(SinhCalculator::calculate(x, epsilon));
    }
    return values;
}

// Реалізація функції сортування і вимірювання часу
double SinhCalculator::sort_and_measure(std::vector<double>& values) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::sort(values.begin(), values.end());
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    return elapsed.count();
}

