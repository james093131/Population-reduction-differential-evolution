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

#include "test_function.hpp"
#include "CEC22.hpp"

using namespace std;
typedef vector<char> c1d;
typedef vector<c1d> c2d;
typedef vector<c2d> c3d;
typedef vector<c3d> c4d;
typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<i2d> i3d;
typedef vector<i3d> i4d;
typedef vector<double> d1d;
typedef vector<d1d> d2d;
typedef vector<d2d> d3d;
typedef vector<d3d> d4d;

std::random_device rd;
std::mt19937_64 generator(rd());
class PR_DE : CEC22
{
public:
    d1d run_result;
    double run_avg;

public:
    void run(int run, int size, int dim, double target_p, int fun_num, int ben_num)
    {
        int r = 0;
        run_result.resize(run, 0);
        run_avg = 0.0;
        while (r < run)
        {
            set(size, dim, fun_num, ben_num);
            ini(dim, fun_num, ben_num);
            diversity(target_p, PR_pop);
            while (nfe < MAX_NFE)
            {
                transition(dim);
                selection(dim, fun_num, ben_num);
                find_best();
                if (pop.size() == size)
                    diversity(target_p, PR_pop);
                // cout << nfe << ' ' << current_best << endl;
            }

            run_result[r] = current_best;
            run_avg += current_best;
            r++;
        }

        // for (int i = 0; i < run_result.size(); i++)
        // {
        //     cout << i << ' ' << run_result[i] << endl;
        // }
        cout << fun_num << ' ' << ben_num << ' ' << run_avg / run << endl;
    }

private:
    double cr, f;
    double max, min;
    int nfe, MAX_NFE;
    double current_best;
    d1d current_best_pos;
    d2d pop;
    d1d objective;
    d2d vector;
    double max_div;
    int PR_pop;

private:
    inline double randDouble(double min, double max)
    {
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
        // return (max - min) * rand() / (RAND_MAX + 1.0) + min;
    }
    inline int randInt(int min, int max)
    {
        std::uniform_int_distribution<int> int_distribution(min, max);
        return int_distribution(generator);
        // return rand() % (max - min + 1) + min;
    }
    void set(int size, int dim, int fun_num, int ben_num)
    {
        cout << scientific << setprecision(8);
        max = 100.0;
        min = -100.0;
        if (ben_num == -1) // testing function
        {
            Set_Range(max, min, fun_num, dim);
            MAX_NFE = dim * 10000;
        }
        else
        {
            if (dim == 10)
                MAX_NFE = 200000;
            else
                MAX_NFE = 1000000;
        }
        nfe = 0;

        cr = 0.2;
        f = 0.75;

        pop.clear();
        pop.swap(pop);
        pop.assign(size, d1d(dim));

        objective.clear();
        objective.swap(objective);
        objective.resize(size);

        vector.clear();
        vector.swap(vector);
        vector.assign(size, d1d(dim, 0));

        current_best = DBL_MAX;

        max_div = 0.0;
        PR_pop = 10;
    }
    void ini(int dim, int fun_num, int ben_num)
    {
        for (int i = 0; i < pop.size(); i++)
        {
            for (int j = 0; j < pop[i].size(); j++)
            {
                pop[i][j] = randDouble(min, max);
            }
            eva(pop[i], objective[i], dim, fun_num, ben_num);
            if (current_best > objective[i])
            {
                current_best = objective[i];
                current_best_pos = pop[i];
            }
        }
    }
    void eva(d1d &position, double &objective, int dim, int fun_num, int ben_num)
    {
        if (ben_num == -1)
            Testing_Function(&position[0], &objective, dim, 1, fun_num);
        else
            cec22_cal(&position[0], objective, dim, fun_num, ben_num);
        nfe++;
    }

    d1d median_pop()
    {
        d1d median(pop[0].size(), 0.0);
        for (int j = 0; j < median.size(); j++)
        {
            d1d temp(pop.size());
            for (int i = 0; i < pop.size(); i++)
            {
                temp[i] = pop[i][j];
            }
            sort(temp.begin(), temp.end());
            if (temp.size() % 2 == 0)
                median[j] = (temp[temp.size() / 2] + temp[temp.size() / 2 + 1]) / 2;
            else
                median[j] = temp[temp.size() / 2];
        }
        return median;
    }
    void diversity(double target_p, int PR_pop)
    {
        double sum_div = 0.0;
        d1d median = median_pop();
        for (int j = 0; j < median.size(); j++)
        {
            double temp = 0.0;
            for (int i = 0; i < pop.size(); i++)
            {
                double temp_div = pop[i][j] - median[j];
                if (temp_div < 0)
                    temp_div *= -1;
                temp += temp_div;
            }
            temp /= pop.size();
            sum_div += temp;
        }
        sum_div /= median.size();

        if (sum_div > max_div)
            max_div = sum_div;

        else if (sum_div / max_div <= target_p)
        {
            population_reduction(PR_pop);
        }
    }
    void population_reduction(int PR_pop)
    {
        d2d new_pop;
        d1d new_obj;
        d2d new_vector;
        new_pop.assign(PR_pop, d1d(pop[0].size()));
        new_vector.assign(PR_pop, d1d(pop[0].size()));
        new_obj.resize(PR_pop);
        new_pop[0] = current_best_pos;
        new_obj[0] = current_best;
        for (int i = 1; i < new_pop.size(); i++)
        {
            int ind = randInt(0, pop.size() - 1);
            new_pop[i] = pop[ind];
            new_obj[i] = objective[ind];
            pop.erase(pop.begin() + ind);
        }

        pop = new_pop;
        objective = new_obj;
        vector = new_vector;
    }
    void transition(int dim)
    {
        for (int i = 0; i < pop.size(); i++)
        {
            int r1, r2, r3;
            int rind = randInt(0, dim - 1);
            do
            {
                r1 = randInt(0, pop.size() - 1);
            } while (r1 == i);
            do
            {
                r2 = randInt(0, pop.size() - 1);
            } while (r2 == r1 || r2 == i);
            do
            {
                r3 = randInt(0, pop.size() - 1);
            } while (r3 == r2 || r3 == r1 || r3 == i);
            for (int j = 0; j < dim; j++)
            {
                if (randDouble(0.0, 1.0) < cr || j == rind)
                    vector[i][j] = pop[r1][j] + f * (pop[r2][j] - pop[r3][j]);
                else
                    vector[i][j] = pop[i][j];

                if (vector[i][j] > max)
                    vector[i][j] = randDouble(min, max);
                if (vector[i][j] < min)
                    vector[i][j] = randDouble(min, max);
            }
        }
    }
    void selection(int dim, int fun_num, int ben_num)
    {
        for (int i = 0; i < pop.size(); i++)
        {
            double temp_obj;
            eva(vector[i], temp_obj, dim, fun_num, ben_num);
            if (temp_obj < objective[i])
            {
                pop[i] = vector[i];
                objective[i] = temp_obj;
            }
            if (nfe == MAX_NFE)
                break;
        }
    }
    void find_best()
    {
        for (int i = 0; i < pop.size(); i++)
        {
            if (current_best > objective[i])
            {
                current_best = objective[i];
                current_best_pos = pop[i];
            }
        }
    }
};