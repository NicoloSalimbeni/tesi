#include "TMacro.h"

#include <iostream>

double solve_eq2(double a, double b, double c)
{
    double delta = b * b - 4 * a * c;
    if (delta < 0)
    {
        std::cout << "delta negativo" << std::endl;
        return -1;
    }
    double sol_mag = (-b + sqrt(delta)) / (2 * a);
    double sol_min = (-b - sqrt(delta)) / (2 * a);
    if (sol_min > 0)
    {
        std::cout << "indecisione sull'energia" << std::endl;
        return -1;
    }
    return sol_mag;
}