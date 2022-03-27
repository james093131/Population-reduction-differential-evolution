#include <stdio.h>
#include <iostream>
#include <sstream>
#include <math.h>
// #include <malloc.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <float.h>
#include <sys/stat.h>
#include <iomanip>
#include <random> /* 亂數函式庫 */
#include <ctime>
#include <functional>
#define PI 3.1415926535897932384626433832795029

using namespace std;

void ACKLEY_OBJECTIVE_VALUE(double *x, double *f, int DIM);      // Ackley  -40~40
void RASTRIGIN_OBJECTIVE_VALUE(double *x, double *f, int DIM);   // Rastrigin -5.12~5.12
void ROSENBROCK_OBJECTIVE_VALUE(double *x, double *f, int DIM);  // Rosenbrock -5~10
void SPHERE_OBJECTIVE_VALUE(double *x, double *f, int DIM);      // Sphere 0~PI
void Michalewicz_OBJECTIVE_VALUE(double *x, double *f, int DIM); // Michalewicz -5.12~5.12
void Bent_Cigar_OBJECTIVE_VALUE(double *x, double *f, int DIM);  // BentCigar -100~100
void Schaffer_F7_OBJECTIVE_VALUE(double *x, double *f, int DIM); // Schaffer F7 -100~100
void Zakharov_OBJECTIVE_VALUE(double *x, double *f, int DIM);    // Zakharov -100~100
void Griewank_OBJECTIVE_VALUE(double *x, double *f, int DIM);    // Griewank -600~600
void Schwefel_OBJECTIVE_VALUE(double *x, double *f, int DIM);    // Schwefel -500~500
void SUM_SQUARES_OBJECTIVE_VALUE(double *x, double *f, int DIM); // Sum Squares -10~10
void POWELL_OBJECTIVE_VALUE(double *x, double *f, int DIM);      // Powell -4~5
void Trid_OBJECTIVE_VALUE(double *x, double *f, int DIM);        // Trid -200~200

void Set_Range(double &max, double &min, int func_num, int dim)
{
    switch (func_num)
    {
    case 1:
        max = 32.768;
        min = -32.768;
        break;
    case 2:
        max = 5.12;
        min = -5.12;
        break;
    case 3:
        max = 10.0;
        min = -5.0;
        break;
    case 4:
        max = 5.12;
        min = -5.12;
        break;
    case 5:
        max = PI;
        min = 0;
        break;
    case 6:
        max = 100.0;
        min = -100.0;
        break;
    case 7:
        max = 100.0;
        min = -100.0;
        break;
    case 8:
        max = 100.0;
        min = -100.0;
        break;
    case 9:
        max = 600.0;
        min = -600.0;
        break;
    case 10:
        max = 500.0;
        min = -500.0;
        break;
    case 11:
        max = 10.0;
        min = -10.0;
        break;
    case 12:
        max = 5.0;
        min = -4.0;
        break;
    case 13:
        max = pow(dim, 2);
        min = -pow(dim, 2);
        break;
    }
}
void Testing_Function(double *x, double *f, int DIM, int N, int func_num)
{
    for (int i = 0; i < N; i++)
    {
        switch (func_num)
        {
        case 1:
            ACKLEY_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 2:
            RASTRIGIN_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 3:
            ROSENBROCK_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 4:
            SPHERE_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 5:
            Michalewicz_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 6:
            Bent_Cigar_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 7:
            Schaffer_F7_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 8:
            Zakharov_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 9:
            Griewank_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 10:
            Schwefel_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 11:
            SUM_SQUARES_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 12:
            POWELL_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        case 13:
            Trid_OBJECTIVE_VALUE(&x[i * DIM], &f[i], DIM);
            break;
        }
    }
}
void ACKLEY_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    double sum2 = 0;
    for (int i = 0; i < DIM; i++)
    {

        sum1 += pow(x[i], 2);
        sum2 += cos(2 * M_PI * x[i]);
    }

    f[0] = -20 * (exp((-0.2) * sqrt(sum1 / DIM))) - exp(sum2 / DIM) + 20 + exp(1);
}
void RASTRIGIN_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    double sum2 = 0;
    for (int i = 0; i < DIM; i++)
    {

        sum1 += pow(x[i], 2);
        sum2 += cos(2 * M_PI * x[i]);
    }

    f[0] = sum1 - 10 * sum2 + 10 * DIM;
}

void ROSENBROCK_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    double sum2 = 0;
    for (int i = 1; i < DIM; i++)
    {
        sum1 += pow(x[i] - pow(x[i - 1], 2), 2);
        sum2 += pow(x[i] - 1, 2);
    }

    f[0] = 100 * sum1 + sum2;
}

void SPHERE_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    for (int i = 0; i < DIM; i++)
    {

        sum1 += pow(x[i], 2);
    }

    f[0] = sum1;
}

void Michalewicz_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum = 0;
    for (int i = 0; i < DIM; i++)
    {
        double cal1 = 0;
        double cal2 = 0;
        cal1 = sin(2 * M_PI * x[i]);

        double X = pow(x[i], 2);
        cal2 = sin(i * X / M_PI);
        cal2 = pow(cal2, 20);

        sum += cal1 * cal2;
    }

    f[0] = -sum;
}

void Bent_Cigar_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    double sum2 = 0;
    sum1 = pow(x[0], 2);
    for (int i = 1; i < DIM; i++)
    {

        sum2 += pow(x[i], 2);
    }

    f[0] = sum1 + 1000000 * sum2;
}

void Schaffer_F7_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    for (int i = 0; i < DIM - 1; i++)
    {
        double si = sqrt(pow(x[i], 2) + pow(x[i + 1], 2));
        double F1 = sqrt(si) * (sin(50 * pow(si, 0.2)) + 1);

        f[0] += pow(F1 / (DIM - 1), 2);
    }
}

void Zakharov_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    double sum2 = 0;
    for (int i = 0; i < DIM; i++)
    {
        sum1 += pow(x[i], 2);
        sum2 += 0.5 * (i + 1) * x[i];
    }

    f[0] = sum1 + pow(sum2, 2) + pow(sum2, 4);
}
void Griewank_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    double sum2 = 1;
    for (int i = 0; i < DIM; i++)
    {
        sum1 += pow(x[i], 2);
        sum2 *= cos((x[i] / sqrt(i + 1)));
    }
    f[0] = 1 + sum1 / 4000 - sum2;
}

void Schwefel_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    for (int i = 0; i < DIM; i++)
    {
        double POS = x[i];
        if (POS < 0)
            POS = -POS;
        sum1 += x[i] * sin(sqrt(POS));
    }

    f[0] = 418.9829 * DIM - sum1;
}

void SUM_SQUARES_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    for (int i = 0; i < DIM; i++)
    {
        sum1 += i * pow(x[i], 2);
    }

    f[0] = sum1;
}

void POWELL_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0;
    for (int i = 1; i < DIM / 4; i++)
    {
        double temp = 0.0;
        temp += pow((x[i * 4 - 3] + 10 * x[i * 4 - 2]), 2);
        temp += 5 * pow((x[i * 4 - 1] - x[i * 4]), 2);
        double t3 = (x[i * 4 - 2] - 2 * x[i * 4 - 1]);
        temp += pow(t3, 4);
        double t4 = (x[i * 4 - 3] + 10 * x[i * 4]);
        temp += 10 * pow(t4, 4);
        sum1 += temp;
    }

    f[0] = sum1;
}

void Trid_OBJECTIVE_VALUE(double *x, double *f, int DIM)
{
    f[0] = 0.0;
    double sum1 = 0.0;
    double sum2 = 0.0;
    for (int i = 0; i < DIM; i++)
    {
        sum1 += pow((x[i] - 1), 2);
    }

    for (int i = 1; i < DIM; i++)
    {
        sum2 += x[i] * x[i - 1];
    }
    f[0] = sum1 - sum2;
}
void test_cal(double *x, double &f, int DIM, int func_num)
{
    Testing_Function(&x[0], &f, DIM, 1, func_num);
}