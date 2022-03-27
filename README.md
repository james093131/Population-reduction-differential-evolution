# Population-reduction-differential-evolution

This is the implementation of "Population management in metaheuristic algorithms: Could less be more?"
This paper was published at https://www.sciencedirect.com/science/article/pii/S1568494621003124 . 

The author uses the traditional DE and diversity method to get excellent performance. Its experimental result can as well as LSHADE.
It's impressive to get this achievement by the easy way.



1. Type the following command to compile the program:

   make

2. Type either one of the following two commands to run the program:

    ./run.sh
  
    or  
    If you want to run the testfunction dataset, you should set the ben_num to -1, otherwise would run the cec'22 dataset.

    
    ./PR_DE [runs] [size] [dimension] [TargetPercent] [fun_num] [ben_num] 

