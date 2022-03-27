start=`date +%s`

run=30
dim=30
size=50
t_p=0.02


#test function
i=1 

for (( i; i<14; i=i+1 ))
do   
./PR_DE $run $dim $size $t_p $i -1 >> result/fun_$dim.txt
done


end=`date +%s`
echo Execution time was `expr $end - $start` seconds.


# cec'22
dim=10
i=1 

for (( i; i<13; i=i+1 ))
do   
./PR_DE $run $dim $size $t_p $i 1 >> result/cec22_$dim.txt
done


end=`date +%s`
echo Execution time was `expr $end - $start` seconds.