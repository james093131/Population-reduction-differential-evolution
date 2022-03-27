#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
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

#include "cec22_test_func.cpp"
using namespace std;

class CEC22
{

public:
    void CEC_Results_Records(int NFE, int MAX_NFE, double Current_Best, double *Each_Run_Evaluation_Best)
    {
        if (NFE == MAX_NFE * 0.01)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[0] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.02)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[1] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.05)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[2] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.1)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[3] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.2)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[4] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.3)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[5] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.4)
        {

            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[6] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.5)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[7] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.6)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[8] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.7)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[9] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.8)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[10] += Current_Best;
        }
        else if (NFE == MAX_NFE * 0.9)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[11] += Current_Best;
        }
        else if (NFE == MAX_NFE * 1.0)
        {
            cout << NFE << ' ' << Current_Best << endl;
            Each_Run_Evaluation_Best[12] += Current_Best;
        }
    }
    void cec22_cal(double *P, double &Obj, int DIM, int F, int F_T)
    {
        cec22_test_func(&P[0], &Obj, DIM, 1, F);
        Obj = cec22_fitness_error(F, Obj);
    }
    double cec22_fitness_error(int F, double K)
    {
        switch (F)
        {
        case 1:
            K -= 300.0;
            return K;
            break;
        case 2:
            K -= 400.0;
            return K;
            break;
        case 3:
            K -= 600.0;
            return K;
            break;
        case 4:
            K -= 800.0;
            return K;
            break;
        case 5:
            K -= 900.0;
            return K;
            break;
        case 6:
            K -= 1800.0;
            return K;
            break;
        case 7:
            K -= 2000.0;
            return K;
            break;
        case 8:
            K -= 2200.0;
            return K;
            break;
        case 9:
            K -= 2300.0;
            return K;
            break;
        case 10:
            K -= 2400.0;
            return K;
            break;
        case 11:
            K -= 2600.0;
            return K;
            break;
        case 12:
            K -= 2700.0;
            return K;
            break;
        }
    }
    // void CEC_Classify(int F, int F_T, double START, double END, double RUN_STD, double RUN_AVG, int DIM)
    // {
    //     fstream file;
    //     string A = "PPSO_2021_CEC_Classify" + to_string(DIM) + ".txt";
    //     file.open(A, ios::app);
    //     file << scientific << setprecision(2);
    //     file << F << ' ' << F_T << ' ' << RUN_AVG << ' ' << RUN_STD << ' ' << (END - START) / CLOCKS_PER_SEC << endl;
    // }
    void Run_Classify(double *Run_Result, int F, int F_T, int run, int DIM)
    {
        fstream file;
        string DIR = "./22RUN_RESULT/";
        string A = DIR + to_string(DIM) + "D/" + to_string(F) + "_" + to_string(F_T) + "_Run_Classify.txt";
        file.open(A, ios::out);
        file << scientific << setprecision(2);
        for (int i = 0; i < run; i++)
        {
            file << Run_Result[i] << endl;
        }
    }
};