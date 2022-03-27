start=`date +%s`

run=30
dim=30
size=50
t_p=0.02


#test function


i=1 

for (( i; i<14; i=i+1 ))
do   
./PR_DE $run $dim $size $t_p $i -1 >> fun_$dim.txt
done


end=`date +%s`
echo Execution time was `expr $end - $start` seconds.