#ifndef SINH_CALC_H
#define SINH_CALC_H

#include <vector>

class SinhCalculator {
public:
    // Обчислення значення sinh(x) з заданою точністю epsilon
    static double calculate(double x, double epsilon);

    // Генерація значень sinh(x) у діапазоні [start, end] з кроком step
    static std::vector<double> generate_values(double start, double end, double step, double epsilon);

    // Сортування масиву значень і вимірювання часу сортування
    static double sort_and_measure(std::vector<double>& values);
};

#endif // SINH_CALC_H

