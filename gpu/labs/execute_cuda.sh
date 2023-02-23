#!/bin/bash
echo > timing_cuda.txt
echo > timing_cpu.txt
for j in `seq 4 30`;
do
	for i in `seq 0 20`;
	do
		t="2^${i}";
		t=`echo "$t" | bc -l`;
		o=`./lab4 $j $t 2>&1`;
		lastline=`echo $o | tail -n 1`;
		echo "N = $j; Threads $t = $lastline" | tee -a timing_cuda.txt
	done;
	o=`./lab2 $j 2>&1`;
	lastline=`echo $o | tail -n 1`;
	echo "N = $j; Threads 1 = $lastline" | tee -a timing_cpu.txt
done;

cat timing_cuda.txt | grep -v "0 0 0 0 0 0 0" | sed -rn 's/N = (.*); Threads (.*) = .*: (.*) ms \((.*) ms\).*/CUDA; \1; \2; \3; \4;/p' > timing_cuda.csv
cat timing_cpu.txt | grep -v "0 0 0 0 0 0 0" | sed -rn 's/N = (.*); Threads (.*) = .*: (.*) ms \((.*) ms\).*/CPU; \1; \2; \3; \4;/p' > timing_cpu.csv
cat timing_cuda.csv timing_cpu.csv > timing_joint.csv