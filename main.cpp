#include "normal.cpp"
// #include "22.hpp"
int main(int argc, const char *argv[])
{
    int run = atoi(argv[1]);
    int dim = atoi(argv[2]);
    int size = atoi(argv[3]);
    double target_p = atof(argv[4]);
    int fun_num = atoi(argv[5]);
    int ben_num = atoi(argv[6]);
    PR_DE prde;
    prde.run(run, size, dim, target_p, fun_num, ben_num);
    return 0;
}