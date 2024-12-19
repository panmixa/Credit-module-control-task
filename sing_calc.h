#ifndef SINH_CALC_H
#define SINH_CALC_H

#include <vector>
#include <cmath>
#include <chrono>

class SinhCalculator {
public:
    static double calculate(double x, double epsilon = 1e-6);
    static std::vector<double> generate_values(double start, double end, double step, double epsilon);
    static double sort_and_measure(std::vector<double>& values);
};

#endif // SINH_CALC_H
