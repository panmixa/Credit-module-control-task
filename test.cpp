#include "sinh_calc.h"
#include <cassert>
#include <iostream>

int main() {
    double start = -10.0, end = 10.0, step = 0.01, epsilon = 1e-6;

    auto values = SinhCalculator::generate_values(start, end, step, epsilon);
    double sort_time = SinhCalculator::sort_and_measure(values);

    assert(sort_time >= 5.0 && sort_time <= 20.0);
    std::cout << "Test passed: Sort time = " << sort_time << " seconds\n";

    return 0;
}

