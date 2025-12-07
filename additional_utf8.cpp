#include <iostream>
#include <locale>
#include <fstream>
#include <iomanip>
using namespace std;

void normalizeLine(double& koefA, double& koefB, double& koefC)
{
    const double EPS = 1e-9;

    // 1. Убедимся, что знак первый ненулевого коэффициента положительный
    if (koefA < 0 ||
        (fabs(koefA) < EPS && koefB < 0) ||
        (fabs(koefA) < EPS && fabs(koefB) < EPS && koefC < 0))
    {
        koefA = -koefA;
        koefB = -koefB;
        koefC = -koefC;
    }

    // 2. Нормализация по первому ненулевому коэффициенту
    if (fabs(koefA) > EPS)
    {
        double k = koefA;
        koefA /= k;
        koefB /= k;
        koefC /= k;
    }
    else if (fabs(koefB) > EPS)
    {
        double k = koefB;
        koefA /= k;
        koefB /= k;
        koefC /= k;
    }
    else if (fabs(koefC) > EPS)
    {
        double k = koefC;
        koefA /= k;
        koefB /= k;
        koefC /= k;
    }

    if (fabs(koefA) < EPS) koefA = 0;
    if (fabs(koefB) < EPS) koefB = 0;
    if (fabs(koefC) < EPS) koefC = 0;
}